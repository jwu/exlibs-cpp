// ======================================================================================
// File         : QuadTree.hpp
// Author       : Wu Jie 
// Last Change  : 12/29/2009 | 14:22:34 PM | Tuesday,December
// Description  : 
// ======================================================================================

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// macro defines
///////////////////////////////////////////////////////////////////////////////

#define qtree_t typename TQuadTree<T>::qtree_t
#define node_t typename TQuadTree<T>::node_t
#define item_t typename TQuadTree<T>::item_t
#define node_list_t typename TQuadTree<T>::node_list_t
#define item_to_node_t typename TQuadTree<T>::item_to_node_t

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// static member functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
node_t* TQuadTree<T>::RequestNode () 
{
    ex_assert ( s_pFreeNodes, "Error! node list has not created. pls call TQuadTree<T>::CreateNodeList() first." );

    if ( !s_pFreeNodes->empty() )
    {
        node_t* pNode = s_pFreeNodes->back();
        s_pFreeNodes->pop_back(); 
        return pNode;
    }
    else
    {
        return ex_new TQuadTreeNode<T>();
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTree<T>::ReturnNode ( node_t* _node )
{
    ex_assert ( s_pFreeNodes, "Error! node list has not created. pls call TQuadTree<T>::CreateNodeList() first." );
    s_pFreeNodes->push_back (_node);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTree<T>::CreateNodeList ( uint _n ) 
{
    if ( s_pFreeNodes == NULL )
    {
        s_pFreeNodes = ex_new node_list_t();

        for ( uint i = 0; i < _n; ++i )
        {
            s_pFreeNodes->push_back ( ex_new TQuadTreeNode<T>() );
        }
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTree<T>::DestroyNodeList () 
{
    if ( s_pFreeNodes )
    {
        for ( node_list_t::iterator iter = s_pFreeNodes->begin(); iter != s_pFreeNodes->end(); ++iter )
        {
            ex_delete (*iter);
        }

        ex_delete (s_pFreeNodes);
        s_pFreeNodes = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
// public member functions
///////////////////////////////////////////////////////////////////////////////


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
TQuadTree<T>::TQuadTree ()
    : m_pRoot (NULL)
    , m_MaxLevel (-1)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
TQuadTree<T>::~TQuadTree ()
{
    clear ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTree<T>::init ( float _left, float _top, float _right, float _bot, int _size, int _maxLevel )
{
    // KEEPME { 
    // m_Width = mathop::ceilpow2_f( _maxSize.width() );
    // m_Height = mathop::ceilpow2_f( _maxSize.height() );
    // } KEEPME end 

    //
    int maxSize = _size;
    m_MaxLevel = _maxLevel; 

    // process maxSize
    if ( !is_powof2(_size) )
        maxSize = (int)mathop::ceilpow2( (uint32)_size );

    // process maxLevel
    int tmp_val = maxSize;
    int level = 0;
    while ( tmp_val >>= 1 )
    {
        ++level;
    }
    ex_assert ( level >= _maxLevel, "Error: the _maxLevel(%d) is larger than the level(%d) we can reach depends on the _size(%d) we provide", m_MaxLevel, level, _size );
    if ( level < _maxLevel || _maxLevel == -1 )
        m_MaxLevel = level; 

    //
    rectf_t root_rect( 0.0f, 0.0f, (float)maxSize, (float)maxSize );
    SetupMapping ( _left, _top, _right, _bot, root_rect );

    // create root node
    m_pRoot = TQuadTree<T>::RequestNode();
    m_pRoot->m_pParent = NULL;
    m_pRoot->m_NodeType = eQuadTree_Root; 
    m_pRoot->m_Rect = root_rect;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTree<T>::clear ( bool _forceClear )
{
    if ( m_pRoot )
    {
        // if we don't force clear, check if there still have item in the tree.
        if ( !_forceClear )
        {
            Array<T> result;
            m_pRoot->AllItems( &result );
            ex_assert ( result.empty(), "You still have %d item in the tree, will be clean-up automatically before destroy", result.size() );
        }

        //
        m_pRoot->clear();
        m_pRoot = NULL;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t TQuadTree<T>::insert ( const T& _value )
{
    return insert ( item_t( _value, *this ) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t TQuadTree<T>::Update ( const T& _value )
{
    item_to_node_t::iterator iter = m_ItemToNode.find(_value);
    if ( iter ==  m_ItemToNode.end() )
        return EResult::not_found;

    //
    int level = m_MaxLevel;
    int root_width = (int)m_pRoot->Rect().width();
    int node_width = (int)(*iter)->Rect().width();
    while ( root_width != node_width )
    {
        --level;
        root_width >>= 1;
    }

    // update the item and get the result node 
    item_t newItem( _value, *this );
    node_t* pNewNode = (*iter)->Update( newItem, level, m_pRoot );
    
    // if the result node is NULL, something gose wrong!
    if ( pNewNode == NULL )
        return EResult::not_found;

    // if the resule node different than the original node, renew the ItemToNode table.
    if ( pNewNode != (*iter) )
    {
        m_ItemToNode.erase(iter);

        // if the result node is root, we need to manually re-insert it here
        // NOTE: the insert functon will insert the item to the table.
        if ( pNewNode == m_pRoot )
        {
            this->insert ( newItem );
        }
        else // else, if it is the sub-node, just re-new the table.
        {
            m_ItemToNode.insert( _value, pNewNode );
        }
    }
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t TQuadTree<T>::remove ( const T& _value )
{
    item_to_node_t::iterator iter = m_ItemToNode.find(_value);
    if ( iter ==  m_ItemToNode.end() )
        return EResult::not_found;

    if ( (*iter)->remove(_value) == EResult::ok )
    {
        m_ItemToNode.erase(iter);
        return EResult::ok;
    }

    return EResult::not_found;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTree<T>::Query ( const vec2f_t& _point, Array<T>* _pResult ) const
{
    vec2f_t qtree_point = MapFromWorld(_point); 
    rectf_t point_rect = rectf_t ( qtree_point.x(), qtree_point.y(), qtree_point.x()+0.1f, qtree_point.y()+0.1f );
    Root()->Query ( point_rect, _pResult );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTree<T>::Query ( const rectf_t& _rect, Array<T>* _pResult ) const
{
    Root()->Query( MapFromWorld(_rect), _pResult );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
vec2f_t TQuadTree<T>::MapFromWorld ( const vec2f_t& _point ) const
{
    vec3f_t mapped_point = vec3f_t(_point) * m_MapFromWorld;
    vec2f_t adjusted_point( mapped_point.x(), mapped_point.y() );
    return adjusted_point;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
rectf_t TQuadTree<T>::MapFromWorld ( const rectf_t& _rect ) const
{
    vec2f_t topLeft = MapFromWorld( _rect.top_left() );
    vec2f_t botRight = MapFromWorld( _rect.bot_right() );

    //
    if ( topLeft.x() > botRight.x() )
    {
        ex::value_swap( topLeft.x(), botRight.x() );
    }
    if ( topLeft.y() > botRight.y() )
    {
        ex::value_swap( topLeft.y(), botRight.y() );
    }

    return rectf_t( topLeft.x(), topLeft.y(), botRight.x(), botRight.y() );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
vec2f_t TQuadTree<T>::MapToWorld ( const vec2f_t& _point ) const
{
    vec3f_t mapped_point = vec3f_t(float(_point.x()), float(_point.y()), 1.0f) * m_MapToWorld;
    return vec2f_t( mapped_point.x(), mapped_point.y() );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
rectf_t TQuadTree<T>::MapToWorld ( const rectf_t& _rect ) const
{
    vec2f_t topLeft = MapToWorld( _rect.top_left() );
    vec2f_t botRight = MapToWorld( _rect.bot_right() );

    //
    if ( m_MapToWorld(0,0) < 0 )
    {
        ex::value_swap( topLeft.x(), botRight.x() );
    }
    if ( m_MapToWorld(1,1) < 0 )
    {
        ex::value_swap( topLeft.y(), botRight.y() );
    }

    //
    return rectf_t( topLeft.x(), topLeft.y(), botRight.x(), botRight.y() );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
const node_t* TQuadTree<T>::Root () const 
{
    return m_pRoot;
}

///////////////////////////////////////////////////////////////////////////////
// protected member functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
void TQuadTree<T>::SetupMapping( float _left, float _top, float _right, float _bot, const rectf_t& _destRect )
{
    // ======================================================== 
    // get MapFromWorld matrix 
    // ======================================================== 


    // scale matrix
    float scale_x = _destRect.width()/mathop::abs(_right-_left); 
    float scale_y = _destRect.height()/mathop::abs(_top-_bot); 

    // get rot matrix
    float dir_x = _right - _left;
    if (dir_x < 0) dir_x = -1.0f;
    else dir_x = 1.0f;

    float dir_y = _bot - _top;
    if (dir_y < 0) dir_y = -1.0f;
    else dir_y = 1.0f;

    // get trans matrix
    vec2f_t src_center ( (_right+_left)*0.5f, (_top+_bot)*0.5f );
    mat2f_t mat_ScaleRot ( scale_x * dir_x, 0.0f,
                           0.0f,            scale_y * dir_y );
    vec2f_t traned_center = src_center * mat_ScaleRot;
    vec2f_t trans = _destRect.center() - traned_center;

    //
    m_MapFromWorld.set ( mat_ScaleRot(0,0), mat_ScaleRot(0,1), 0.0f,
                         mat_ScaleRot(1,0), mat_ScaleRot(1,1), 0.0f, 
                         trans.x(),         trans.y(),         1.0f );

    // ======================================================== 
    // get MapToWorld matrix 
    // ======================================================== 

    //
    mat_ScaleRot(0,0) = 1.0f / mat_ScaleRot(0,0);
    mat_ScaleRot(1,1) = 1.0f / mat_ScaleRot(1,1);
    trans = -(trans*mat_ScaleRot);
    m_MapToWorld.set( mat_ScaleRot(0,0), mat_ScaleRot(0,1), 0.0f,
                      mat_ScaleRot(1,0), mat_ScaleRot(1,1), 0.0f, 
                      trans.x(),         trans.y(),         1.0f );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t TQuadTree<T>::insert ( const item_t& _item )
{
    ex_assert ( m_pRoot->Rect().contains( _item.Rect() ), "ERROR: can't add item if the bouding rect don't completely contained by root's rect" );
    if ( m_pRoot->Rect().contains( _item.Rect() ) == false )
        return EResult::failed;

    node_t* pNode = m_pRoot->insert ( _item, m_MaxLevel );
    m_ItemToNode.insert( _item.value(), pNode );
    return EResult::ok;
}

///////////////////////////////////////////////////////////////////////////////
// undefs
///////////////////////////////////////////////////////////////////////////////

#undef qtree_t
#undef node_t
#undef item_t
#undef node_list_t
#undef item_to_node_t

// ######################### 
} // end namespace ex 
// ######################### 



