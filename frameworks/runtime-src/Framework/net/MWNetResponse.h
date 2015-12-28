/******************************
 Description: Net response object
 Author: M.Wan
 Date: 3/14/2015
 ******************************/

#ifndef __NET_NET_RESPONSE__
#define __NET_NET_RESPONSE__

#include "../base/mwbase.h"

#include <string>

MW_FRAMEWORK_BEGIN

class MWNetRequest;

/**
 * Network response wrapper class.
 */
class MW_DLL MWNetResponse : public MWObject
{
public:
    /**
     * Create a new MWNetResponse.
     *
     * @param protocolId Protocol id.
     * @param body Request body.
     * @param request The request object related to the response.
     *
     * @return Return a new NetRequest object.
     */
    static MWNetResponse *create(const std::string &protocolId, const std::string &body, MWNetRequest *request);
    
    /**
     * NetResponse destructor.
     */
    virtual ~MWNetResponse();
    
    /**
     * Body, Protocol id getter and setter.
     */
    // MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _body, Body);
	MW_SYNTHESIZE(MWBinaryData *, _body, Body);
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _protocolId, ProtocolId);
    /**
     * Related request object getter.
     */
    MW_SYNTHESIZE_READONLY(MWNetRequest *, _relatedRequest, RelatedRequest);
    
protected:
    bool init(const std::string &protocolId, const std::string &body, MWNetRequest *request);
};

MW_FRAMEWORK_END

#endif
