#include "MWTcpService.h"

#include "MWTcpSocket.h"
#include "../MWNetRequest.h"
#include "../MWNetResponse.h"
#include "../MWNetCenter.h"

#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

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
	_protocolId = protocolId;
	_queue = MWQueue::create();
	CC_SAFE_RETAIN(_queue);

	_socket = MWTcpSocket::create(bindPort);
	if (!_socket)
	{
		return false;
	}
	CC_SAFE_RETAIN(_socket);

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
, _queue(nullptr)
{
}

MWTcpService::~MWTcpService()
{
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	if (_mutex)
	{
		pthread_mutex_destroy(&_mutex);
	}
	if (_socket)
	{
		_socket->close();
		_socket->release();
	}
	pthread_cancel(_pid);
	CC_SAFE_RELEASE(_queue);
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

	if (!_socket->connect(_host, _port))
	{
		CCLOG("Socket connect failed.");
		return false;
	}

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

	while (true)
	{
		if (!service->_socket)
		{
			break;
		}
		if (!service->_socket->isConnected())
		{
			// try reconnecting.
			int bindPort = service->_socket->getBindPort();
			service->_socket->release();
			service->_socket = MWTcpSocket::create(bindPort);
			if (service->_socket)
			{
				service->_socket->retain();
				if (service->_socket->connect(service->_host, service->_port)) {
					Director::getInstance()->getScheduler()->schedule([service](float dt) {
						string err = "tcp socket reconnected";
						auto response = MWNetResponse::create(service->_protocolId, MWBinaryData::create((MW_RAW_DATA)err.c_str(), err.size()), nullptr);
						MWNetCenter::getInstance()->dispatchFailedMessage(response);
					}, (void *)service, 0, 0, 0, false, "TCP_RECONNECT_MSG");
					retryCount = 0;
				}
			}
			++retryCount;

			if (retryCount >= 10)
			{
				// over the retry limit.
				Director::getInstance()->getScheduler()->schedule([service](float dt) {
					if (service->_socket == nullptr || !service->_socket->isConnected())
					{
						string err = "tcp socket disconnected";
						auto response = MWNetResponse::create(service->_protocolId, MWBinaryData::create((MW_RAW_DATA)err.c_str(), err.size()), nullptr);
						MWNetCenter::getInstance()->dispatchFailedMessage(response);
					}
				}, (void *)service, 0, 0, 0, false, "TCP_DISCONNECT_MSG");
				retryCount = 0;
			}

			continue;
		}

		MWBinaryData *data = service->_socket->receive();
		if (!data)
		{
			continue;
		}

		pthread_mutex_lock(&service->_mutex);
		service->_queue->enqueue(data);
		pthread_mutex_unlock(&service->_mutex);

		data->release();
	}

	return nullptr;
}

void MWTcpService::update(float dt)
{
	if (!_socket || !_socket->isConnected())
	{
		return;
	}

	while (!_queue->empty())
	{
		MWBinaryData *data = static_cast<MWBinaryData *>(_queue->front());
		_queue->dequeue();

		auto response = MWNetResponse::create(_protocolId, data, nullptr);
		MWNetCenter::getInstance()->dispatchSuccessfulMessage(response);
	}
}

MW_FRAMEWORK_END