/******************************
 Description: Net service base
 Author: M.Wan
 Date: 3/14/2015
 ******************************/

#ifndef __NET_NET_SERVICE__
#define __NET_NET_SERVICE__

#include "../base/mwbase.h"
#include "base/CCRef.h"

MW_FRAMEWORK_BEGIN

class MWNetRequest;

class MWNetService : public cocos2d::Ref
{
public:
    virtual ~MWNetService() {}
    
    /**
     * Send request to the server.
     *
     * @param request The request to send.
     */
    virtual void sendMessage(MWNetRequest *request) = 0;
    
    /**
     * Execute extra command.
     *
     * @param cmd Command name.
     * @param params Command parameters.
     */
    virtual void executeCommand(const std::string &cmd, cocos2d::Ref *params) = 0;
};

MW_FRAMEWORK_END

#endif
