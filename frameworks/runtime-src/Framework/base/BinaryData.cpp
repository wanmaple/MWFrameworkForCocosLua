#include "BinaryData.h"
#include "cocos2d.h"
#include <new>
#include <stdlib.h>
#include <string.h>

using namespace cocos2d;
using namespace std;

namespace mwframework
{
	BinaryData *BinaryData::create(void *data, MW_ULONG size)
	{
		auto pData = new (nothrow) BinaryData();
		if (pData && pData->init(data, size))
		{
			pData->autorelease();
			return pData;
		}
		CC_SAFE_RELEASE(pData);
		return nullptr;
	}

	BinaryData::~BinaryData()
	{
		if (_data)
		{
			free(_data);
		}
	}

	bool BinaryData::init(void *data, MW_ULONG size)
	{
		// copy the data
		_data = (MW_ULONG*)malloc(size);
		memcpy(this->_data, data, size);
		_size = size;

		return true;
	}

	void *BinaryData::getData() const
	{
		return _data;
	}

	MW_ULONG BinaryData::getSize() const
	{
		return _size;
	}
}