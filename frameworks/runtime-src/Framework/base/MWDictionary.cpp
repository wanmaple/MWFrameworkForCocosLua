#include "MWDictionary.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace mwframework {
    
    MWDictionary *MWDictionary::create()
    {
        auto pDict = new (nothrow) MWDictionary();
        if (pDict) {
            pDict->autorelease();
            return pDict;
        }
        CC_SAFE_RELEASE(pDict);
        return nullptr;
    }
    
    MWDictionary::MWDictionary()
    : _innerMap()
    {
        
    }
    
    MWDictionary::~MWDictionary()
    {
        this->clear();
    }
}