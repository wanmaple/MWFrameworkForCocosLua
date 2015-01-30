#include "MWBinaryData.h"
#include "cocos2d.h"
#include <new>
#include <stdlib.h>
#include <string.h>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWBinaryData *MWBinaryData::create(MW_RAW_DATA data, MW_ULONG size)
{
    auto pData = new (nothrow) MWBinaryData();
    if (pData && pData->init(data, size))
    {
        pData->autorelease();
        return pData;
    }
    CC_SAFE_RELEASE(pData);
    return nullptr;
}

MWBinaryData::~MWBinaryData()
{
    if (_data)
    {
        free(_data);
    }
}

bool MWBinaryData::init(MW_RAW_DATA data, MW_ULONG size)
{
    // copy the data
    _data = (MW_ULONG*)malloc(size);
    memcpy(this->_data, data, size);
    _size = size;
    
    return true;
}

MW_RAW_DATA MWBinaryData::getData() const
{
    return _data;
}

MW_ULONG MWBinaryData::getSize() const
{
    return _size;
}

MW_FRAMEWORK_END