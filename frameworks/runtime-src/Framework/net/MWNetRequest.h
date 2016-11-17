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
    static MWNetRequest *create(const std::string &protocolId, MWBinaryData *body);
    
    /**
     * NetRequest destructor.
     */
    virtual ~MWNetRequest();
    
    /**
     * Body, Protocol id getter and setter.
     */
	MW_SYNTHESIZE(MWBinaryData *, _body, getBody, setBody);
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _protocolId, getProtocolId, setProtocolId);
    
protected:
	bool init(const std::string &protocolId, MWBinaryData *body);
};

MW_FRAMEWORK_END

#endif
