/******************************
 Description: Tree structure.
 Author: M.Wan
 Date: 2/2/2015
 ******************************/

#ifndef __BASE_TREE__
#define __BASE_TREE__

#include "MWObject.h"
#include "FrameworkMacros.h"
#include "ICloneable.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MWArrayList;

/**
 * Tree basic element.
 */
class MW_DEPRECATED MWTreeNode : public MWObject, public ICloneable<MWTreeNode>
{
    friend class MWTree;
public:
    /**
     * Create a tree node.
     *
     * @param obj Wrapped object.
     *
     * @return MWTreeNode instance which is autoreleased.
     */
    static MWTreeNode *create(cocos2d::Ref *obj);
    
    /**
     * MWTreeNode constructor.
     */
    MWTreeNode();
    /**
     * MWTreeNode destructor.
     */
    virtual ~MWTreeNode();
    
    /**
     * Get the parent node.
     */
    inline MWTreeNode *getParent()
    {
        return _parent;
    }
    /**
     * Get all children.
     */
    inline MWArrayList *getChildren()
    {
        return _children;
    }
    /**
     * Get wrapped object.
     */
    inline cocos2d::Ref *getObject()
    {
        return _obj;
    }
    
    /**
     * Retrieve child node whose value is equivalent to the specified value.
     * @note The operation won't retrieve the value recursively.
     *
     * @param obj Node value to retrieve.
     *
     * @return Child node whose object equals the specified one.
     */
    MWTreeNode *getChildNode(cocos2d::Ref *obj);
    
    /**
     * Set wrapped object.
     */
    void setObject(cocos2d::Ref *obj) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
    /**
     * Append a child node to the back.
     *
     * @param child Object to append.
     */
    void appendChild(cocos2d::Ref *child) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    /**
     * Append a child tree node to the back.
     *
     * @param child Tree node to append.
     */
    void appendNode(MWTreeNode *child) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
    /**
     * Remove the child node.
     *
     * @param child Object to remove.
     */
    bool removeChild(cocos2d::Ref *child);
    /**
     * Remove the child tree node.
     *
     * @param child Tree node to remove.
     */
    bool removeNode(MWTreeNode *child);
    
    /**
     * ICloneable overrides.
     */
    virtual MWTreeNode *clone() override;
    
protected:
    bool init(cocos2d::Ref *obj);
    
    cocos2d::Ref *_obj;
    MWTreeNode *_parent;
    MWArrayList *_children;
};

/**
 * Tree data structure.
 */
class MW_DEPRECATED MWTree : public cocos2d::Ref, public ICloneable<MWTree>
{
public:
    /**
     * Create a tree with specified wrapped object.
     *
     * @param obj Root wrapped object.
     *
     * @return MWTree instance which is autoreleased.
     */
    static MWTree *create(cocos2d::Ref *obj);
    /**
     * Create a tree with specified root node.
     *
     * @param root Root tree node.
     *
     * @return MWTree instance which is autoreleased.
     */
    static MWTree *createWithNode(MWTreeNode *root);
    
    /**
     * MWTree constructor.
     */
    MWTree();
    /**
     * MWTree constructor.
     */
    virtual ~MWTree();
    
    /**
     * Retrieve descendant node recursively.
     *
     * @param obj Wrapped value of the node to retrieve.
     *
     * @return Retrieved node.
     */
    MWTreeNode *getDescendantNode(cocos2d::Ref *obj);
    
    /**
     * Collect all nodes with preorder.
     *
     * @return The collection of all nodes in the tree.
     */
    MWArrayList *getAllNodes();
    
    /**
     * Get root node of the tree.
     */
    inline MWTreeNode *getRootNode()
    {
        return _root;
    }
    
    /**
     * Get the node count of the tree.
     */
    MW_UINT count();
    
    /**
     * ICloneable overrides.
     */
    virtual MWTree *clone() override;
    
protected:
    bool initWithNode(MWTreeNode *root);
    MWTreeNode *visitNode(MWTreeNode *parent, cocos2d::Ref *obj);
    void innerAddNodeToArray(MWTreeNode *node, MWArrayList *list);
    
    MWTreeNode *_root;
};

MW_FRAMEWORK_END

#endif /* defined(__BASE_TREE__) */
