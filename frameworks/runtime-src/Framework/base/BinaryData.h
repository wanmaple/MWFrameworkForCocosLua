/******************************
Description: Binary data, to save raw data and data size.
Author: M.Wan
Date: 1/28/2015
******************************/

#ifndef __BASE_BINARY_DATA__
#define __BASE_BINARY_DATA__

#include "base/CCRef.h"
#include "Macros.h"
#include "IUncopyable.h"
#include "IUninheritable.h"
#include <memory>

namespace mwframework
{
	/**
     * Wrapper of binary data.
     */
	class MWDLL BinaryData : public cocos2d::Ref, private IUncopyable, public IUninheritable<BinaryData>
	{
	public:
		/**
         * Create binary data object.
         *
         * @param data Raw binary data.
         * @param size Binary data size.
         *
         * @return BinaryData instance which is autoreleased.
         */
		static BinaryData *create(void *data, MW_ULONG size);

		/**
		* BinaryData destructor.
		*/
		virtual ~BinaryData();

		/**
		* Get raw data.
		*
		* @return Raw data.
		*/
		void *getData() const;
		/**
		* Get data size.
		*
		* @return Data size.
		*/
		MW_ULONG getSize() const;

	private:
		bool init(void *data, MW_ULONG size);

		void *_data;
		MW_ULONG _size;
	};
}

#endif