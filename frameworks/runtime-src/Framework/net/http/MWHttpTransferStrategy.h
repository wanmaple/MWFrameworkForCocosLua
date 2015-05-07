/******************************
 Description: Transfer rule in http.
 Author: M.Wan
 Date: 03/18/2015
 ******************************/

#ifndef __HTTP_HTTPTRANSFERSTRATEGY__
#define __HTTP_HTTPTRANSFERSTRATEGY__

#include "../../base/mwbase.h"
#include <string>
#include <map>

MW_FRAMEWORK_BEGIN

/**
 * Tell me how to transfer parameters to http.
 */
class MW_INTERFACE MWHttpTransferStrategy
{
public:
    /**
     * HttpTransferStrategy destructor.
     */
    virtual ~MWHttpTransferStrategy() {}
    
    /**
     * How to get url parameters to transfer based on your rule?
     *
     * @return The mapping of your transfer parameters in http.
     */
    virtual std::map<std::string, std::string> transferParameters(const std::string &body) = 0;
};

MW_FRAMEWORK_END

#endif
