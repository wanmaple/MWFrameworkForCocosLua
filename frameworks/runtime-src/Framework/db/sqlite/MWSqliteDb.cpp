#include "MWSqliteDb.h"
#include "../../platform/MWIOUtils.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

static MWDictionary g_dbCache;

MWSqliteDb::MWSqliteDb()
: _db(nullptr)
{
    
}

MWSqliteDb::~MWSqliteDb()
{
    if (_db)
    {
        g_dbCache.removeObjectForKey(_keyName);
        sqlite3_close(_db);
    }
}

MWSqliteDb *MWSqliteDb::openDb(const std::string &dbPath)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // assets is a zip file, so you can't locate to such file path.
    Data fileData = FileUtils::getInstance()->getDataFromFile(dbPath);
    string tmpPath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), "tmp");
    auto filePath = MWIOUtils::getInstance()->splicePath(tmpPath, dbPath);
    size_t found = filePath.find_last_of("/\\");
    string tmpFilename = filePath.substr(found + 1);
    MWIOUtils::getInstance()->createDirectory(filePath.substr(0, found + 1));
    if (!MWIOUtils::getInstance()->writeDataToFile(fileData.getBytes(), fileData.getSize(), filePath)) {
        return nullptr;
    }
#else
    std::string filePath = FileUtils::getInstance()->fullPathForFilename(dbPath.c_str());
#endif
    // check from cache.
    MWSqliteDb *pSqlite = nullptr;
    if (g_dbCache.hasKey(filePath)) {
        return (MWSqliteDb*)g_dbCache.objectForKey(filePath);
    } else {
        pSqlite = new (nothrow) MWSqliteDb();
        if (pSqlite && pSqlite->initWithFile(filePath)) {
            pSqlite->autorelease();
            g_dbCache.setObjectForKey(filePath, pSqlite);
            return pSqlite;
        }
        CC_SAFE_RELEASE(pSqlite);
        return nullptr;
    }
}

bool MWSqliteDb::initWithFile(const std::string &file)
{
    int res = sqlite3_open(file.c_str(), &_db);
    _keyName = file;
    if (res == SQLITE_OK)
    {
        return true;
    }
    else
    {
        CCLOG("Sqlite open db: %s failed. Error code: %d", file.c_str(), res);
        return false;
    }
}

void MWSqliteDb::clearConnectionCache()
{
    g_dbCache.clear();
}

MWArrayList *MWSqliteDb::executeQuery(const std::string &sql)
{
    auto result = MWArrayList::create();
    sqlite3_stmt *pStmt = nullptr;
    
    bool res = sqlite3_prepare(_db, sql.c_str(), -1, &pStmt, nullptr) == SQLITE_OK;
    if (res)
    {
        while (sqlite3_step(pStmt) == SQLITE_ROW)
        {
            auto columnDict = MWDictionary::create();
            int columnNum = sqlite3_column_count(pStmt);
            for (int i = 0; i < columnNum; ++i)
            {
                int type = sqlite3_column_type(pStmt, i);
                
                const char *szName = sqlite3_column_name(pStmt, i);
                Ref *pValue = nullptr;
                if (type == SQLITE_INTEGER)
                {
                    pValue = __Integer::create(sqlite3_column_int(pStmt, i));
                }
                else if (type == SQLITE_FLOAT)
                {
                    pValue = __Double::create(sqlite3_column_double(pStmt, i));
                }
                else if (type == SQLITE_TEXT)
                {
                    pValue = __String::create((const char*)sqlite3_column_text(pStmt, i));
                }
                else
                {
                    // unknown type?
                    CCLOG("Unknown sqlite3 type");
                    CC_SAFE_RELEASE(result);
                    return nullptr;
                }
                columnDict->setObjectForKey(szName, pValue);
            }
            result->appendObject(columnDict);
        }
        sqlite3_finalize(pStmt);
        
        return result;
    }
    CC_SAFE_RELEASE(result);
    return nullptr;
}

bool MWSqliteDb::executeNonQuery(const std::string &sql)
{
    char msg[1024] = { 0 };
    char *szErr = msg;
    int result = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &szErr);
    if (result != SQLITE_OK) {
        CCLOG("Sql execution failed, error code: %d, error message: %s\n", result, szErr);
    }
    return result == SQLITE_OK;
}

bool MWSqliteDb::beginTransaction()
{
    char msg[1024] = { 0 };
    char *szErr = msg;
    int result = sqlite3_exec(_db, "begin transaction", nullptr, nullptr, &szErr);
    if (result != SQLITE_OK) {
        CCLOG("Begin transaction failed, error code: %d, error message: %s\n", result, szErr);
        return false;
    }
    return true;
}

bool MWSqliteDb::endTransaction(bool sqlResult)
{
    char msg[1024] = { 0 };
    char *szErr = msg;
    if (sqlResult) {
        int result = sqlite3_exec(_db, "commit transaction", nullptr, nullptr, &szErr);
        if (result != SQLITE_OK) {
            CCLOG("Commit transaction failed, error code: %d, error message: %s\n", result, szErr);
            return false;
        }
    } else {
        int result = sqlite3_exec(_db, "rollback transaction", nullptr, nullptr, &szErr);
        if (result != SQLITE_OK) {
            CCLOG("Rollback transaction failed, error code: %d, error message: %s\n", result, szErr);
            return false;
        }
    }
    return true;
}

MW_FRAMEWORK_END