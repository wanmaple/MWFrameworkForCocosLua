/******************************
 Description: DB base.
 Author: M.Wan
 Date: 2/16/2015
 ******************************/

#ifndef __DB_DB_BASE__
#define __DB_DB_BASE__

#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * DB interfaces.
 */
class IDbBase
{
public:
    virtual ~IDbBase() {}
    
    /**
     * Execute query sql statement and return the selection.
     */
    virtual MWArrayList *executeQuery(const std::string &sql) = 0;
    /**
     * Execute non-query sql statement and return the execution result.
     */
    virtual bool executeNonQuery(const std::string &sql) = 0;
    /**
     * Begin transaction.
     */
    virtual bool beginTransaction() = 0;
    /**
     * End transaction with the specified execution result.
     */
    virtual bool endTransaction(bool sqlResult) = 0;
};

MW_FRAMEWORK_END

#endif
