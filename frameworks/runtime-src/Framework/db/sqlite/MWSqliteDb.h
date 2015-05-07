/******************************
Description: Encapsulate sqlite3 operations.
Author: M.Wan
Date: 2/16/2015
******************************/

#ifndef __SQLITE_SQLITEDB__
#define __SQLITE_SQLITEDB__

#include "libsqlite/sqlite3.h"
#include "../../base/mwbase.h"
#include "../IDbBase.h"
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Sqlite db object.
 */
class MW_DLL MWSqliteDb : public MWObject, public IDbBase
{
public:
    virtual ~MWSqliteDb();
    
    /**
     * Open a sqlite3 db and return a db object.
     *
     * @param dbPath Db file path.
     *
     * @return SqliteDb object.
     */
    static MWSqliteDb *openDb(const std::string &dbPath);
    
    /**
     * Clear all connection cache.
     */
    static void clearConnectionCache();
    
    /**
     * IDbBase overrides.
     */
    MWArrayList *executeQuery(const std::string &sql) override;
    bool executeNonQuery(const std::string &sql) override;
    bool beginTransaction();
    bool endTransaction(bool result);
    
protected:
    bool initWithFile(const std::string &file);
    
    sqlite3 *_db;
    std::string _keyName;
};

MW_FRAMEWORK_END

#endif