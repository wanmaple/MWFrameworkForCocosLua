#include "MWTree.h"
#include "MWArrayList.h"
#include "MWException.h"
#include "FrameworkErrors.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

/**
 * MWTreeNode implementation.
 */
MWTreeNode *MWTreeNode::create(cocos2d::Ref *obj)
{
    auto pNode = new (nothrow) MWTreeNode();
    if (pNode && pNode->init(obj)) {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_RELEASE(pNode);
    return nullptr;
}

bool MWTreeNode::init(cocos2d::Ref *obj)
{
    if (!obj) {
        return false;
    }
    _children = new (nothrow) MWArrayList();
    if (!_children) {
        return false;
    }
    this->setObject(obj);
    return true;
}

MWTreeNode::MWTreeNode()
: _obj(nullptr)
, _parent(nullptr)
, _children(nullptr)
{
    
}

MWTreeNode::~MWTreeNode()
{
    CC_SAFE_RELEASE(_obj);
    CC_SAFE_RELEASE(_children);
}

void MWTreeNode::setObject(cocos2d::Ref *obj) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check parameter.
    if (!obj) {
        MW_THROW_EXCEPTION(1006);
    }
    CC_SAFE_RELEASE(_obj);
    _obj = obj;
    CC_SAFE_RETAIN(obj);
}

void MWTreeNode::appendChild(cocos2d::Ref *child) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    this->appendChild(MWTreeNode::create(child));
}

void MWTreeNode::appendNode(mwframework::MWTreeNode *child) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check parameter.
    if (!child) {
        MW_THROW_EXCEPTION(1006);
    }
    _children->appendObject(child);
}

bool MWTreeNode::removeChild(cocos2d::Ref *child)
{
    if (!child) {
        return false;
    }
    MWTreeNode *pNode = nullptr;
    for (MW_UINT i = 0; i < _children->count(); ++i) {
        pNode = static_cast<MWTreeNode*>(_children->objectAtIndex(i));
        if (pNode->_obj == child) {
            return _children->removeObjectAtIndex(i);
        }
    }
    return false;
}

bool MWTreeNode::removeNode(mwframework::MWTreeNode *child)
{
    if (!child) {
        return false;
    }
    MWTreeNode *pNode = nullptr;
    for (MW_UINT i = 0; i < _children->count(); ++i) {
        pNode = static_cast<MWTreeNode*>(_children->objectAtIndex(i));
        if (pNode == child) {
            return _children->removeObjectAtIndex(i);
        }
    }
    return false;
}

MWTreeNode *MWTreeNode::getChildNode(cocos2d::Ref *obj)
{
    if (!obj) {
        return nullptr;
    }
    MWTreeNode *pNode = nullptr;
    for (MW_UINT i = 0; i < _children->count(); ++i) {
        pNode = static_cast<MWTreeNode*>(_children->objectAtIndex(i));
        if (pNode->_obj == obj) {
            return pNode;
        }
    }
    return nullptr;
}

MWTreeNode *MWTreeNode::clone()
{
    auto pCopy = MWTreeNode::create(_obj);
    if (pCopy) {
        MWTreeNode *pChild = nullptr;
        for (MW_UINT i = 0; i < _children->count(); ++i) {
            pChild = static_cast<MWTreeNode*>(_children->objectAtIndex(i));
            pChild = pChild->clone();
            pCopy->_children->appendObject(pChild);
        }
        pCopy->autorelease();
        return pCopy;
    }
    return nullptr;
}

/**
 * MWTree implementation.
 */
MWTree *MWTree::create(cocos2d::Ref *obj)
{
    return MWTree::createWithNode(MWTreeNode::create(obj));
}

MWTree *MWTree::createWithNode(mwframework::MWTreeNode *root)
{
    auto pTree = new (nothrow) MWTree();
    if (pTree && pTree->initWithNode(root)) {
        pTree->autorelease();
        return pTree;
    }
    CC_SAFE_RELEASE(pTree);
    return nullptr;
}

bool MWTree::initWithNode(mwframework::MWTreeNode *root)
{
    if (!root) {
        return false;
    }
    _root = root;
    root->retain();
    return true;
}

MWTree::MWTree()
: _root(nullptr)
{
    
}

MWTree::~MWTree()
{
    CC_SAFE_RELEASE(_root);
}

MWTreeNode *MWTree::getDescendantNode(cocos2d::Ref *obj)
{
    if (!obj) {
        return nullptr;
    }
    if (_root->_obj == obj) {
        return _root;
    }
    return this->visitNode(_root, obj);
}

MWTreeNode *MWTree::visitNode(mwframework::MWTreeNode *parent, cocos2d::Ref *obj)
{
    MWTreeNode *pNode = nullptr;
    MWTreeNode *pRes = nullptr;
    for (MW_UINT i = 0; i < parent->_children->count(); ++i) {
        pNode = static_cast<MWTreeNode*>(parent->_children->objectAtIndex(i));
        if (pNode->_obj == obj) {
            return pNode;
        }
        if ((pRes = this->visitNode(pNode, obj))) {
            return pRes;
        }
    }
    return nullptr;
}

MWArrayList *MWTree::getAllNodes()
{
    auto pNodes = MWArrayList::create();
    this->innerAddNodeToArray(_root, pNodes);
    return pNodes;
}

void MWTree::innerAddNodeToArray(mwframework::MWTreeNode *node, mwframework::MWArrayList *list)
{
    list->appendObject(node);
    MWTreeNode *pNode = nullptr;
    for (MW_UINT i = 0; i < node->_children->count(); ++i) {
        pNode = static_cast<MWTreeNode*>(node->_children->objectAtIndex(i));
        this->innerAddNodeToArray(pNode, list);
    }
}

MW_UINT MWTree::count()
{
    return this->getAllNodes()->count();
}

MWTree *MWTree::clone()
{
    auto pRootCopy = _root->clone();
    auto pCopy = MWTree::create(pRootCopy);
    if (pCopy) {
        pCopy->autorelease();
        return pCopy;
    }
    return nullptr;
}

MW_FRAMEWORK_END