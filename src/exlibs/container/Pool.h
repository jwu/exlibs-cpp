// ======================================================================================
// File         : Pool.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 08:45:29 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef POOL_H_1281833142
#define POOL_H_1281833142
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "BitArray.h"
#include "List.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Pool 
// 
// Purpose: pool is index fixed array 
//          When erase a item from Pool, the index of the other item will not changed.
//
// NOTE: Before erase an item, if you allocate memory for that item, you need 
//       to deallocate or you may probably get memory leak, cause you don't have way 
//       to get unused item.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class Pool
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Pool<T,TAllocator_T>                       self_t;
    typedef BitArray<TAllocator_T>                     free_bits_t;
    typedef size_t                                      sz_t;
	typedef T                                           value_t;          
	typedef T&                                          ref_t;          
	typedef const T&                                    const_ref_t;          
	typedef T*                                          ptr_t;          
	typedef const T*                                    const_ptr_t;          

    ///////////////////////////////////////////////////////////////////////////////
    // class Node 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct Node
    {
        value_t    value;
        Node*      prev;
        Node*      next;
    }; // end struct Node

    // typedef 
    typedef Node                                               node_t;
	typedef ContainerAllocator< node_t, TAllocator_T >         node_allocator_t; 
	typedef ContainerAllocator< value_t, TAllocator_T >        value_allocator_t;

    ///////////////////////////////////////////////////////////////////////////////
    // class PoolIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename Val_T, typename Ref_T, typename Ptr_T >
    class PoolIterator : public std::iterator< std::bidirectional_iterator_tag, Val_T, ptrdiff_t, Ptr_T, Ref_T >
    {
        friend class Pool;
    public:
        typedef PoolIterator<Val_T,Ref_T,Ptr_T>                          iter_self_t; 
        typedef std::iterator< std::bidirectional_iterator_tag, 
                               Val_T, 
                               ptrdiff_t, 
                               Ptr_T, 
                               Ref_T >                                    iter_base_t;
        typedef PoolIterator< Val_T, Val_T&, Val_T* >                    iterator_t;
        typedef PoolIterator< Val_T, const Val_T&, const Val_T* >        const_iterator_t;

        typedef Val_T       iter_value_t;
        typedef Ptr_T       iter_pointer_t;
        typedef Ref_T       iter_reference_t;

    public:
        //
        PoolIterator()
            : m_pNode(NULL)
        {
        }

        //
        PoolIterator( node_t* _pNode )
            : m_pNode(_pNode)
        {
        }

        //
        PoolIterator( const iterator_t& _copy )
            : m_pNode(_copy.m_pNode)
        {
        }

        // 
        INLINE iter_self_t& operator ++ () 
        {
            this->_incr();
            return *this;
        }
        INLINE iter_self_t operator ++ (int) 
        {
            iter_self_t _tmp = *this;
            this->_incr();
            return _tmp; 
        }

        //
        INLINE iter_self_t& operator -- () 
        {
            this->_Decr();
            return *this; 
        }

        INLINE iter_self_t operator -- (int) 
        {
            iter_self_t _tmp = *this;
            this->_Decr();
            return _tmp; 
        }

        //
        INLINE bool operator == ( const iter_self_t& _cmp_iter ) const { return m_pNode == _cmp_iter.m_pNode; } 
        INLINE bool operator != ( const iter_self_t& _cmp_iter ) const { return m_pNode != _cmp_iter.m_pNode; } 

        //
        iter_reference_t operator * () const { return m_pNode->value; }

    protected:
        void _incr() { m_pNode = m_pNode->next; }
        void _Decr() { m_pNode = m_pNode->prev; }

    protected:
        node_t*          m_pNode; 

    }; // end struct PoolIterator

    // typedef
    typedef PoolIterator<value_t,value_t&,value_t*>                          iterator;
    typedef PoolIterator<value_t,const value_t&,const value_t*>              c_iterator;
    typedef std::reverse_iterator<iterator>                                  r_iterator;
    typedef std::reverse_iterator<c_iterator>                                c_r_iterator;


    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    explicit Pool( sz_t _count = 256 )
        : m_pNodes(NULL),
          m_pUsed(NULL),
          m_pFree(NULL),
          m_capacity(_count),
          m_count(0)
    {
        this->_init(m_capacity);
    }

    // 
    Pool( sz_t _count, const value_t& _val )
        : m_pNodes(NULL),
          m_pUsed(NULL),
          m_pFree(NULL),
          m_capacity(_count),
          m_count(0)
    {
        this->_init(m_capacity);
        for ( sz_t i = 0; i < m_capacity; ++i )
            this->insert(_val);
    }

    //
    Pool( const self_t& _copy )
        : m_pNodes(NULL),
          m_pUsed(NULL),
          m_pFree(NULL),
          m_capacity(_copy.m_capacity),
          m_count(0)
    {
        this->_init(m_capacity);

        //
        c_iterator iter = _copy.begin();
        c_iterator iterEnd = _copy.end();
        for ( ; iter != iterEnd; ++iter )
            this->insert(*iter);
    }

    //
    Pool( const value_t* _pFirst, const value_t* _pLast )
        : m_pNodes(NULL),
          m_pUsed(NULL),
          m_pFree(NULL),
          m_capacity(_pLast-_pFirst),
          m_count(0)
    {
        this->_init(m_capacity);

        //
        while ( _pFirst != _pLast )
        {
            this->insert(*_pFirst);
            ++_pFirst;
        }
    }

    //
    ~Pool()
    {
        this->_dealloc();
    }

    //
    INLINE self_t& operator = ( const self_t& _copy ) 
    {
        //
        clear();
        resize(_copy.m_capacity);
        memcpy( this->_dataPtr(), _copy._dataPtr(), sizeof(node_t)*(m_capacity+2) );
        this->_initNodes();
        m_freeBits = _copy.m_freeBits;

        //
        for ( sz_t iBit = m_capacity-1; iBit != sz_t(-1); --iBit )
        {
            // if free
            if ( this->is_free_at(iBit) )
            {
                this->_pushFreeNode( m_pNodes + iBit );
            }
            else
            {
                this->_pushUsedNode( m_pNodes + iBit );
            }
        }

        return *this;
    }

    //
    INLINE bool operator == ( const self_t& _comp ) const
    {
        if ( size() != _comp.size() ) 
            return false;

        c_iterator it_mine = begin();
        c_iterator it_yours = _comp.begin();
        for ( ; it_mine != end(); ++it_mine, ++it_yours )
        {
            sz_t idx = index(*it_mine);
            if ( _comp.is_free_at (idx) ) // confirm that same index have same allocated node.
                return false;
            if ( *it_mine != _comp[idx] ) // check the value of the node in same index
                return false;
        }

        return true;
    }
    INLINE bool operator != ( const self_t& _comp ) const { return !((*this) == _comp); }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:
    // 
    INLINE node_allocator_t node_allocator() { return node_allocator_t(); }
    INLINE value_allocator_t GetValueAllocator() { return value_allocator_t(); }

    //
    INLINE iterator begin()                                 { return this->_usedNodeBegin(); }
    INLINE c_iterator begin() const                         { return this->_usedNodeBegin(); }

    //
    INLINE iterator end()                                   { return this->_usedNodeEnd(); }
    INLINE c_iterator end() const                           { return this->_usedNodeEnd(); }

    //
    INLINE r_iterator rbegin()                              { return r_iterator(m_pUsed);   }
    INLINE c_r_iterator rbegin() const                      { return c_r_iterator(m_pUsed);   }

    //
    INLINE r_iterator rend()                                { return r_iterator(_dataPtr()); }
    INLINE c_r_iterator rend() const                        { return c_r_iterator(_dataPtr()); }

    //
    INLINE bool empty() const                               { return _usedNodeBegin() == _usedNodeEnd(); }
    INLINE bool is_free( const iterator& _pos ) const       { return m_freeBits[index(_pos)]; }
    INLINE bool is_free_at( sz_t _idx ) const               { return m_freeBits[_idx]; }

    //
    INLINE sz_t size() const                                { return m_count; }
    INLINE sz_t max_size() const                            { return sz_t(-1); }
    INLINE sz_t capacity() const                            { return m_capacity;   }
    INLINE sz_t index( const iterator& _iter ) const        { return _iter.m_pNode - m_pNodes; }
    INLINE sz_t index( const_ref_t _val ) const             
    {
        // remember, use &_val means use value_t*, and it will minus the sizeof(ptr)*2 (next,prev) so the result will be wrong
        return ( (node_t*)(&_val) - m_pNodes );
    }

    //
    INLINE iterator to_iter( sz_t _idx )                    { ex_assert( this->is_free_at(_idx) != true, "node[%d] have been freed", _idx ); return iterator( m_pNodes + _idx ); }
    INLINE c_iterator to_iter( sz_t _idx ) const            { ex_assert( this->is_free_at(_idx) != true, "node[%d] have been freed", _idx ); return c_iterator( m_pNodes + _idx ); }

    //
    INLINE result_t erase( iterator _pos )                   
    {
        // if the node already earse, skip
        if ( this->is_free(_pos) ) 
            return EResult::already_freed;

        this->_freeUsedNode(_pos.m_pNode);
        return EResult::ok;
    }

    //
    INLINE result_t erase( iterator _first, iterator _last, List<iterator>* _pFreedIters ) 
    {
        iterator iter = _first;
        while ( iter != _last )
        {
            iterator cur_iter = iter;
            if ( this->erase(iter++) == EResult::already_freed )
                _pFreedIters->push_back(cur_iter);
        }

        //
        if ( _pFreedIters->empty() )
            return EResult::ok;
        else
            return EResult::already_freed;
    }

    //
    INLINE result_t erase_at( sz_t _idx )
    {
        return this->erase( iterator(m_pNodes+_idx) );
    }

    //
    INLINE void clear()                                      
    {
        this->_freeAllUsedNode();
    }

    //
    INLINE void swap( self_t& _container )                   
    {
        ex::value_swap( m_pNodes, _container.m_pNodes );
        ex::value_swap( m_pFree, _container.m_pFree );
        ex::value_swap( m_pUsed, _container.m_pUsed );
        ex::value_swap( m_capacity, _container.m_capacity );
        m_freeBits.swap(_container.m_freeBits);
    }

    //
    INLINE ref_t operator [] ( sz_t _idx ) 
    {
        ex_assert( !this->is_free_at(_idx), "The element have already been free" ); 
        return m_pNodes[_idx].value;
    }
    INLINE const_ref_t operator [] ( sz_t _idx ) const 
    {
        ex_assert( !this->is_free_at(_idx), "The element have already been free" ); 
        return m_pNodes[_idx].value;
    }

    //
    INLINE ref_t front () 
    {
        return *begin();
    }
    INLINE const_ref_t front () const 
    {
        return *begin();
    }

    //
    INLINE ref_t back () 
    {
        return *end();
    }
    INLINE const_ref_t back () const 
    {
        return *end();
    }

    //
    INLINE iterator insert( const T& _val )
    {
        node_t* pNode = this->_requestFreeNode();
        GetValueAllocator().construct( &pNode->value, _val );
        this->_pushUsedNode(pNode);
        return pNode;
    }

    //
    INLINE sz_t insert_getindex( const T& _val )
    {
        return this->index(insert(_val));
    }

    // this is only used in ex_new_in
    INLINE ptr_t insert()
    {
        node_t* pNode = this->_requestFreeNode();
        this->_pushUsedNode(pNode);
        return &(pNode->value);
    }

    // TODO: havn't tested
    INLINE void push_at( sz_t _idx, const T& _val )
    {
        ex_assert( this->is_free_at(_idx), "index:%d is not free", _idx );
        node_t* pNode = this->_requestFreeNodeAt(_idx);
        GetValueAllocator().construct( &pNode->value, _val );
        this->_pushUsedNode(pNode);
    }

    // TODO: havn't tested
    // this is only used in ex_new_at
    INLINE ptr_t push_at( sz_t _idx )
    {
        ex_assert( this->is_free_at(_idx), "index:%d is not free", _idx );
        node_t* pNode = this->_requestFreeNodeAt(_idx);
        this->_pushUsedNode(pNode);
        return &(pNode->value);
    }

    // reset will clear the old data, then resize 
    INLINE result_t reset( sz_t _new_size )
    {
        clear();
        return resize(_new_size);
    }

    // resize will keep the old data, if it small than the _new_size
    INLINE result_t resize( sz_t _new_size ) 
    {
        if ( _new_size < capacity()  )
            return this->shrink(_new_size);
        else
            return this->reserve(_new_size);
    }

    //
    INLINE result_t reserve( sz_t _new_size )
    {
        if ( capacity() < _new_size )
        {
            node_t* pOrgNodes = this->_dataPtr(); 
            m_pUsed = (node_t*)node_allocator().allocate(_new_size+2);
            memcpy( m_pUsed, pOrgNodes, sizeof(node_t)*(m_capacity+2) );

            this->_initNodes();

            //
            m_freeBits.resize(_new_size,true);
            m_count = 0;

            //
            for ( sz_t iBit = _new_size-1; iBit != sz_t(-1); --iBit )
            {
                // if free
                if ( this->is_free_at(iBit) )
                {
                    this->_pushFreeNode( m_pNodes + iBit );
                }
                else
                {
                    this->_pushUsedNode( m_pNodes + iBit );
                }
            }

            // deallocate original data
            if ( pOrgNodes )
                node_allocator().deallocate( pOrgNodes, this->size() /*this is a dummy value*/ );

            //
            m_capacity = _new_size;
            return EResult::ok;
        }

        return EResult::no_change;
    }

    //
    INLINE result_t shrink( sz_t _shrink_size = sz_t(-1) )
    {
        // if zero, clear and return
        if ( _shrink_size == 0 )
        {
            clear();
            return EResult::ok;
        }

        // if -1, process auto shrink
        sz_t lastFreeBit = m_capacity-1;
        if ( _shrink_size == sz_t(-1) )
        {
            for ( ; lastFreeBit != sz_t(-1); --lastFreeBit )
            {
                // if bit in used
                if ( !this->is_free_at(lastFreeBit) )
                    break;
            }
        }
        else
        {
            lastFreeBit = _shrink_size;
        }

        //
        if ( lastFreeBit < capacity() )
        {
            sz_t newSize = lastFreeBit; 

            node_t* pOrgNodes = this->_dataPtr(); 
            m_pUsed = (node_t*)node_allocator().reallocate(pOrgNodes,newSize+2);
            // memcpy( m_pUsed, pOrgNodes, sizeof(node_t)*(newSize+2) );
            // node_allocator().deallocate(pOrgNodes,m_capacity);

            this->_initNodes();

            m_freeBits.resize(newSize,true);
            m_capacity = newSize;
            m_count = 0;

            //
            for ( sz_t iBit = m_capacity-1; iBit != sz_t(-1); --iBit )
            {
                // if free
                if ( this->is_free_at(iBit) )
                {
                    this->_pushFreeNode( m_pNodes + iBit );
                }
                else
                {
                    this->_pushUsedNode( m_pNodes + iBit );
                }
            }
        }
        return EResult::ok;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    INLINE iterator _freeNodeBegin() { ex_assert(m_pFree, "m_pFree should allocated"); return m_pFree; }
    INLINE c_iterator _freeNodeBegin() const { ex_assert(m_pFree, "m_pFree should allocated"); return m_pFree; }

    INLINE iterator _freeNodeEnd() { ex_assert(m_pNodes, "m_pNodes should allocated"); return m_pNodes - 1; }
    INLINE c_iterator _freeNodeEnd() const { ex_assert(m_pNodes, "m_pNodes should allocated"); return m_pNodes - 1; }

    //
    INLINE iterator _usedNodeBegin() { ex_assert( _dataPtr(), "data-ptr should allocated"); return _dataPtr()->next; }
    INLINE c_iterator _usedNodeBegin() const { ex_assert(_dataPtr(), "data-ptr should allocated"); return _dataPtr()->next; }

    INLINE iterator _usedNodeEnd() { ex_assert(_dataEndPtr(), "data-end-ptr should allocated"); return _dataEndPtr(); }
    INLINE c_iterator _usedNodeEnd() const { ex_assert(_dataEndPtr(), "data-end-ptr should allocated"); return const_cast<node_t*>(_dataEndPtr()); }

    //
    INLINE sz_t _index( const node_t* _pNode ) const { return _pNode - m_pNodes; }

    INLINE node_t* _dataPtr() { ex_assert(m_pNodes, "m_pNodes should allocated"); return m_pNodes - 2; }
    INLINE const node_t* _dataPtr() const { ex_assert(m_pNodes, "m_pNodes should allocated"); return m_pNodes - 2; }

    INLINE node_t* _dataEndPtr() { ex_assert(m_pNodes, "m_pNodes should allocated"); return m_pNodes-2; }
    INLINE const node_t* _dataEndPtr() const { ex_assert(m_pNodes, "m_pNodes should allocated"); return m_pNodes-2; }

    //
    INLINE void _init( sz_t _count )
    {
        // there will be 2 more node,
        // node_1 for UsedNode
        // node_2 for FreeNode
        m_pUsed = (node_t*)node_allocator().allocate(_count+2);
        this->_initNodes();
        m_freeBits.resize(_count);

        // push all nodes to free chain
        for ( sz_t i = _count-1; i != sz_t(-1); --i )
        {
            this->_pushFreeNode(m_pNodes+i);
        }
    }

    //
    INLINE void _initNodes ()
    {
        m_pFree = m_pUsed+1; 
        m_pNodes = m_pUsed+2; 

        // init
        m_pFree->next = NULL;
        m_pFree->prev = NULL;

        m_pUsed->next = _dataEndPtr();
        m_pUsed->prev = _dataEndPtr();

        m_pNodes->next = NULL;
        m_pNodes->prev = NULL;
    }

    //
    INLINE void _dealloc()
    {
        clear();
        node_t* pData =  this->_dataPtr();
        if ( pData )
            node_allocator().deallocate( pData, this->size() /*this is a dummy value*/ );
    }

    //
    INLINE void _pushFreeNode( node_t* _pNode ) 
    {
        m_pFree->next = _pNode;
        _pNode->prev = m_pFree; 
        _pNode->next = NULL;
        m_pFree = _pNode;

        // set bit
        m_freeBits[_index(_pNode)] = true;
    }

    //
    INLINE node_t* _requestFreeNode()
    {
        if ( iterator(m_pFree) == _freeNodeEnd() )
        {
            this->reserve( capacity() * 2 );
        }
        node_t* pRet = m_pFree;
        m_pFree = m_pFree->prev;
        m_pFree->next = NULL;

        ex_assert( this->is_free_at(index(pRet)), "error! the node is in used" );
        return pRet;
    }

    //
    INLINE node_t* _requestFreeNodeAt( sz_t _idx )
    {
        ex_assert( this->is_free_at(_idx), "index:%d is not free", _idx );
        node_t* pRet = m_pNodes+_idx;

        //
        pRet->prev->next = pRet->next;

        //
        if ( pRet->next )
            pRet->next->prev = pRet->prev;
        // if this is first node
        else 
            m_pFree = pRet->prev;

        return pRet;
    }

    //
    INLINE void _pushUsedNode( node_t* _pNode ) 
    {
        m_pUsed->next = _pNode;
        _pNode->prev = m_pUsed; 
        _pNode->next = _dataEndPtr(); // used-node end
        _dataEndPtr()->prev = _pNode;
        m_pUsed = _pNode;

        // set bit
        m_freeBits[_index(_pNode)] = false;
        ++m_count;
    }

    //
    INLINE void _freeUsedNode( node_t* _pNode )
    {
        ex_assert( !this->is_free_at(index(_pNode)), "the node already freed" );
        // TODO: shrink here is uneffecient
        // FIXME: shrink will re-address everything, so the _pNode in will be nothing
        // if ( size()*2 < capacity() )
            // this->shrink();

        GetValueAllocator().destroy(&_pNode->value);
        // unlink the node from used chain
        _pNode->prev->next = _pNode->next;
        _pNode->next->prev = _pNode->prev;

        // if this is last node
        if ( _pNode->next == _dataEndPtr() )
            m_pUsed = _pNode->prev;

        this->_pushFreeNode(_pNode);
        --m_count;
    }

    //
    INLINE void _freeAllUsedNode()
    {
        node_t* pUsedNodeBegin = _usedNodeBegin().m_pNode;
        node_t* pUsedNodeEnd = _usedNodeEnd().m_pNode;
        while ( pUsedNodeBegin != pUsedNodeEnd )
        {
            node_t* pTmp = pUsedNodeBegin;
            pUsedNodeBegin = pUsedNodeBegin->next;
            GetValueAllocator().destroy( &pTmp->value );

            //
            this->_pushFreeNode(pTmp);
            --m_count;
        }
        m_pUsed = _dataPtr();
        m_pUsed->next = _dataEndPtr();
        m_pUsed->prev = _dataEndPtr();

        ex_assert( m_count == 0, "there still have node not been cleared" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        c_iterator iter       = this->begin();
        c_iterator iterEnd    = this->end();
        for ( ; iter != iterEnd; ++iter )
        {
            string = string + "[" + ex::to_str<FLAGS>(index(*iter)) + "]" + ex::to_str<FLAGS>((*iter)) + "\n";
        }
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Pool");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    node_t*                     m_pNodes;
    node_t*                     m_pUsed;
    node_t*                     m_pFree;
    free_bits_t                 m_freeBits;
    sz_t                        m_capacity;
    sz_t                        m_count;

}; // end class Pool

// #########################
} // end namespace ex 
// #########################

// ------------------------------------------------------------------
// Desc: 
//  If the TNeedConstruct<T>::Result is true, 
//  it is recomment to use this new function to do add/insert
//  instead of adding/inserting by member function. 
//  Because you will call constructor then copy-constructor.
// ------------------------------------------------------------------

// ========================================================
// placement new for push back
// ========================================================

template<  typename T, template <class> class TAllocator_T >
INLINE void* operator new ( size_t _size, ex::Pool<T,TAllocator_T>& _pool )
{
    return _pool.insert();
}

// ========================================================
// placement new for insert
// ========================================================

template<  typename T, template <class> class TAllocator_T >
INLINE void* operator new ( size_t _size, ex::Pool<T,TAllocator_T>& _pool, int _idx )
{
    return &(*(_pool.push_at( _idx )));
}

// ------------------------------------------------------------------
// Desc: 
// this is dummy function
// ------------------------------------------------------------------
// {
template<  typename T, template <class> class TAllocator_T >
INLINE void operator delete ( void* _ptr, ex::Pool<T,TAllocator_T>& _pool ) {}

template< typename T, template <class> class TAllocator_T >
INLINE void operator delete ( void* _ptr, ex::Pool<T,TAllocator_T>& _pool, int _idx ) {}
// }

// #################################################################################
#endif // END POOL_H_1281833142
// #################################################################################

