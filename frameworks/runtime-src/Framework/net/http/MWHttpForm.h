/******************************
 Description: Http form to commit.
 Author: M.Wan
 Date: 03/18/2015
 ******************************/

#ifndef __HTTP_HTTPFORM__
#define __HTTP_HTTPFORM__

#include "../../base/mwbase.h"
#include <string>
#include <map>

MW_FRAMEWORK_BEGIN

/**
 * Http form object.
 */
class MW_DLL MWHttpForm : public MWObject
{
public:
    /**
     * HttpForm destructor.
     */
    ~MWHttpForm();
    
    /**
     * Create http form object.
     */
    static MWHttpForm *create();
    
    /**
     * Add new parameter to the form.
     *
     * @param paramName Name of parameter.
     * @param paramValue Value of parameter.
     */
    void putParam(const std::string &paramName, const std::string &paramValue);
    /**
     * Get the specified parameter value.
     *
     * @param paramName Name of parameter to get.
     */
    const char *getParam(const std::string &paramName);
    /**
     * Remove the specified parameter.
     *
     * @param paramName Name of parameter to get.
     */
    void removeParam(const std::string &paramName);
    
    /**
     * Convert object to connection string.
     *
     * @return String connected with parameters.
     */
    virtual std::string toString() override;
    
protected:
	MWHttpForm() {}

    bool _init();
    
    unsigned char toHex(unsigned char x);
    unsigned char fromHex(unsigned char x);
    std::string urlEncode(const std::string &str);
    std::string urlDecode(const std::string &str);
    
    std::map<std::string, std::string> _params;
};

MW_FRAMEWORK_END

#endif
