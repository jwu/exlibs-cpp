// ======================================================================================
// File         : QuadTree.h
// Author       : Wu Jie 
// Last Change  : 12/28/2009 | 16:57:28 PM | Monday,December
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef QUADTREE_H_1261990654
#define QUADTREE_H_1261990654
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class TQuadTree 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class TQuadTree
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef TQuadTree<T> qtree_t;
    typedef TQuadTreeNode<T> node_t;
    typedef TQuadTreeItem<T> item_t;

    typedef List<node_t*> node_list_t;
    typedef HashMap<T,node_t*> item_to_node_t;

    ///////////////////////////////////////////////////////////////////////////////
    // static members
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // ------------------------------------------------------------------ 
    // Desc: 
    // NOTE: you need to manually destroy rest nodes by calling DestroyNodes 
    //       when you close your application or you will have memory leak 
    // ------------------------------------------------------------------ 

    static node_list_t* s_pFreeNodes;

public:

    static void CreateNodeList ( uint _n = 64 );
    static void DestroyNodeList (); 

    static node_t* RequestNode (); 
    static void ReturnNode ( node_t* _node ); 

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    TQuadTree ();
    ~TQuadTree ();

    // NOTE: the _left, _top, _right, _bot is the world you define.
    //       the _size is the maximum size of the quad tree.
    //       the _maxLevel is the maximum level of the quad tree. ( the _maxLevel should <= pow.of.2(_size) )
    //       the quad tree constructor will use the world's LTRB calculate and map to the dest tree ( 0,0 -> _size,_size )
    void init ( float _left = -512.0f, float _top = 512.0f, float _right = 512.0f, float _bot = -512.0f, int _size = 1024, int _maxLevel = -1 );
    void clear ( bool _forceClear = false );

    //
    result_t insert ( const T& _value );
    result_t Update ( const T& _value );
    result_t remove ( const T& _value );

    // NOTE: only world position here
    void Query ( const vec2f_t& _point, Array<T>* _pResult ) const;
    void Query ( const rectf_t& _rect, Array<T>* _pResult ) const;

    // map from world
    vec2f_t MapFromWorld ( const vec2f_t& _point ) const;
    rectf_t MapFromWorld ( const rectf_t& _rect ) const;

    // map to world
    vec2f_t MapToWorld ( const vec2f_t& _point ) const;
    rectf_t MapToWorld ( const rectf_t& _rect ) const;

    // 
    const node_t* Root () const; 

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void SetupMapping( float _left, float _right, float _top, float _bot, const rectf_t& _destRect );
    result_t insert ( const item_t& _item );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    node_t* m_pRoot;
    mat3f_t m_MapFromWorld;
    mat3f_t m_MapToWorld;
    item_to_node_t  m_ItemToNode;
    uint32 m_MaxLevel;

}; // end class TQuadTree

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END QUADTREE_H_1261990654
// #################################################################################


