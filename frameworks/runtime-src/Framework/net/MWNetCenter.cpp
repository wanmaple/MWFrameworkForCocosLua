#include "MWNetCenter.h"

#include "MWNetRequest.h"
#include "MWNetResponse.h"
#include "MWNetService.h"
#include "MWNetHandler.h"
#include "MWNetFilter.h"
#include "MWNetProtocol.h"

using namespace std;

MW_FRAMEWORK_BEGIN

MWNetCenter::MWNetCenter()
: _serviceMap(new MWDictionary())
, _protocolMap(new MWDictionary())
, _filters(new MWArrayList())
{
}

MWNetCenter::~MWNetCenter()
{
    CC_SAFE_DELETE(_serviceMap);
    CC_SAFE_DELETE(_protocolMap);
    CC_SAFE_DELETE(_filters);
}

void MWNetCenter::sendMessage(mwframework::MWNetRequest *request)
{
    string protocolId = request->getProtocolId();
    MWNetProtocol *pProtocol = static_cast<MWNetProtocol*>(_protocolMap->objectForKey(protocolId));
    if (!pProtocol) {
        MW_THROW_EXCEPTION(5002);
    }
    MWNetService *pService = static_cast<MWNetService*>(_serviceMap->objectForKey(pProtocol->getServiceId()));
    if (!pService) {
        MW_THROW_EXCEPTION(5001);
    }
    pService->sendMessage(request);
}

void MWNetCenter::sendCommand(const std::string &serviceId, const std::string &cmd, cocos2d::Ref *params)
{
    MWNetService *pService = static_cast<MWNetService*>(_serviceMap->objectForKey(serviceId));
    if (!pService) {
        MW_THROW_EXCEPTION(5001);
    }
    pService->executeCommand(cmd, params);
}

void MWNetCenter::dispatchSuccessfulMessage(mwframework::MWNetResponse *response)
{
    if (!response) {
        MW_THROW_EXCEPTION(1006);
    }
    string protocolId = response->getProtocolId();
    MWNetProtocol *pProtocol = static_cast<MWNetProtocol*>(_protocolMap->objectForKey(protocolId));
    if (!pProtocol) {
        MW_THROW_EXCEPTION(5002);
    }
    // filter the response.
    MWNetFilter *pFilter = nullptr;
    for (MW_UINT i = 0; i < _filters->count(); ++i) {
        pFilter = static_cast<MWNetFilter*>(_filters->objectAtIndex(i));
        if (!pFilter) {
            MW_THROW_EXCEPTION(1010);
        }
        pFilter->filterSuccessfulMessage(response);
    }
    // handle the response.
    MWNetHandler *pHandler = pProtocol->getRelatedHandler();
    if (!pHandler) {
        MW_THROW_EXCEPTION(1010);
    }
    pHandler->handleSuccessfulMessage(response);
}

void MWNetCenter::dispatchFailedMessage(mwframework::MWNetResponse *response)
{
    if (!response) {
        MW_THROW_EXCEPTION(1006);
    }
    string protocolId = response->getProtocolId();
    MWNetProtocol *pProtocol = static_cast<MWNetProtocol*>(_protocolMap->objectForKey(protocolId));
    if (!pProtocol) {
        MW_THROW_EXCEPTION(5002);
    }
    // filter the response.
    MWNetFilter *pFilter = nullptr;
    for (MW_UINT i = 0; i < _filters->count(); ++i) {
        pFilter = static_cast<MWNetFilter*>(_filters->objectAtIndex(i));
        if (!pFilter) {
            MW_THROW_EXCEPTION(1010);
        }
        pFilter->filterFailedMessage(response);
    }
    // handle the response.
    MWNetHandler *pHandler = pProtocol->getRelatedHandler();
    if (!pHandler) {
        MW_THROW_EXCEPTION(1010);
    }
    pHandler->handleFailedMessage(response);
}

void MWNetCenter::addNetService(const std::string &serviceId, mwframework::MWNetService *service)
{
    if (serviceId.size() <= 0 || !service) {
        MW_THROW_EXCEPTION(1006);
    }
    if (_serviceMap->hasKey(serviceId)) {
        MW_THROW_EXCEPTION(5003);
    }
    _serviceMap->setObjectForKey(serviceId, service);
}

void MWNetCenter::removeNetService(const std::string &serviceId)
{
    if (serviceId.size() > 0) {
        _serviceMap->removeObjectForKey(serviceId);
    }
}

void MWNetCenter::addNetProtocol(const std::string &protocolId, const std::string &serviceId, mwframework::MWNetHandler *handler)
{
    if (protocolId.size() <= 0 || serviceId.size() <= 0 || !handler) {
        MW_THROW_EXCEPTION(1006);
    }
    if (!_serviceMap->hasKey(serviceId)) {
        MW_THROW_EXCEPTION(5001);
    }
    auto pProtocol = MWNetProtocol::create(protocolId, serviceId, handler);
    this->addNetProtocol(pProtocol);
}

void MWNetCenter::addNetProtocol(mwframework::MWNetProtocol *protocol)
{
    if (!protocol) {
        MW_THROW_EXCEPTION(1006);
    }
    MWNetService *pService = static_cast<MWNetService*>(_serviceMap->objectForKey(protocol->getServiceId()));
    if (!pService) {
        MW_THROW_EXCEPTION(5001);
    }
    // we allow duplicated protocol, so use carefully.
    _protocolMap->setObjectForKey(protocol->getProtocolId(), protocol);
}

void MWNetCenter::removeNetProtocol(const std::string &protocolId)
{
    if (protocolId.size() > 0) {
        _protocolMap->removeObjectForKey(protocolId);
    }
}

void MWNetCenter::addNetFilter(mwframework::MWNetFilter *filter)
{
    if (!filter) {
        MW_THROW_EXCEPTION(1006);
    }
    _filters->appendObject(filter);
}

void MWNetCenter::removeNetFilter(mwframework::MWNetFilter *filter)
{
    if (!filter) {
        MW_THROW_EXCEPTION(1006);
    }
    _filters->removeObject(filter);
}

void MWNetCenter::removeAllNetFilters()
{
    _filters->clear();
}

MW_FRAMEWORK_END