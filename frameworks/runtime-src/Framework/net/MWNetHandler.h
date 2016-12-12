/******************************
 Description: Net handler base.
 Author: M.Wan
 Date: 3/14/2015
 ******************************/

#ifndef __NET_NET_HANDLER__
#define __NET_NET_HANDLER__

#include "../base/mwbase.h"

#include <string>

MW_FRAMEWORK_BEGIN

class MWNetResponse;

/**
 * A handler class to handle the network response.
 */
class MW_DLL MWNetHandler : public MWObject
{
public:
    /**
     * Create a NetHandler object.
     * @note This method is just for script. Please don't create it in cpp.
     */
    static MWNetHandler *create();
    
    /**
     * MWNetHandler destructor.
     */
    virtual ~MWNetHandler() {}
    
    /**
     * Protocols about how to handle successful/failed message.
     */
    virtual void handleSuccessfulMessage(MWNetResponse *response);
    virtual void handleFailedMessage(MWNetResponse *response);

protected:
	MWNetHandler() {}
};

MW_FRAMEWORK_END

#endif
