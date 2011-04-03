// ======================================================================================
// File         : QuadTreeNode.h
// Author       : Wu Jie 
// Last Change  : 12/28/2009 | 17:18:16 PM | Monday,December
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef QUADTREENODE_H_1261991898
#define QUADTREENODE_H_1261991898
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

enum EQuadTreeNodeType
{
    eQuadTree_Unknown = -1, 
    eQuadTree_TL = 0,   // top-left
    eQuadTree_TR,       // top-right
    eQuadTree_BL,       // bottom-left
    eQuadTree_BR,       // bottom-right
    eQuadTree_Count, 
    eQuadTree_Root,     // root      
}; // end enum EQuadTreeNodeType

///////////////////////////////////////////////////////////////////////////////
// class TQuadTreeNode
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class TQuadTreeNode
{
    friend class TQuadTree<T>;

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef TQuadTree<T> qtree_t; 
    typedef TQuadTreeNode<T> node_t; 
    typedef TQuadTreeItem<T> item_t; 

    typedef Array<item_t> items_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    TQuadTreeNode ( rectf_t _rect = rectf_t(0.0f, 0.0f, 1.0f, 1.0f), EQuadTreeNodeType _nodeType = eQuadTree_Unknown );
    ~TQuadTreeNode ();
    
    // TODO: search item / get item
    // NOTE: can't use Items.empty() to judge if search deeper. We have situation that child have item but parent don't.

    //
    const node_t* SubNode( EQuadTreeNodeType _nodeType ) const;
    const rectf_t& Rect () const;
    EQuadTreeNodeType NodeType () const;

    // NOTE: returns the items in current node.
    item_t& Items();
    const item_t& Items() const;

    // NOTE: returns the items in current node and its sub-nodes.
    void AllItems( Array<T>* _pResult ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    node_t* CreateChild ( EQuadTreeNodeType _nodeType );
    void Return ();
    void clear ();

    // 
    node_t* insert ( const item_t& _item, uint _level );
    node_t* Update ( const item_t& _item, uint _level, node_t* _pRoot );
    result_t remove ( const T& _value );

    void Query ( const rectf_t& _rect, Array<T>* _pResult ) const;
    void Refresh ();

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    node_t* m_pParent;
    node_t* m_pSubNodes[eQuadTree_Count];

    rectf_t m_Rect; // The rectangle this node
    items_t m_Items;
    EQuadTreeNodeType   m_NodeType;

}; // end class TQuadTreeNode 

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END QUADTREENODE_H_1261991898
// #################################################################################


