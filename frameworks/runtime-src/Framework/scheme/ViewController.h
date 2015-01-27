/******************************
 Description: UI view controller
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __SCHEME_VIEW_CONTROLLER__
#define __SCHEME_VIEW_CONTROLLER__

#include "base/CCRef.h"
#include "../base/Macros.h"
#include <string>

namespace mwframework {
    class IViewControllerDelegate
    {
    public:
        virtual ~IViewControllerDelegate() {}
        
        /**
         * Notified when the view is already loaded, do some ui initialization here.
         */
        virtual void viewDidLoad() = 0;
        virtual void viewWillAppear() = 0;
        virtual void viewDidAppear() = 0;
        virtual void viewWillDisappear() = 0;
        virtual void viewDidDisappear() = 0;
        virtual void viewDidUnload() = 0;
        virtual void didReceiveMemoryWarning() = 0;
    };
    
    class GameLayer;
    
    /**
     * Basic view controller of the framework.
     */
    class MWDLL ViewController : public cocos2d::Ref, public IViewControllerDelegate
    {
    public:
        /**
         * Create a view controller.
         *
         * @return GameScene instance which is autoreleased.
         */
        static ViewController *create();
        
        /**
         * Get related view.
         *
         * @return Related view of the view controller.
         */
        inline GameLayer *view() const
        {
            return _view;
        }
        
        inline std::string getIdentifier() const
        {
            return _identifer;
        }
        inline void setIdentifier(const std::string &identifier)
        {
            _identifer = identifier;
        }
        
        /**
         * IViewControllerDelegate overrides
         */
        virtual void viewDidLoad() override;
        virtual void viewWillAppear() override;
        virtual void viewDidAppear() override;
        virtual void viewWillDisappear() override;
        virtual void viewDidDisappear() override;
        virtual void viewDidUnload() override;
        virtual void didReceiveMemoryWarning() override;
        
    protected:
        virtual bool init();
        
        GameLayer *_view;
        std::string _identifer;
    };
}

#endif /* defined(__SCHEME_VIEW_CONTROLLER__) */
