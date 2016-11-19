/******************************
Description: Socket TCP service.
Author: M.Wan
Date: 11/19/2016
******************************/

#ifndef __SOCKET_TCP_SERVICE__
#define __SOCKET_TCP_SERVICE__

#include "../../base/mwbase.h"
#include "cocos2d.h"
#include "../MWNetService.h"
#include <pthread.h>

#define TCP_SOCKET_PROTOCOL_ID "TCP_SOCKET"

MW_FRAMEWORK_BEGIN

class MWNetRequest;
class MWTcpSocket;

class MW_DLL MWTcpService : public MWNetService
{
public:
	static MWTcpService *create(const std::string &host, int port, const std::string &protocolId = TCP_SOCKET_PROTOCOL_ID, int bindPort = 4000);

	~MWTcpService();

	MW_SYNTHESIZE_READONLY(std::string, _host, getHost);
	MW_SYNTHESIZE_READONLY(int, _port, getPort);

	void update(float dt);

	/**
	* NetService overrides.
	*/
	virtual void sendMessage(MWNetRequest *request);
	virtual void executeCommand(const std::string &cmd, cocos2d::Ref *param);

protected:
	static void *_socketThread(void *param);

	MWTcpService();

	bool _init(const std::string &host, int port, const std::string &protocolId, int bindPort);

	bool _connect();

	std::string _protocolId;

	MWTcpSocket *_socket;
	MWQueue *_queue;

	pthread_t _pid;
	pthread_mutex_t _mutex;
};

MW_FRAMEWORK_END

#endif