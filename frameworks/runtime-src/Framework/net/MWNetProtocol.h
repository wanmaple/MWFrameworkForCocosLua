/******************************
 Description: Net protocol object
 Author: M.Wan
 Date: 3/14/2015
 ******************************/

#ifndef __NET_NET_PROTOCOL__
#define __NET_NET_PROTOCOL__

#include "../base/mwbase.h"

#include <string>

MW_FRAMEWORK_BEGIN

class MWNetHandler;

/**
 * Net protocol class, there is a unique service id for each network service and a protocol id for each service protocol. There also should own a handler to handle the network response for the protocol.
 */
class MW_DLL MWNetProtocol : public MWObject, public IUninheritable<MWNetProtocol>
{
public:
    /**
     * Create a new NetProtocol.
     *
     * @param protocolId Protocol id.
     * @param serviceId Service id.
     * @param handler Related net handler.
     *
     * @return Return a new NetProtocol object.
     */
    static MWNetProtocol *create(const std::string &protocolId, const std::string &serviceId, MWNetHandler *handler);
    
    /**
     * NetProtocol destructor.
     */
    virtual ~MWNetProtocol();
    
    /**
     * Protocol id, Service id getter and setter.
     */
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _serviceId, ServiceId);
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _protocolId, ProtocolId);
    /**
     * Related handler getter.
     */
    MW_SYNTHESIZE_READONLY(MWNetHandler *, _relatedHandler, RelatedHandler);
    
protected:
    bool init(const std::string &protocolId, const std::string &serviceId, MWNetHandler *handler);
};

MW_FRAMEWORK_END

#endif
