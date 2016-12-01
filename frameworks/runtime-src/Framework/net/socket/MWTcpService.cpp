#include "MWTcpService.h"

#include "MWTcpSocket.h"
#include "../MWNetRequest.h"
#include "../MWNetResponse.h"
#include "../MWNetCenter.h"

#include <new>

#define DEFAULT_RETRY_COUNT 10

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

static volatile bool g_threadSignal = true;

MWTcpService *MWTcpService::create(const std::string &host, int port, const std::string &protocolId, int bindPort)
{
	auto ret = new (nothrow)MWTcpService();
	if (ret && ret->_init(host, port, protocolId, bindPort))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

bool MWTcpService::_init(const std::string &host, int port, const std::string &protocolId, int bindPort)
{
	_host = host;
	_port = port;
	_bindPort = bindPort;
	_protocolId = protocolId;
	g_threadSignal = true;

	if (!_connect())
	{
		return false;
	}

	return true;
}

MWTcpService::MWTcpService()
: _mutex()
, _pid()
, _host("")
, _port(0)
, _socket(nullptr)
{
}

MWTcpService::~MWTcpService()
{
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	pthread_mutex_destroy(&_mutex);
	if (_socket)
	{
		_socket->close();
		_socket->release();
	}
	g_threadSignal = false;
	//pthread_cancel(_pid);
}

void MWTcpService::sendMessage(MWNetRequest *request)
{
	if (_socket && _socket->isConnected())
	{
		_socket->send(request->getBody());
	}
}

void MWTcpService::executeCommand(const std::string &cmd, cocos2d::Ref *param)
{
	// Add user commands here.
}

bool MWTcpService::_connect()
{
	int err;

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

	// init mutex
	err = pthread_mutex_init(&_mutex, nullptr);
	if (err)
	{
		CCLOG("Mutex create failed. ERROR CODE: %d", err);
		return false;
	}

	// init thread
	pthread_attr_t attr;
	err = pthread_attr_init(&attr);
	if (err)
	{
		CCLOG("Socket thread create failed. ERROR CODE: %d", err);
		return false;
	}

	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (err)
	{
		CCLOG("Socket thread create failed. ERROR CODE: %d", err);
		pthread_attr_destroy(&attr);
		return false;
	}

	err = pthread_create(&_pid, &attr, &MWTcpService::_socketThread, this);
	if (err)
	{
		CCLOG("Socket thread create failed. ERROR CODE: %d", err);
		pthread_attr_destroy(&attr);
		return false;
	}

	return true;
}

void *MWTcpService::_socketThread(void *param)
{
	MWTcpService *service = (MWTcpService *)param;

	int retryCount = 0;

	while (g_threadSignal)
	{
		if (retryCount >= DEFAULT_RETRY_COUNT)
		{
			break;
		}
		if (!service->_socket)
		{
			service->_socket = MWTcpSocket::create(service->_bindPort);
			if (service->_socket)
			{
				if (service->_socket->connect(service->_host, service->_port))
				{
					Director::getInstance()->getScheduler()->schedule([service](float dt) {
						string err = "socket connected";
						auto response = MWNetResponse::create(service->_protocolId, MWBinaryData::create((MW_RAW_DATA)err.c_str(), err.size()), nullptr);
						MWNetCenter::getInstance()->dispatchFailedMessage(response);
					}, (void *)service, 0, 0, 0, false, "TCP_CONNECT_MSG");
				}
			}
		}
		if (!service->_socket->isConnected())
		{
			// try reconnecting.
			service->_socket->release();
			service->_socket = MWTcpSocket::create(service->_bindPort);
			if (service->_socket)
			{
				if (service->_socket->connect(service->_host, service->_port)) {
					retryCount = 0;
					Director::getInstance()->getScheduler()->schedule([service](float dt) {
						string err = "socket reconnected";
						auto response = MWNetResponse::create(service->_protocolId, MWBinaryData::create((MW_RAW_DATA)err.c_str(), err.size()), nullptr);
						MWNetCenter::getInstance()->dispatchFailedMessage(response);
					}, (void *)service, 0, 0, 0, false, "TCP_RECONNECT_MSG");
				}
			}
			++retryCount;

			if (retryCount >= DEFAULT_RETRY_COUNT)
			{
				// over the retry limit.
				Director::getInstance()->getScheduler()->schedule([service](float dt) {
					if (service->_socket == nullptr || !service->_socket->isConnected())
					{
						string err = "socket closed";
						auto response = MWNetResponse::create(service->_protocolId, MWBinaryData::create((MW_RAW_DATA)err.c_str(), err.size()), nullptr);
						MWNetCenter::getInstance()->dispatchFailedMessage(response);
					}
				}, (void *)service, 0, 0, 0, false, "TCP_CLOSE_MSG");
			}

			continue;
		}

		MW_ULONG size;
		MW_BYTE *data = service->_socket->receive(&size);
		if (!data)
		{
			Director::getInstance()->getScheduler()->schedule([service](float dt) {
				if (service->_socket == nullptr || !service->_socket->isConnected())
				{
					string err = "socket disconnected";
					auto response = MWNetResponse::create(service->_protocolId, MWBinaryData::create((MW_RAW_DATA)err.c_str(), err.size()), nullptr);
					MWNetCenter::getInstance()->dispatchFailedMessage(response);
				}
			}, (void *)service, 0, 0, 0, false, "TCP_DISCONNECT_MSG");
			continue;
		}

		pthread_mutex_lock(&service->_mutex);
		service->_queue.push(std::make_pair(data, size));
		pthread_mutex_unlock(&service->_mutex);
	}

	return nullptr;
}

void MWTcpService::update(float dt)
{
	if (!_socket || !_socket->isConnected())
	{
		return;
	}

	while (!_queue.empty())
	{
		pthread_mutex_lock(&_mutex);
		auto pair = _queue.front();
		_queue.pop();
		pthread_mutex_unlock(&_mutex);

		auto data = MWBinaryData::create(pair.first, pair.second);
		auto response = MWNetResponse::create(_protocolId, data, nullptr);
		MWNetCenter::getInstance()->dispatchSuccessfulMessage(response);

		free(pair.first);
	}
}

MW_FRAMEWORK_END