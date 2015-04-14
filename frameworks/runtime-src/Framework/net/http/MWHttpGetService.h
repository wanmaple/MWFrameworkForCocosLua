/******************************
 Description: Http get service.
 Author: M.Wan
 Date: 03/18/2015
 ******************************/

#ifndef __HTTP_HTTP_GET_SERVICE__
#define __HTTP_HTTP_GET_SERVICE__

#include "../../base/mwbase.h"

#include "cocos2d.h"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "../MWNetService.h"
#include "MWHttpTransferStrategy.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MWNetRequest;
class MWHttpForm;

/**
 * Http get service.
 */
class MW_DLL MWHttpGetService : public MWNetService
{
public:
    /**
     * Create HttpGetService with specified service address.
     *
     * @param serviceAddress Service address.
     */
    static MWHttpGetService *create(const std::string &serviceAddress);
    
    /**
     * HttpGetService constructor.
     *
     * @param serviceAddress Service address.
     */
    explicit MWHttpGetService(const std::string &serviceAddress);
    /**
     * HttpGetService destructor.
     */
    virtual ~MWHttpGetService();
    
    /**
     * NetService overrides.
     */
    virtual void sendMessage(MWNetRequest *request);
    virtual void executeCommand(const std::string &cmd, cocos2d::Ref *param);
    
    /**
     * Get service address.
     */
    inline const std::string &getServiceAddress()
    {
        return _serviceAddr;
    }
    /**
     * Set service address.
     */
    inline void setServiceAddress(const std::string &serviceAddress)
    {
        _serviceAddr = serviceAddress;
    }
    
    /**
     * Set the rule of transfering.
     *
     * @param Transfer strategy.
     */
    inline void setTransferRule(MWHttpTransferStrategy *strategy)
    {
        _strategy = strategy;
    }
    
protected:
    bool _init(const std::string &serviceAddress);
    
    MWHttpForm *_createForm(const std::string &body);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
    
    std::string _serviceAddr;
    MWHttpTransferStrategy *_strategy;
};

MW_FRAMEWORK_END

#endif