// ======================================================================================
// File         : QuadTreeItem.h
// Author       : Wu Jie 
// Last Change  : 12/28/2009 | 17:19:14 PM | Monday,December
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef QUADTREEITEM_H_1261991956
#define QUADTREEITEM_H_1261991956
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class TQuadTreeItemBase 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class TQuadTreeItemBase
{
    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    TQuadTreeItemBase ( const T& _value )
        : m_Item (_value) 
    {
    }

    TQuadTreeItemBase ( const T& _value, const rectf_t& _rect )
        : m_Item (_value) 
        , m_ItemRect(_rect)
    {
    }

    ~TQuadTreeItemBase () {}

    INLINE void SetRect ( const rectf_t& _rect ) { m_ItemRect = _rect; }
    INLINE const rectf_t& Rect () const { return m_ItemRect; }

    T& value () { return m_Item; }
    const T& value () const { return m_Item; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    T m_Item;
    rectf_t m_ItemRect;

}; // end class TQuadTreeItemBase

///////////////////////////////////////////////////////////////////////////////
// class TQuadTreeItem 
// 
// Purpose: 
//  NOTE: you can specialize the class to fit the interface for your wrap class 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class TQuadTreeItem : public TQuadTreeItemBase<T>
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef TQuadTreeItemBase<T> base_t;
    typedef TQuadTree<T> qtree_t;
    typedef TQuadTreeNode<T> node_t;
    typedef TQuadTreeItem<T> item_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    TQuadTreeItem ( const T& _value, const qtree_t& _qtree );
    ~TQuadTreeItem ();

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

}; // end class CQuadTreeItem

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END QUADTREEITEM_H_1261991956
// #################################################################################


