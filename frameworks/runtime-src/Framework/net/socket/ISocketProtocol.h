/******************************
Description: Socket protocol.
Author: M.Wan
Date: 11/19/2016
******************************/

#ifndef __SOCKET_SOCKET_PROTOCOL__
#define __SOCKET_SOCKET_PROTOCOL__

#include "../../base/mwbase.h"

MW_FRAMEWORK_BEGIN

class MW_INTERFACE ISocketProtocol
{
public:
	virtual ~ISocketProtocol() {}

	virtual bool connect(const std::string &host, int port) = 0;
	virtual bool bind(int port) = 0;
	virtual bool listen(int count) = 0;
	virtual int send(MWBinaryData *data) = 0;
	virtual MW_BYTE *receive(MW_ULONG *size) = 0;
	virtual void close() = 0;
};

MW_FRAMEWORK_END

#endif