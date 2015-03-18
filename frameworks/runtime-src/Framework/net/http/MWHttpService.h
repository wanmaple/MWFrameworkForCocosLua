/******************************
 Description: Http service.
 Author: M.Wan
 Date: 03/18/2015
 ******************************/

#ifndef __HTTP_HTTPSERVICE__
#define __HTTP_HTTPSERVICE__

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
 * Http service.
 */
class MW_DLL MWHttpService : public MWNetService
{
public:
    /**
     * Create HttpService with specified service address.
     *
     * @param serviceAddress Service address.
     */
    static MWHttpService *create(const std::string &serviceAddress);
    
    /**
     * HttpService constructor.
     *
     * @param serviceAddress Service address.
     */
    explicit MWHttpService(const std::string &serviceAddress);
    /**
     * HttpService destructor.
     */
    virtual ~MWHttpService();
    
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