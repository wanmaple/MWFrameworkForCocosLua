#include "MWLinkedList.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWLinkedList *MWLinkedList::create()
{
    auto pList = new (nothrow) MWLinkedList();
    if (pList) {
        pList->autorelease();
        return pList;
    }
    CC_SAFE_RELEASE(pList);
    return nullptr;
}

MWLinkedList::MWLinkedList()
: _innerList()
{
}

MWLinkedList::~MWLinkedList()
{
    this->clear();
}

MW_FRAMEWORK_END