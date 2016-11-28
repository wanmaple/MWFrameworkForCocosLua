#if CC_TARGET_PLATFORM == CC_TARGET_PLATFORM_IOS

#include "MWTcpSocket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define SOCKET_ERROR -1

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWTcpSocket *MWTcpSocket::create(int bindPort)
{
	auto ret = new (std::nothrow) MWTcpSocket();
	if (ret && ret->_init(bindPort))
	{
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

bool MWTcpSocket::_init(int bindPort)
{
	_sock = socket(AF_INET, SOCK_STREAM, 0);		// 0 indicates TCP/IP
	if (_sock == -1)
	{
		CCLOG("Socket create failed.");
		return false;
	}

	if (bindPort != 0 && !bind(bindPort))
	{
		return false;
	}

	_buffer = new char[1024];

	return true;
}

MWTcpSocket::MWTcpSocket()
: _connected(false)
, _sock(-1)
, _host("")
, _port(0)
, _buffer(nullptr)
{
}

MWTcpSocket::~MWTcpSocket()
{
	if (_connected)
	{
		close();
	}
	if (_buffer)
	{
		delete[] _buffer;
	}
}

bool MWTcpSocket::bind(int port)
{
	sockaddr_in addr;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	int opt = 1;
	if (::setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt)) < 0)
	{
		return false;
	}

	int err = ::bind(_sock, (const sockaddr *)&addr, sizeof(sockaddr));
	if (err == SOCKET_ERROR)
	{
		return false;
	}
	_bindPort = port;
	
	return true;
}

bool MWTcpSocket::connect(const std::string &host, int port)
{
	sockaddr_in addr;
	addr.sin_addr.s_addr = inet_addr(host.c_str());
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	int err = ::connect(_sock, (const sockaddr *)&addr, sizeof(sockaddr));
	if (err == SOCKET_ERROR)
	{
		_connected = false;
		_host = "";
		_port = 0;
		return false;
	}
	_connected = true;
	_host = host;
	_port = port;

	return true;
}

bool MWTcpSocket::listen(int count)
{
	int err = ::listen(_sock, count);
	if (err == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

int MWTcpSocket::send(MWBinaryData *data)
{
	int bytes, sent = 0;
	char *buf = (char *)data->getData();
	int len = data->getSize();
	while (sent < data->getSize())
	{
		bytes = ::send(_sock, buf + sent, len - sent, 0);
		if (bytes <= 0)
		{
			CCLOG("Socket data send failed. Sent bytes: %d, All bytes: %d", sent, len);
			break;
		}
		sent += bytes;
	}
	return sent;
}

MW_BYTE *MWTcpSocket::receive(MW_ULONG *size)
{
	int received = ::recv(_sock, _buffer, 1024, 0);
	if (received <= 0)
	{
		_connected = false;
		_host = "";
		_port = 0;
		CCLOG("Socket disconnected");
		return nullptr;
    }
    MW_BYTE *ret = (MW_BYTE *)malloc(received);
    memcpy(ret, _buffer, received);
    *size = received;
	// clear buffer.
	memset(_buffer, 0, received);
	return ret;
}

void MWTcpSocket::close()
{
	::close(_sock);
	_connected = false;
	_host = "";
	_port = 0;
}

MW_FRAMEWORK_END

#endif