/******************************
 Description: Net request object
 Author: M.Wan
 Date: 3/14/2015
 ******************************/

#ifndef __NET_NET_REQUEST__
#define __NET_NET_REQUEST__

#include "../base/mwbase.h"

#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Network request wrapper class.
 */
class MW_DLL MWNetRequest : public MWObject
{
public:
    /**
     * Create a new NetRequest.
     *
     * @param protocolId Protocol id.
     * @param body Request body.
     *
     * @return Return a new NetRequest object.
     */
    static MWNetRequest *create(const std::string &protocolId, const std::string &body);
    
    /**
     * NetRequest destructor.
     */
    virtual ~MWNetRequest();
    
    /**
     * Body, Protocol id getter and setter.
     */
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _body, Body);
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _protocolId, ProtocolId);
    
protected:
    bool init(const std::string &protocolId, const std::string &body);
};

MW_FRAMEWORK_END

#endif
