#include "MWSocketIOService.h"

#include "../MWNetRequest.h"
#include "../MWNetResponse.h"
#include "../MWNetCenter.h"

#include <new>

using namespace cocos2d;
using namespace cocos2d::network;
using namespace std;

MW_FRAMEWORK_BEGIN

MWSocketIOService *MWSocketIOService::create(const std::string &serviceAddress)
{
	auto ret = new (nothrow) MWSocketIOService();
	if (ret && ret->_init(serviceAddress))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

bool MWSocketIOService::_init(const std::string &serviceAddress)
{
	_serviceAddr = serviceAddress;

	_socket = SocketIO::connect(_serviceAddr, *this);
	if (_socket)
	{
		return true;
	}
	CC_SAFE_RELEASE_NULL(_socket);
	return false;
}

MWSocketIOService::MWSocketIOService()
: _socket(nullptr)
{
}

MWSocketIOService::~MWSocketIOService()
{
	if (_socket)
	{
		_socket->disconnect();
	}
	CC_SAFE_RELEASE(_socket);
}

void MWSocketIOService::sendMessage(MWNetRequest *request)
{
	MWBinaryData *msg = request->getBody();
	const char *binary = reinterpret_cast<const char *>(msg->getData());
	_socket->send(binary);
}

void MWSocketIOService::executeCommand(const std::string &cmd, cocos2d::Ref *param)
{
}

void MWSocketIOService::onConnect(cocos2d::network::SIOClient *client)
{
	CCLOG("Socket to %s is connected.", _serviceAddr.c_str());
}

void MWSocketIOService::onMessage(cocos2d::network::SIOClient *client, const std::string &data)
{
	MWBinaryData *binary = MWBinaryData::create((MW_RAW_DATA)data.c_str(), data.size());
	auto response = MWNetResponse::create(SOCKET_IO_PROTOCOL_ID, binary, nullptr);
	MWNetCenter::getInstance()->dispatchSuccessfulMessage(response);
}

void MWSocketIOService::onClose(cocos2d::network::SIOClient *client)
{
	CCLOG("Socket to %s is disconnected.", _serviceAddr.c_str());
}

void MWSocketIOService::onError(cocos2d::network::SIOClient *client, const std::string &data)
{
	MWBinaryData *binary = MWBinaryData::create((MW_RAW_DATA)data.c_str(), data.size());
	auto response = MWNetResponse::create(SOCKET_IO_PROTOCOL_ID, binary, nullptr);
	MWNetCenter::getInstance()->dispatchFailedMessage(response);
}

void MWSocketIOService::fireEventToScript(cocos2d::network::SIOClient *client, const std::string &eventName, const std::string &data)
{
	CCLOG("Socket to %s fire event %s to script. Data: %s", _serviceAddr.c_str(), eventName.c_str(), data.c_str());
}

MW_FRAMEWORK_END