/******************************
 Description: Binary data, to save raw data and data size.
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __BASE_BINARY_DATA__
#define __BASE_BINARY_DATA__

#include "base/CCRef.h"
#include "FrameworkMacros.h"
#include "IUncopyable.h"
#include "IUninheritable.h"
#include <memory>

MW_FRAMEWORK_BEGIN

/**
 * Wrapper of binary data.
 */
class MW_DLL MWBinaryData : public cocos2d::Ref, MW_UNCOPYABLE, MW_UNINHERITABLE(MWBinaryData)
{
public:
    /**
     * Create binary data object.
     *
     * @param data Raw binary data.
     * @param size Binary data size.
     *
     * @return MWBinaryData instance which is autoreleased.
     */
    static MWBinaryData *create(MW_RAW_DATA data, MW_ULONG size);
    
    /**
     * BinaryData destructor.
     */
    virtual ~MWBinaryData();
    
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
    bool init(MW_RAW_DATA data, MW_ULONG size);
    
    MW_RAW_DATA _data;
    MW_ULONG _size;
};

MW_FRAMEWORK_END

#endif