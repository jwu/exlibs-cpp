// ======================================================================================
// File         : QuadTreeNode.hpp
// Author       : Wu Jie 
// Last Change  : 12/29/2009 | 14:22:28 PM | Tuesday,December
// Description  : 
// ======================================================================================

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// macro defines
///////////////////////////////////////////////////////////////////////////////

#define qtree_t typename TQuadTreeNode<T>::qtree_t
#define node_t typename TQuadTreeNode<T>::node_t
#define item_t typename TQuadTreeNode<T>::item_t
#define items_t typename TQuadTreeNode<T>::items_t

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
TQuadTreeNode<T>::TQuadTreeNode ( rectf_t _rect, EQuadTreeNodeType _nodeType )
    : m_pParent (NULL)
    , m_Rect (_rect)
    , m_NodeType (_nodeType)
{
    for ( uint i = 0; i < eQuadTree_Count; ++i )
        m_pSubNodes[i] = NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
TQuadTreeNode<T>::~TQuadTreeNode ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
const node_t* TQuadTreeNode<T>::SubNode( EQuadTreeNodeType _nodeType ) const
{
    return m_pSubNodes[_nodeType];
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
const rectf_t& TQuadTreeNode<T>::Rect () const
{
    return m_Rect;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
EQuadTreeNodeType TQuadTreeNode<T>::NodeType () const
{
    return m_NodeType;
}

///////////////////////////////////////////////////////////////////////////////
// protected
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
node_t* TQuadTreeNode<T>::insert ( const item_t& _item, uint _level )
{
    int node_width = (int)m_Rect.width();
    int node_height = (int)m_Rect.height();

    int half_width = node_width>>1;
    int half_height = node_height>>1;

    // if our _level count to zero, or current cell rect size is 1, then item to current node and return.
    if ( _level == 0 || half_width == 0 )
    {
        m_Items.push_back(_item);
        return this;
    }

    vec2f_t center ( m_Rect.left() + half_width, m_Rect.top() + half_height );
    const rectf_t& itRect = _item.Rect(); 
    float itLeft = itRect.left();
    float itRight = itRect.right();
    float itTop = itRect.top();
    float itBot = itRect.bot();

    // check position
    EQuadTreeNodeType nodeType = eQuadTree_Unknown;
    if ( itRight <= center.x() && itBot <= center.y() )
    {
        nodeType = eQuadTree_TL;
    }
    else if ( itLeft >= center.x() && itBot <= center.y() )
    {
        nodeType = eQuadTree_TR;
    }
    else if ( itRight <= center.x() && itTop >= center.y() )
    {
        nodeType = eQuadTree_BL;
    }
    else if ( itLeft >= center.x() && itTop >= center.y() )
    {
        nodeType = eQuadTree_BR;
    }

    // if the item across center-lines, insert it to current item-list.
    if ( nodeType == eQuadTree_Unknown )
    {
        m_Items.push_back (_item);
        return this;
    }
    else // else put it to the fitting node so that it will recursively process space partition.
    {
        if ( !m_pSubNodes[nodeType] )
            m_pSubNodes[nodeType] = CreateChild( nodeType );

        return m_pSubNodes[nodeType]->insert(_item,_level-1);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
node_t* TQuadTreeNode<T>::Update ( const item_t& _item, uint _level, node_t* _pRoot )
{
    // find and remove the item in item list
    items_t::iterator iter;
    for ( iter = m_Items.begin(); iter != m_Items.end(); ++iter )
    {
        if ( (*iter).value() == _item.value() )
        {
            break;
        }
    }
    if ( iter == m_Items.end() )
    {
        return NULL;
    }

    // case 1: if the rect contains the item, call insert 
    if ( Rect().contains( _item.Rect() ) )
    {
        int node_width = (int)m_Rect.width();
        int node_height = (int)m_Rect.height();

        int half_width = node_width>>1;
        int half_height = node_height>>1;

        vec2f_t center ( m_Rect.left() + half_width, m_Rect.top() + half_height );
        const rectf_t& itRect = _item.Rect(); 
        float itLeft = itRect.left();
        float itRight = itRect.right();
        float itTop = itRect.top();
        float itBot = itRect.bot();


        // check position
        EQuadTreeNodeType nodeType = eQuadTree_Unknown;
        if ( itRight <= center.x() && itBot <= center.y() )
        {
            nodeType = eQuadTree_TL;
        }
        else if ( itLeft >= center.x() && itBot <= center.y() )
        {
            nodeType = eQuadTree_TR;
        }
        else if ( itRight <= center.x() && itTop >= center.y() )
        {
            nodeType = eQuadTree_BL;
        }
        else if ( itLeft >= center.x() && itTop >= center.y() )
        {
            nodeType = eQuadTree_BR;
        }

        // case 1.1: if the item across center-lines, or if the level reach to 0 upate current item
        if ( nodeType == eQuadTree_Unknown || _level == 0 )
        {
            *iter = _item;
            return this;
        }
        // case 1.2: if the item contains by child, erase the item and put it to the child
        else 
        {
            m_Items.erase(iter);
            if ( !m_pSubNodes[nodeType] )
                m_pSubNodes[nodeType] = CreateChild( nodeType );

            return m_pSubNodes[nodeType]->insert(_item,_level-1);
        }
    }

    // case 2: if the item not belong to current node.
    // erase the item, return the root node so that the tree can re-insert it from the root
    else
    {
        m_Items.erase(iter);
        Refresh();
        return _pRoot;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t TQuadTreeNode<T>::remove ( const T& _value )
{
    // find and remove the item in item list
    bool bFound = false;
    for ( items_t::iterator iter = m_Items.begin(); iter != m_Items.end(); ++iter )
    {
        if ( (*iter).value() == _value )
        {
            bFound = true;
            m_Items.erase(iter);
            break;
        }
    }
    if ( !bFound )
    {
        return EResult::not_found; 
    }

    // refresh the node
    Refresh ();
    return EResult::ok; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTreeNode<T>::Query ( const rectf_t& _rect, Array<T>* _pResult ) const
{
    for ( items_t::c_iterator iter = m_Items.begin(); iter != m_Items.end(); ++iter )
    {
        if ( intersect::rect_rect( _rect, (*iter).Rect() ) )
            _pResult->push_back( (*iter).value() );
    }

    for ( int i = 0; i < eQuadTree_Count; ++i )
    {
        // if the node not exists, skip it
        if ( m_pSubNodes[i] == NULL )
            continue;

        // case 1: search area completely contained by sub-node 
        // if a node completely contains the query area, go down that branch and skip the remainning nodes (break this loop)
        if ( m_pSubNodes[i]->Rect().contains(_rect) )
        {
            m_pSubNodes[i]->Query( _rect, _pResult );
            break;
        }

        // case 2: sub-node completely contained by search area
        // if the query area completely contains a sub-node, just add all the contents of that node and its children to the result. 
        // you nee to continue loop to test the other nodes.
        if ( _rect.contains( m_pSubNodes[i]->Rect() ) )
        {
            m_pSubNodes[i]->AllItems(_pResult);
            continue;
        }

        // case 3: search area intersects with sub-node
        // traverse into this node, continue the loop to search other nodes.
        if ( intersect::rect_rect( _rect, m_pSubNodes[i]->Rect() ) )
        {
            m_pSubNodes[i]->Query( _rect, _pResult );
        }
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTreeNode<T>::Refresh ()
{
    if ( m_NodeType == eQuadTree_Root )
        return;

    // if the node doesn't contains any item, and if it dosen't have any sub-nodes, return it!
    if ( m_Items.empty() )
    {
        bool has_subnode = false;
        for ( int i = 0; i < eQuadTree_Count; ++i )
        {
            if ( m_pSubNodes[i] )
            {
                has_subnode = true;
                break;
            }
        }

        //
        if ( !has_subnode )
        {
            node_t* pParent = m_pParent;
            Return ();
            pParent->Refresh();
        }
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
node_t* TQuadTreeNode<T>::CreateChild ( EQuadTreeNodeType _nodeType )
{
    node_t* pChild = TQuadTree<T>::RequestNode();
    pChild->m_pParent = this;
    pChild->m_NodeType = _nodeType; 

    //
    int node_width = (int)m_Rect.width();
    int node_height = (int)m_Rect.height();

    int half_width = node_width>>1;
    int half_height = node_height>>1;
    float left = m_Rect.left();
    float top = m_Rect.top();

    if ( _nodeType == eQuadTree_TR )
    {
        left += half_width;
    }
    else if ( _nodeType == eQuadTree_BL )
    {
        top += half_height;
    }
    else if ( _nodeType == eQuadTree_BR )
    {
        left += half_width;
        top += half_height;
    }

    pChild->m_Rect.set( left, top, left + half_width, top + half_height );

    return pChild;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTreeNode<T>::Return ()
{
    // return four children.
    for ( uint i = 0; i < eQuadTree_Count; ++i )
    {
        if ( m_pSubNodes[i] )
            m_pSubNodes[i]->Return(); 
    }

    // find node in parent, de-ref it.
    if ( m_pParent )
    {
        m_pParent->m_pSubNodes[m_NodeType] = NULL;
        m_pParent = NULL;
    }

    // check if we still have item in it.
    ex_assert ( m_Items.empty(), "the node still contain item, it can't be return. something goes wrong!" );
    m_Items.clear(); 

    // reset the node type, rect size
    m_NodeType = eQuadTree_Unknown;
    m_Rect.set ( 0.0f, 0.0f, 1.0f, 1.0f );

    //
    TQuadTree<T>::ReturnNode(this);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTreeNode<T>::clear ()
{
    // clear items in children.
    for ( uint i = 0; i < eQuadTree_Count; ++i )
    {
        if ( m_pSubNodes[i] )
            m_pSubNodes[i]->clear(); 
    }

    m_Items.clear();
    Return();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
item_t& TQuadTreeNode<T>::Items()
{
    return m_Items;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
const item_t& TQuadTreeNode<T>::Items() const
{
    return m_Items;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTreeNode<T>::AllItems( Array<T>* _pResult ) const
{
    //
    for ( typename Array<item_t>::c_iterator iter = m_Items.begin(); iter != m_Items.end(); ++iter )
    {
        _pResult->push_back( (*iter).value() );
    }

    //
    for ( int i = 0; i < eQuadTree_Count; ++i )
    {
        if ( m_pSubNodes[i] == NULL )
            continue;
        m_pSubNodes[i]->AllItems(_pResult);
    }
}

///////////////////////////////////////////////////////////////////////////////
// undefs
///////////////////////////////////////////////////////////////////////////////

#undef qtree_t
#undef node_t
#undef item_t
#undef items_t

// ######################### 
} // end namespace ex 
// ######################### 

