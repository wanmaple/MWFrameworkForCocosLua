/******************************
 Description: Net filter base.
 Author: M.Wan
 Date: 3/14/2015
 ******************************/

#ifndef __NET_NET_FILTER__
#define __NET_NET_FILTER__

#include "../base/mwbase.h"

#include <string>

MW_FRAMEWORK_BEGIN

class MWNetResponse;

/**
 * A filter class to filter the network response.
 */
class MW_DLL MWNetFilter : public MWObject
{
public:
    /**
     * Create a NetFilter object.
     * @note This method is just for script. Please don't create it in cpp.
     */
    static MWNetFilter *create();
    
    /**
     * MWNetHandler destructor.
     */
    virtual ~MWNetFilter() {}
    
    /**
     * Protocols about how to filter successful/failed message.
     */
    virtual void filterSuccessfulMessage(MWNetResponse *response);
    virtual void filterFailedMessage(MWNetResponse *response);
};

MW_FRAMEWORK_END

#endif
