/******************************
 Description: Http downloader.
 Author: M.Wan
 Date: 03/18/2015
 ******************************/

#ifndef __HTTP_HTTPDOWNLOADER__
#define __HTTP_HTTPDOWNLOADER__

#include "../../base/mwbase.h"

#include <string>

#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <errno.h>

MW_FRAMEWORK_BEGIN

class MWHttpDownloader;

class MWDownloadTask;

class MW_INTERFACE MWHttpDownloaderDelegate
{
public:
    virtual ~MWHttpDownloaderDelegate() {}
    
    /**
     * Delegate when the download task starts.
     *
     * @param downloader Related downloader of the task.
     */
    virtual void onDownloadStarted(MWHttpDownloader *downloader) = 0;
    /**
     * Delegate when the download task executes.
     *
     * @param downloader Related downloader of the task.
     * @param progress Downloading progress.
     */
    virtual void onDownloading(MWHttpDownloader *downloader, float progress) = 0;
    /**
     * Delegate when the download task completes.
     *
     * @param downloader Related downloader of the task.
     */
    virtual void onDownloadCompleted(MWHttpDownloader *downloader) = 0;
    /**
     * Delegate when the download task fails.
     *
     * @param downloader Related downloader of the task.
     * @param errorMsg Encountered error message.
     */
    virtual void onDownloadFailed(MWHttpDownloader *downloader, const std::string &errorMsg) = 0;
};

class MW_DLL MWDownloadTask : public MWObject
{
    friend MWHttpDownloader;
    friend size_t onReceiveData(void *, size_t size, size_t writeSize, void *userdata);
    friend int onProgress(void *userdata, double totalToDownload, double downloaded, double totalToUpload, double uploaded);
public:
    /**
     * Create a download task.
     *
     * @param url Download url.
     * @param savePath Local file path to save.
     * @param userdata User object to store in the task.
     * @param canResume Whether support the breakpoint resuming.
     * @param retryTimes Retry count when downloading failed.
     *
     * @return DownloadTask object.
     */
    static MWDownloadTask *create(const std::string &url, const std::string &savePath, cocos2d::Ref *userdata = nullptr, bool canResume = true, int retryTimes = 3);
    
    /**
     * DownloadTask constructor.
     *
     * @param url Download url.
     * @param savePath Local file path to save.
     * @param userdata User object to store in the task.
     * @param canResume Whether support the breakpoint resuming.
     * @param retryTimes Retry count when downloading failed.
     */
    explicit MWDownloadTask(const std::string &url, const std::string &savePath, cocos2d::Ref *userdata = nullptr, bool canResume = true, int retryTimes = 3);
    /**
     * DownloadTask destructor.
     */
    virtual ~MWDownloadTask();
    
    /**
     * Get download url.
     *
     * @return Download url.
     */
    inline const char *getUrl()
    {
        return _url.c_str();
    }
    /**
     * Get local download path.
     *
     * @return Local download path.
     */
    inline const char *getPath()
    {
        return _path.c_str();
    }
    /**
     * Whether supports breakpoint resume feature.
     *
     * @return Boolean value.
     */
    inline bool supportResume()
    {
        return _supportResume;
    }
    /**
     * Get stored user object.
     *
     * @return Stored user object.
     */
    inline cocos2d::Ref *getUserdata()
    {
        return _userdata;
    }
    /**
     * Set stored user object.
     *
     * @param Stored user object.
     */
    void setUserdata(cocos2d::Ref *userdata);
    
protected:
    int _retryOnce();
    
    std::string _url;
    std::string _path;
    bool _supportResume;
    cocos2d::Ref *_userdata;
    
    int _breakpointBytes;
    FILE *_saveFile;
    size_t _lastDownloadedBytes;
    size_t _unreceivedDataTimes;
    volatile int _retryTimes;
};

enum class MWDownloadEventType
{
    DOWNLOAD_STARTED = 0,
    DOWNLOAD_INPROGRESS,
    DOWNLOAD_SUCCESS,
    DOWNLOAD_FAILED,
};

class MW_DLL MWDownloadEvent : public MWObject
{
public:
    /**
     * Create a download event.
     *
     * @param eventType Download event type.
     * @param task Related download task.ß
     *
     * @return DownloadEvent object.
     */
    static MWDownloadEvent *create(MWDownloadEventType eventType, MWDownloadTask *task);
    
    /**
     * DownloadEvent constructor.
     *
     * @param eventType Download event type.
     * @param task Related download task.ß
     */
    MWDownloadEvent(MWDownloadEventType eventType, MWDownloadTask *task);
    /**
     * DownloadEvent destructor.
     */
    ~MWDownloadEvent();
    
    /**
     * DownloadEvent getter and setter.
     */
    MW_SYNTHESIZE(MWDownloadEventType, _type, Type);
    /**
     * Related task getter and setter.
     */
    MW_SYNTHESIZE_RETAIN(MWDownloadTask*, _task, RelatedTask);
    /**
     * Download progress getter and setter.
     */
    MW_SYNTHESIZE(float, _progress, Progress);
    /**
     * Error message getter and setter.
     */
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _errorMsg, ErrorMessage);
};

/**
 * Http downloader.
 */
class MW_DLL MWHttpDownloader : public MWObject
{
    friend size_t onReceiveData(void *, size_t size, size_t writeSize, void *userdata);
    friend void *downloadThread(void *data);
    friend int onProgress(void *userdata, double totalToDownload, double downloaded, double totalToUpload, double uploaded);
public:
    /**
     * HttpDownloader constructor.
     */
    MWHttpDownloader();
    /**
     * HttpDownloader destructor.
     */
    virtual ~MWHttpDownloader();
    
    /**
     * Destroy all tasks.
     */
    void destroy();
    
    /**
     * Begin a download task.
     *
     * @param url Download url.
     * @param savePath Local file path to save.
     * @param userdata User object to store in the task.
     * @param canResume Whether support the breakpoint resuming.
     * @param retryTimes Retry count when downloading failed.
     */
    void beginDownloading(const std::string &url, const std::string &savePath, cocos2d::Ref *userdata, bool supportResume, int retryTimes);
    
    /**
     * Retry failed task.
     *
     * @param userdata User object.
     *
     * @return Whether the operation is supported.
     */
    bool retryTask(cocos2d::Ref *userdata);
    
    /**
     * Whether the downloader is downloading.
     *
     * @return Boolean value.
     */
    inline bool isDownloading()
    {
        return _downloading;
    }
    
    void onDownloadUpdated(float dt);
    
    /**
     * Downloader delegate getter and setter.
     */
    MW_SYNTHESIZE(MWHttpDownloaderDelegate*, _delegate, Delegate);
    
protected:
    bool _initThread();
    void _executeTask();
    
    bool _initTask();
    bool _download();
    bool _finishDownloading();
    
    void _addDownloadEvent(MWDownloadEventType eventType, MWDownloadTask *task, float progress, const std::string &error = "");
    
    bool _inited;       // whether inited.
    MWQueue *_taskQueue;
    MWQueue *_eventQueue;
    
    bool _needQuit;
    MWDownloadTask *_currentTask;
    bool _downloading;
    
    pthread_t _networkThread;
    pthread_mutex_t _taskMutex;
    pthread_mutex_t _eventMutex;
    sem_t *_newTaskSemPtr;
    sem_t _newTaskSem;
};

MW_FRAMEWORK_END

#endif /* defined(__HTTP_HTTPDOWNLOADER__) */
