/******************************
Description: Socket on win32 platform.
Author: M.Wan
Date: 11/19/2016
******************************/

#ifndef __SOCKET_TCP_SOCKET__
#define __SOCKET_TCP_SOCKET__

#include "ISocketProtocol.h"
#include <pthread.h>
#include <semaphore.h>
#include <string>

MW_FRAMEWORK_BEGIN

class MW_DLL MWTcpSocket : public cocos2d::Ref, public ISocketProtocol
{
public:
	/**
	* The object created won't be autoreleased. (Take care)
	*/
	static MWTcpSocket *create(int bindPort = 0);

	~MWTcpSocket();

	MW_SYNTHESIZE_READONLY(int, _bindPort, getBindPort);
	MW_SYNTHESIZE_READONLY(std::string, _host, getHost);
	MW_SYNTHESIZE_READONLY(int, _port, getPort);
	MW_SYNTHESIZE_READONLY(bool, _connected, isConnected);

	/**
	* Overrides
	*/
	bool connect(const std::string &host, int port) override;
	bool bind(int port) override;
	bool listen(int count) override;
	int send(MWBinaryData *data) override;
	MW_BYTE *receive(MW_ULONG *size) override;
	void close() override;

private:
	MWTcpSocket();

	bool _init(int bindPort);

	int _sock;		// socket handle

	char *_buffer;
};

MW_FRAMEWORK_END

#endif