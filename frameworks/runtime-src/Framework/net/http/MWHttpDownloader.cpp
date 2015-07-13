#include "MWHttpDownloader.h"
#include "cocos2d.h"
#include "../../platform/MWIOUtils.h"

#include <time.h>
#include <new>

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "curl/include/ios/curl/curl.h"
#include "curl/include/ios/curl/easy.h"
#endif

using namespace cocos2d;
using namespace std;

#define TEMP_FILE_SUFFIX ".tmp"
#define MWHTTPDOWNLOADER_SEMAPHORE_NAME "http_downloader_sem"
#define DOWNLOADING_UNRESPONSE_TIMES 10

MW_FRAMEWORK_BEGIN

static string g_downloaderSemName = string(MWHTTPDOWNLOADER_SEMAPHORE_NAME);

void *downloadThread(void *userdata)
{
    MWHttpDownloader *pDownloader = (MWHttpDownloader *) userdata;
    
    while (!pDownloader->_needQuit) {
        // wait for new task
        sem_wait(pDownloader->_newTaskSemPtr);
        
        pDownloader->_downloading = true;
        
        MWDownloadTask *pTask = nullptr;
        pthread_mutex_lock(&pDownloader->_taskMutex);
        if (pDownloader->_taskQueue->count() > 0) {
            pTask = (MWDownloadTask *) pDownloader->_taskQueue->front();
            pDownloader->_taskQueue->dequeue();
        }
        pthread_mutex_unlock(&pDownloader->_taskMutex);
        
        if (pTask) {
            pDownloader->_setCurrentTask(pTask);
            pDownloader->_executeTask();
        }
        pDownloader->_downloading = false;
    }
    
    return nullptr;
}

size_t onReceiveData(void *buffer, size_t size, size_t writeSize, void *userdata)
{
    MWHttpDownloader *pDownloader = (MWHttpDownloader *) userdata;
    MWDownloadTask *pTask = pDownloader->_currentTask;
    
    size_t written = fwrite(buffer, size, writeSize, pTask->_saveFile);
    return written;
}

int onProgress(void *userdata, double totalToDownload, double downloaded, double totalToUpload, double uploaded)
{
    MWHttpDownloader *pDownloader = (MWHttpDownloader *) userdata;
    MWDownloadTask *pTask = pDownloader->_currentTask;
    
    // When the nonresponse count exceeds the DOWNLOADING_UNRESPONSE_TIMES, treat this as download exception.
    if (pTask->_lastDownloadedBytes == (ssize_t) downloaded) {
        ++pTask->_unreceivedDataTimes;
    } else {
        pTask->_unreceivedDataTimes = 0;
    }
    pTask->_lastDownloadedBytes = (ssize_t)downloaded;
    
    if (pTask->_unreceivedDataTimes >= DOWNLOADING_UNRESPONSE_TIMES) {
        return 1;
    }
    
    float progress = downloaded / totalToDownload;
    if (progress < 0) {
        progress = 0;
    } else if (progress > 1) {
        progress = 1;
    }
    pDownloader->_addDownloadEvent(EDownloadEventType::DOWNLOAD_INPROGRESS, pTask, progress);
    
    return 0;
}

/************************ MWDownloadTask Implementation ************************/
MWDownloadTask::MWDownloadTask(const string &url, const string &savePath, Ref *userdata, bool supportResume, int retryTimes)
: _url(url)
, _savePath(savePath)
, _supportResume(supportResume)
, _userdata(nullptr)
, _breakpointBytes(0)
, _saveFile(nullptr)
, _lastDownloadedBytes(0)
, _unreceivedDataTimes(0)
, _retryTimes(retryTimes)
{
    this->setUserdata(userdata);
}

MWDownloadTask::~MWDownloadTask()
{
    CC_SAFE_RELEASE(_userdata);
}

MWDownloadTask *MWDownloadTask::create(const std::string &url, const std::string &savePath, Ref *userdata, bool supportResume, int retryTimes)
{
    auto pTask = new (nothrow) MWDownloadTask(url, savePath, userdata, supportResume, retryTimes);
    if (pTask) {
        pTask->autorelease();
        return pTask;
    }
    CC_SAFE_RELEASE(pTask);
    return pTask;
}

int MWDownloadTask::_retryOnce()
{
    --_retryTimes;
    if (_retryTimes < 0) {
        _retryTimes = 0;
    }
    return _retryTimes;
}

void MWDownloadTask::setUserdata(cocos2d::Ref *userdata)
{
    if (_userdata != userdata) {
        CC_SAFE_RELEASE(_userdata);
        CC_SAFE_RETAIN(userdata);
        _userdata = userdata;
    }
}

/************************ MWDownloadEvent Implementation ************************/
MWDownloadEvent *MWDownloadEvent::create(EDownloadEventType eventType, MWDownloadTask *task)
{
    auto pEvent = new (nothrow) MWDownloadEvent(eventType, task);
    if (pEvent) {
        pEvent->autorelease();
        return pEvent;
    }
    CC_SAFE_RELEASE(pEvent);
    return nullptr;
}

MWDownloadEvent::MWDownloadEvent(EDownloadEventType eventType, MWDownloadTask *task)
: _type(eventType)
, _task(nullptr)
, _progress(0.0f)
, _errorMsg()
{
    this->setRelatedTask(task);
}

MWDownloadEvent::~MWDownloadEvent()
{
    CC_SAFE_RELEASE(_task);
}

/************************ MWHttpDownloader Implementation ************************/
MWHttpDownloader::MWHttpDownloader()
: _inited(false)
, _taskQueue(new MWQueue())
, _eventQueue(new MWQueue())
, _needQuit(false)
, _currentTask(nullptr)
, _delegate(nullptr)
, _downloading(false)
, _needRetry(false)
, _eventMutex()
{
}

MWHttpDownloader::~MWHttpDownloader()
{
    CC_SAFE_RELEASE(_taskQueue);
    CC_SAFE_RELEASE(_eventQueue);
}

void MWHttpDownloader::destroy()
{
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    
    _needQuit = true;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    sem_unlink(g_downloaderSemName.c_str());
    sem_close(_newTaskSemPtr);
    pthread_mutex_destroy(&_taskMutex);
    pthread_mutex_destroy(&_eventMutex);
#else
    sem_destroy(_newTaskSemPtr);
    pthread_mutex_destroy(&_taskMutex);
    pthread_mutex_destroy(&_eventMutex);
#endif
    this->release();
}

void MWHttpDownloader::beginDownloading(const std::string &url, const std::string &savePath, cocos2d::Ref *userdata, bool supportResume, int retryTimes)
{
    if (url.size() == 0 || savePath.size() == 0) {
        MW_THROW_EXCEPTION(5014);
    }
    
    // init thread
    if (!_inited) {
        _inited = this->_initThread();
        if (!_inited) {
            CCLOG("MWHttpDownloader init thread failed.");
            return;
        }
    }
    
    // create download task and add to the task queue.
    auto pTask = MWDownloadTask::create(url, savePath, userdata, supportResume, retryTimes);
    
    pthread_mutex_lock(&_taskMutex);
    _taskQueue->enqueue(pTask);
    pthread_mutex_unlock(&_taskMutex);
    
    // post semaphore to the downloading thread.
    sem_post(_newTaskSemPtr);
}

bool MWHttpDownloader::retry(cocos2d::Ref *userdata)
{
    if (this->_needRetry) {
        MWDownloadTask *pRetryTask = this->_currentTask;
        if (pRetryTask && pRetryTask->_retryTimes > 0) {
            pRetryTask->_retryOnce();
            
            auto pTask = MWDownloadTask::create(pRetryTask->getUrl(), pRetryTask->getSavePath(), userdata, pRetryTask->_supportResume, pRetryTask->_retryTimes);
            pthread_mutex_lock(&_taskMutex);
            _taskQueue->enqueue(pTask);
            pthread_mutex_unlock(&_taskMutex);
            
            sem_post(_newTaskSemPtr);
            
            return true;
        } else {
            CC_SAFE_RELEASE(pRetryTask);
        }
    }
    
    return false;
}

void MWHttpDownloader::onDownloadUpdated(float dt)
{
    if (_delegate) {
        pthread_mutex_lock(&_eventMutex);
        MWQueue *pCopyQueue = _eventQueue->clone();
        _eventQueue->clear();
        pthread_mutex_unlock(&_eventMutex);
        
        MWDownloadEvent *pEvent = nullptr;
        while (pCopyQueue->count() > 0) {
            pEvent = (MWDownloadEvent *) pCopyQueue->front();
            Ref *userdata = pEvent->getRelatedTask()->getUserdata();
            if (pEvent->getType() == EDownloadEventType::DOWNLOAD_STARTED) {
                _delegate->onDownloadStarted(this, userdata);
            } else if (pEvent->getType() == EDownloadEventType::DOWNLOAD_INPROGRESS) {
                _delegate->onDownloading(this, pEvent->getProgress(), userdata);
            } else if (pEvent->getType() == EDownloadEventType::DOWNLOAD_SUCCESS) {
                _delegate->onDownloadCompleted(this, userdata);
            } else if (pEvent->getType() == EDownloadEventType::DOWNLOAD_FAILED) {
                _delegate->onDownloadFailed(this, pEvent->getErrorMessage(), userdata);
            }
            pCopyQueue->dequeue();
        }
    }
}

bool MWHttpDownloader::_initThread()
{
    pthread_mutex_init(&_taskMutex, NULL);
    pthread_mutex_init(&_eventMutex, NULL);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    long t = time(NULL);
    g_downloaderSemName.append(__String::createWithFormat("%ld", t)->getCString());
    _newTaskSemPtr = sem_open(g_downloaderSemName.c_str(), O_CREAT, 0644, 0);
    if (_newTaskSemPtr == SEM_FAILED) {
        CCLOG("Create new task semaphore failed, errno = %d.", errno);
        _newTaskSemPtr = nullptr;
        return false;
    }
#else
    sem_t newTaskSem;
    int semRet = sem_init(&newTaskSem, 0, 0);
    if (semRet < 0) {
        CCLOG("Create complete task semaphore failed.");
        return false;
    }
    _newTaskSemPtr = &newTaskSem;
#endif
    
    pthread_create(&_networkThread, nullptr, &downloadThread, this);
    pthread_detach(_networkThread);
    
    Director::getInstance()->getScheduler()->schedule(schedule_selector(MWHttpDownloader::onDownloadUpdated), this, 0, false);
    
    return true;
}

bool MWHttpDownloader::_initTask()
{
    string tmpFullPath = _currentTask->getSavePath();
    
    // the save path should be a file path.
    if (tmpFullPath[tmpFullPath.size() - 1] == '/') {
        CCLOG("Not a directory save path, use file path instead.");
        return false;
    }
    
    // create directory
    string dirPath = tmpFullPath.substr(0, tmpFullPath.find_last_of('/'));
    if (!MWIOUtils::getInstance()->createDirectory(dirPath)) {
        CCLOG("Create download directory failed.");
        return false;
    }
    
    tmpFullPath.append(TEMP_FILE_SUFFIX);
    
    // delete old tmp file when not in breakpoint resume mode.
    if (!this->_currentTask->_supportResume && MWIOUtils::getInstance()->fileExists(tmpFullPath)) {
        bool res = MWIOUtils::getInstance()->removeFile(tmpFullPath);
        if (!res) {
            CCLOG("Encounter an error when try to delete old .tmp file");
            return false;
        }
    }
    
    FILE *pFile = fopen(tmpFullPath.c_str(), "ab");
    if (!pFile) {
        CCLOG("Create downloading file error.");
        return false;
    }
    
    // breakpoint resume mode, it requires to get file size.
    fseek(pFile, 0, SEEK_END);
    _currentTask->_breakpointBytes = ftell(pFile);
    _currentTask->_saveFile = pFile;
    
    return true;
}

void MWHttpDownloader::_executeTask()
{
    CCLOG("Begin downloading file: [%s]", _currentTask->getUrl());
    
    this->_addDownloadEvent(EDownloadEventType::DOWNLOAD_STARTED, _currentTask, 0);
    this->setNeedRetry(false);
    
    bool ret = true;
    do {
        ret = this->_initTask();
        if (!ret) {
            this->setNeedRetry(true);
            this->_addDownloadEvent(EDownloadEventType::DOWNLOAD_FAILED, _currentTask, 0, GetErrorString(5011));
            break;
        }
        ret = this->_download();
        if (!ret) {
            this->setNeedRetry(true);
            this->_addDownloadEvent(EDownloadEventType::DOWNLOAD_FAILED, _currentTask, 0, GetErrorString(5012));
            break;
        }
        // close file handle to ensure the move operation.
        if (_currentTask->_saveFile) {
            fclose(_currentTask->_saveFile);
            _currentTask->_saveFile = nullptr;
        }
        ret = this->_finishDownloading();
        if (!ret) {
            this->setNeedRetry(true);
            this->_addDownloadEvent(EDownloadEventType::DOWNLOAD_FAILED, _currentTask, 0, GetErrorString(5013));
            break;
        }
    } while (false);
    
    if (_currentTask->_saveFile) {
        // close the file handle.
        fclose(_currentTask->_saveFile);
        _currentTask->_saveFile = nullptr;
    }
    
    if (ret) {
        this->_addDownloadEvent(EDownloadEventType::DOWNLOAD_SUCCESS, _currentTask, 1);
    }
}

bool MWHttpDownloader::_download()
{
    // use curl.
    CURL *curl = curl_easy_init();
    if (!curl) {
        CCLOG("Curl initialization failed.");
        return false;
    }
    
    char *errorBuffer = (char*)malloc(CURL_ERROR_SIZE);
    CURLcode res;
    
    curl_easy_setopt(curl, CURLOPT_URL, _currentTask->getUrl());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onReceiveData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    
    // breakpoint resume
    if (_currentTask->_supportResume && _currentTask->_breakpointBytes != 0) {
        char buffer[1000] = { 0 };
        sprintf(buffer, "%d-", _currentTask->_breakpointBytes);
        string str(buffer);
        curl_easy_setopt(curl, CURLOPT_RANGE, str.c_str());
    }
    
    // no timeout
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 0);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
    
    // download progress
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, onProgress);
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
    
    // forbid alarm timeout, dns timeout depends on this, so there is no timeout check.
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    
    // dns cache, 6 hours
    static CURLSH *shareHandle = nullptr;
    if (!shareHandle) {
        shareHandle = curl_share_init();
        curl_share_setopt(shareHandle, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
    }
    curl_easy_setopt(curl, CURLOPT_SHARE, shareHandle);
    curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 3600 * 6);
    
    res = curl_easy_perform(curl);
    
    int responseCode;
    CURLcode code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    // 206 is breakpoing resuming.
    if (code != CURLE_OK || (responseCode != 200 && responseCode != 206)) {
        code = CURLE_HTTP_RETURNED_ERROR;
    }
    
    curl_easy_cleanup(curl);
    
    if (res != 0 || code != CURLE_OK || (responseCode != 200 && responseCode != 206)) {
        string errorMsg;
        errorMsg.append("Download failed: ").append(errorBuffer);
        CCLOG("Download error: %s", errorMsg.c_str());
        return false;
    }
    free(errorBuffer);
    
    return true;
}

bool MWHttpDownloader::_finishDownloading()
{
    string tmpFullPath = _currentTask->getSavePath();
    
    // delete the save file which does already exist.
    if (MWIOUtils::getInstance()->fileExists(tmpFullPath)) {
        if (!MWIOUtils::getInstance()->removeFile(tmpFullPath)) {
            CCLOG("Remove existed file failed.");
            return false;
        }
    }
    
    tmpFullPath.append(TEMP_FILE_SUFFIX);
    
    if (!MWIOUtils::getInstance()->moveFile(tmpFullPath, _currentTask->getSavePath())) {
        CCLOG("Rename downloaded file failed.");
        return false;
    }
    
    return true;
}

void MWHttpDownloader::_addDownloadEvent(EDownloadEventType eventType, MWDownloadTask *task, float progress, const std::string &error)
{
    auto pEvent = MWDownloadEvent::create(eventType, task);
    pEvent->setProgress(progress);
    pEvent->setErrorMessage(error);
    
    pthread_mutex_lock(&_eventMutex);
    _eventQueue->enqueue(pEvent);
    pthread_mutex_unlock(&_eventMutex);
}

void MWHttpDownloader::_setCurrentTask(mwframework::MWDownloadTask *task)
{
    if (_currentTask != task) {
        CC_SAFE_RELEASE(_currentTask);
        _currentTask = task;
        CC_SAFE_RETAIN(_currentTask);
    }
}

MW_FRAMEWORK_END