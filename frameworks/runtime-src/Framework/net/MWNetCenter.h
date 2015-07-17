/******************************
 Description: Net center.
 Author: M.Wan
 Date: 3/14/2015
 ******************************/

#ifndef __NET_NET_CENTER__
#define __NET_NET_CENTER__

#include "../base/mwbase.h"

#include <string>

MW_FRAMEWORK_BEGIN

class MWNetRequest;
class MWNetResponse;
class MWNetService;
class MWNetHandler;
class MWNetFilter;
class MWNetProtocol;

class MW_DLL MWNetCenter : public MWObject
{
    MW_SINGLETON(MWNetCenter);
public:
    /**
     * NetCenter destructor.
     */
    ~MWNetCenter();
    
    /**
     * Send request to the server.
     *
     * @param request The request to send.
     */
    void sendMessage(MWNetRequest *request);
    /**
     * Execute specified command.
     *
     * @param serviceId Service id.
     * @param cmd Command name.
     * @param params Command parameters.
     */
    void sendCommand(const std::string &serviceId, const std::string &cmd, cocos2d::Ref *params);
    
    /**
     * Dispatch the successful response.
     *
     * @param response Returned response from the server.
     */
    void dispatchSuccessfulMessage(MWNetResponse *response);
    /**
     * Dispatch the failed response.
     *
     * @param response Returned response from the server.
     */
    void dispatchFailedMessage(MWNetResponse *response);
    
    /**
     * Add a new net service.
     *
     * @param serviceId Service id to add.
     * @param service Service object.
     */
    void addNetService(const std::string &serviceId, MWNetService *service);
    /**
     * Remove net service.
     *
     * @param serviceId Service id to remove.
     */
    void removeNetService(const std::string &serviceId);
    
    /**
     * Add a new net protocol.
     *
     * @param protocolId Protocol id.
     * @param serviceId Which service id to add.
     * @param handler Related net handler.
     */
    void addNetProtocol(const std::string &protocolId, const std::string &serviceId, MWNetHandler *handler);
    /**
     * Add a new net protocol.
     *
     * @param protocol Protocol object.
     */
    void addNetProtocol(MWNetProtocol *protocol);
    /**
     * Remove the specified protocol.
     *
     * @param protocolId Protocol id to remove.
     */
    void removeNetProtocol(const std::string &protocolId);
    
    /**
     * Add a new net filter.
     *
     * @param filter Filter to add.
     */
    void addNetFilter(MWNetFilter *filter);
    /**
     * Remove net filter.
     *
     * @param filter Filter to remove.
     */
    void removeNetFilter(MWNetFilter *filter);
    /**
     * Remove all filters.
     */
    void removeAllNetFilters();
    
protected:
    MWDictionary *_serviceMap;
    MWDictionary *_protocolMap;
    MWArrayList *_filters;
};

MW_FRAMEWORK_END

#endif
