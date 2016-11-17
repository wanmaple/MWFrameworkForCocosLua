/******************************
Description: Socket TCP service.
Author: M.Wan
Date: 11/17/2016
******************************/

#ifndef __SOCKET_TCP_SERVICE__
#define __SOCKET_TCP_SERVICE__

#include "../../base/mwbase.h"

#include "cocos2d.h"
#include "../MWNetService.h"
#include "network/SocketIO.h"

#define SOCKET_IO_PROTOCOL_ID "SOCKETIO"

MW_FRAMEWORK_BEGIN

class MWNetRequest;

class MW_DLL MWSocketIOService : public MWNetService, public cocos2d::network::SocketIO::SIODelegate
{
public:
	static MWSocketIOService *create(const std::string &serviceAddress);

	virtual ~MWSocketIOService();

	/**
	* NetService overrides.
	*/
	virtual void sendMessage(MWNetRequest *request);
	virtual void executeCommand(const std::string &cmd, cocos2d::Ref *param);

	/**
	* SIODelegate overrides.
	*/
	virtual void onConnect(cocos2d::network::SIOClient *client);
	virtual void onMessage(cocos2d::network::SIOClient *client, const std::string &data);
	virtual void onClose(cocos2d::network::SIOClient *client);
	virtual void onError(cocos2d::network::SIOClient *client, const std::string &data);
	virtual void fireEventToScript(cocos2d::network::SIOClient *client, const std::string &eventName, const std::string &data);

	MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _serviceAddr, getServiceAddress, setServiceAddress);

protected:
	MWSocketIOService();

	bool _init(const std::string &serviceAddress);

private:
	cocos2d::network::SIOClient *_socket;
};

MW_FRAMEWORK_END

#endif