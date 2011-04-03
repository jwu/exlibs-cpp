// ======================================================================================
// File         : HashPool.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:26:51 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASHPOOL_H_1250522814
#define HASHPOOL_H_1250522814
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "Pool.h"
#include "Array.h"
#include "Pair.h"

// #########################
namespace ex { 
// #########################
    
///////////////////////////////////////////////////////////////////////////////
// class HashPool
// 
// Purpose:
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename KEY, 
           typename VALUE,
           typename HASH_FUNC, 
           typename GET_KEY_FUNC, 
           typename EQUAL_KEY_FUNC,
           template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class HashPool
{

    ///////////////////////////////////////////////////////////////////////////////
    // public typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
	typedef HashPool< KEY,
                       VALUE,
                       HASH_FUNC,
                       GET_KEY_FUNC,
                       EQUAL_KEY_FUNC,
                       TAllocator_T >                       self_t;  
    typedef size_t                                          sz_t;           
	typedef VALUE&                                          ref_t;          
	typedef const VALUE&                                    const_ref_t;          
	typedef VALUE*                                          ptr_t;          
	typedef const VALUE*                                    const_ptr_t;          

    typedef KEY                                             key_t;          
    typedef VALUE                                           value_t;          
    typedef HASH_FUNC                                       hash_f;          
    typedef GET_KEY_FUNC                                    get_key_f;
    typedef EQUAL_KEY_FUNC                                  equal_key_f;          

    // ========================================================
    // internal structs
    // ========================================================

public:

    ///////////////////////////////////////////////////////////////////////////////
    // class HashNode 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct HashNode
    {
        // NOTE: this is for serialize use. (serialize need a default constructor)
        HashNode()
            : hash_next(ex::IndexNone),
              hash_prev(ex::IndexNone)
        {
        }

        //
        HashNode( const value_t& _val )
            : value(_val),
              hash_next(ex::IndexNone),
              hash_prev(ex::IndexNone)
        {
        }

        //
        value_t     value;
        sz_t        hash_next;
        sz_t        hash_prev;

        INLINE bool operator == ( const HashNode& _comp ) const { return value == _comp.value; }
        INLINE bool operator != ( const HashNode& _comp ) const { return !(this->operator == (_comp)); }

        ///////////////////////////////////////////////////////////////////////////////
        // generic functions 
        ///////////////////////////////////////////////////////////////////////////////

    public:

        //
        template < class SELF_TYPE > friend class PropertyInstance;
        void serialize ( ISerializeNode* _pNode );
        template < uint FLAGS > INLINE string_t to_str() const
        {
            string_t string;
            string = string + "value: " + ex::to_str<FLAGS>(value) + "\n";
            string = string + "hash_next: " + ex::to_str<FLAGS>(uint32(hash_next)) + "\n";
            string = string + "hash_prev: " + ex::to_str<FLAGS>(uint32(hash_prev)) + "\n";
            return string;
        }
        static const string_id_t& type_name () 
        {
            static const string_id_t strID ("HashNode");
            return strID;
        }

    }; // end struct HashNode

    // typedef 
    typedef HashNode                                           node_t;
	typedef ContainerAllocator<node_t,TAllocator_T>            node_allocator_t; // this allocator allocate node_t
	typedef ContainerAllocator<value_t,TAllocator_T>           value_allocator_t; // this allocator allocate value_t
	typedef ContainerAllocator<sz_t, TAllocator_T>             index_allocator_t; // this allocator allcate hash indices
    typedef Pool<node_t,TAllocator_T>                          node_pool_t;

    // typedef
    typedef typename node_pool_t::iterator              iterator;
    typedef typename node_pool_t::c_iterator            c_iterator;
    typedef typename node_pool_t::r_iterator            r_iterator;
    typedef typename node_pool_t::c_r_iterator          c_r_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    HashPool( sz_t _size = 256 )
        : m_hashCount(_size)
        , m_hashToNodeTable(NULL)
    {
        this->_init(m_hashCount);
    }

    //
    HashPool( const self_t& _copy )
        : m_hashCount(_copy.m_hashCount),
          m_nodepool(_copy.m_nodepool)
    {
        m_hashToNodeTable = index_allocator().allocate( m_hashCount );
        memcpy( m_hashToNodeTable, _copy.m_hashToNodeTable, sizeof(sz_t)*m_hashCount );
    }

    //
    ~HashPool()
    {
        this->_dealloc();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE self_t& operator = ( const self_t& _copy ) 
    {
        m_nodepool = _copy.m_nodepool;
        if ( m_hashToNodeTable )
            index_allocator().deallocate(m_hashToNodeTable, m_hashCount/*this is dummy value*/);
        m_hashCount = _copy.m_hashCount;
        m_hashToNodeTable = index_allocator().allocate( m_hashCount );
        memcpy( m_hashToNodeTable, _copy.m_hashToNodeTable, sizeof(sz_t)*this->size() );
        return *this;
    }

    //
    // DISABLE { 
    // INLINE bool operator == ( const self_t& _comp ) const
    // {
    //     if ( size() != _comp.size() ) 
    //         return false;
    //     return m_nodepool == _comp.m_nodepool;
    // }
    // INLINE bool operator != ( const self_t& _comp ) const { return !((*this) == _comp); }
    // } DISABLE end 

    //
    INLINE index_allocator_t index_allocator() { return index_allocator_t(); }

    //
    INLINE iterator begin() { return m_nodepool.begin(); }
    INLINE c_iterator begin() const { return m_nodepool.begin(); }

    //
    INLINE iterator end() { return m_nodepool.end(); }
    INLINE c_iterator end() const { return m_nodepool.end(); }

    //
    INLINE r_iterator rbegin() { return m_nodepool.rbegin(); }
    INLINE c_r_iterator rbegin() const { return m_nodepool.rbegin(); }

    //
    INLINE r_iterator rend() { return m_nodepool.rend(); }
    INLINE c_r_iterator rend() const { return m_nodepool.rend(); }

    //
    INLINE iterator to_iter( sz_t _idx )                     { return m_nodepool.to_iter(_idx); }
    INLINE c_iterator to_iter( sz_t _idx ) const          { return m_nodepool.to_iter(_idx); }

    //
    INLINE sz_t size() const { return m_nodepool.size(); } 
    INLINE sz_t max_size() const { return sz_t(-1); }
    INLINE sz_t capacity() const { return m_hashCount; }
    INLINE bool empty() const { return size() == 0; } 

    //
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
            this->_update(_new_size);
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

        // shrink size is -1, process auto shrink
        if ( _shrink_size == sz_t(-1) )
        {
            m_nodepool.shrink(-1);
            if ( ex::is_powof2(uint(this->size())) )
                this->_update(this->size());
            return EResult::ok;
        }

        //
        if ( _shrink_size != sz_t(-1) )
        {
            this->_update(_shrink_size);
            return EResult::ok;
        }

        return EResult::no_change;
    }

    //
    INLINE void clear()                                        
    {
        if ( !this->empty() )
        {
            // NOTE: the HashPool needs at least one item resize.
            for ( sz_t i = 0; i < m_hashCount; ++i )
            {
                m_hashToNodeTable[i] = sz_t(ex::IndexNone);
            }

            //
            m_nodepool.clear();
            m_hashCount = 0;
        }
    }

    //
    INLINE void swap( self_t& _container )                     
    {
        std::swap( m_hashFunctor, _container.m_hashFunctor );
        std::swap( m_equalKeyFunctor, _container.m_equalKeyFunctor );
        std::swap( m_getKeyFunctor, _container.m_getKeyFunctor );
        std::swap( m_hashCount, _container.m_hashCount );
        std::swap( m_hashToNodeTable, _container.m_hashToNodeTable );
        m_nodepool.swap(_container.m_nodepool);
    }   

    //
    INLINE sz_t InsertEqual( const value_t& _val )
    {
        ex_assert ( this->capacity() > 0, "fatal error! operate with empty hash-table. this could happend when you call HashPool::clear, but never call HashPool::resize when reuse it." );
        sz_t hash_index = _getHashIndexByValue(_val);
        return _insert( hash_index, _val );
    }

    //
    INLINE Pair<sz_t,result_t> InsertUnique( const value_t& _val )
    {
        ex_assert ( this->capacity() > 0, "fatal error! operate with empty hash-table. this could happend when you call HashPool::clear, but never call HashPool::resize when reuse it." );
        sz_t hash_index = _getHashIndexByValue(_val);
        for ( sz_t i = m_hashToNodeTable[hash_index]; i != sz_t(ex::IndexNone); i = m_nodepool[i].hash_next )
        {
            // compare the key
            if ( isEqualKey( key(_val), key(m_nodepool[i].value) ) )
                return Pair<sz_t,result_t>(i,EResult::already_existed);
        }
        sz_t unique_idx = _insert( hash_index, _val );
        return Pair<sz_t,result_t>( unique_idx, EResult::ok );
    }

    //
    INLINE iterator erase( iterator _iter )
    {
        iterator iterNext = _iter;
        ++iterNext;
        ex_assert ( this->size() > 0, "erase item in empty size hash-pool" );
        this->_erase( m_nodepool.index(_iter), _getHashIndexByNode(&(*_iter)) );
        return iterNext;
    }

    //
    INLINE iterator erase( iterator _first, iterator _last ) 
    {
        ex_assert ( this->size() > 0, "erase item in empty size hash-pool" );

        // if the range is wrong, swap it.
        if ( int(m_nodepool.index(_first)) < int(m_nodepool.index(_last)) )
        {
            iterator temp = _first;
            _first = _last;
            _last = temp;
        }

        iterator iter = _first;
        while ( iter != _last )
        {
            iter = this->erase(iter);
        }

        return iter;
    }

    // available for set/map
    INLINE sz_t erase_equal( const key_t& _key )
    {
        if ( this->size() > 0 )
        {
            sz_t remove_num = 0;
            sz_t hash_index = _getHashIndexByKey(_key);

            // process erase
            for ( sz_t idx = m_hashToNodeTable[hash_index],next_idx = ex::IndexNone; idx != sz_t(ex::IndexNone); idx = next_idx )
            {
                // erase will destroy the idx, we need to use next_idx keep right iterate.
                next_idx = m_nodepool[idx].hash_next;
                if ( isEqualKey( _key, key(m_nodepool[idx].value) ) )
                {
                    _erase( idx, hash_index );
                }
            }
            return remove_num;
        }
        return 0;
    }

    // available for multi-set/multi-map
    INLINE result_t erase_unique( const key_t& _key )
    {
        if ( this->size() > 0 )
        {
            iterator iter = find_unique(_key);
            if ( iter != end() )
            {
                this->erase(iter);
                return EResult::ok;
            }
        }
        return EResult::not_found;
    }

    // 
    INLINE void find_equal( const key_t& _key, Array<iterator>* _pResult )
    {
        if ( this->size() > 0 )
        {
            sz_t hash_index = _getHashIndexByKey( _key );
            for ( sz_t i = m_hashToNodeTable[hash_index]; i != sz_t(ex::IndexNone); i = m_nodepool[i].hash_next )
            {
                if ( isEqualKey( _key, key(m_nodepool[i].value) ) )
                {
                    _pResult->push_back( m_nodepool.to_iter(i) );
                }
            }
        }
    }

    // 
    INLINE void find_equal( const key_t& _key, Array<c_iterator>* _pResult ) const
    {
        if ( this->size() > 0 )
        {
            sz_t hash_index = _getHashIndexByKey( _key );
            for ( sz_t i = m_hashToNodeTable[hash_index]; i != sz_t(ex::IndexNone); i = m_nodepool[i].hash_next )
            {
                if ( isEqualKey( _key, key(m_nodepool[i].value) ) )
                {
                    _pResult->push_back( m_nodepool.to_iter(i) );
                }
            }
        }
    }

    // 
    INLINE iterator find_unique( const key_t& _key )
    {
        if ( this->size() > 0 )
        {
            sz_t hash_index = _getHashIndexByKey( _key );
            for ( sz_t i = m_hashToNodeTable[hash_index]; i != sz_t(ex::IndexNone); i = m_nodepool[i].hash_next )
            {
                ex_assert( !m_nodepool.is_free_at(i), "the node[%d] have been freed.", i );
                if ( isEqualKey( _key, key(m_nodepool[i].value) ) )
                    return m_nodepool.to_iter(i);
            }
        }
        return end();
    }

    // 
    INLINE c_iterator find_unique( const key_t& _key ) const
    {
        if ( this->size() > 0 )
        {
            sz_t hash_index = _getHashIndexByKey( _key );
            for ( sz_t i = m_hashToNodeTable[hash_index]; i != sz_t(ex::IndexNone); i = m_nodepool[i].hash_next )
            {
                ex_assert( !m_nodepool.is_free_at(i), "the node[%d] have been freed", i );
                if ( isEqualKey( _key, key(m_nodepool[i].value) ) )
                    return m_nodepool.to_iter(i);
            }
        }
        return end();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    INLINE key_t key( const value_t& _val ) const { return m_getKeyFunctor(_val); }
    INLINE key_t key( const node_t* _pNode ) const { return m_getKeyFunctor(_pNode->value); }

    //
    INLINE bool isEqualKey( const key_t& _key1, const key_t& _key2 ) const { return m_equalKeyFunctor( _key1, _key2 ); }

    //
    INLINE sz_t getHash( const key_t& _key ) const { return m_hashFunctor(_key); }

protected:

    // _GetHashIndex
    // _GetHashIndex can't be overload, cause THashSet... may share same type for key_t & value_t.
    INLINE sz_t _getHashIndexByKey( const key_t& _key ) const { return getHash(_key) & (m_hashCount-1); }
    INLINE sz_t _getHashIndexByValue( const value_t& _val ) const { return getHash(key(_val)) & (m_hashCount-1); }
    INLINE sz_t _getHashIndexByNode( const node_t* _pNode ) const { return getHash(key(_pNode)) & (m_hashCount-1); }

    //
    INLINE void _init( sz_t _count )
    {
        ex_assert_exec( ex::is_powof2((uint)m_hashCount), m_hashCount = mathop::ceilpow2(_count), "m_hashCount must be power of 2, for bit operation & instead of %" );
        m_hashToNodeTable = index_allocator().allocate( m_hashCount );
        for ( sz_t i = 0; i < m_hashCount; ++i )
        {
            m_hashToNodeTable[i] = sz_t(ex::IndexNone);
        }
        m_nodepool.resize(_count);
    }

    //
    INLINE void _dealloc()
    {
        clear();
        index_allocator().deallocate( m_hashToNodeTable, m_hashCount );
    }

    //
    INLINE void _update( sz_t _new_size )
    {
        if ( _new_size != this->capacity() )
        {
            ex_assert_exec( ex::is_powof2((uint)_new_size), m_hashCount = mathop::ceilpow2(_new_size), "new size must be power of 2, for bit operation & instead of %" );
            index_allocator().deallocate( m_hashToNodeTable, m_hashCount /*this is a dummy value*/ );

            // change the capacity and hash_to_node table
            m_hashCount = _new_size;
            m_hashToNodeTable = index_allocator().allocate( m_hashCount );
            for ( sz_t i = 0; i < m_hashCount; ++i )
            {
                m_hashToNodeTable[i] = sz_t(ex::IndexNone);
            }

            // rehash hashtable
            m_nodepool.resize(m_hashCount);
            typename node_pool_t::iterator iter = m_nodepool.begin();
            typename node_pool_t::iterator iterEnd = m_nodepool.end();

            for ( ; iter != iterEnd; ++iter )
            {
                node_t& node = (*iter);
                sz_t hash_index = _getHashIndexByNode(&node);
                sz_t cur_idx = m_nodepool.index(node);
                sz_t next_idx = m_hashToNodeTable[hash_index];

                //
                node.hash_next = next_idx;
                node.hash_prev = ex::IndexNone;
                m_hashToNodeTable[hash_index] = cur_idx;

                //
                if ( next_idx != sz_t(ex::IndexNone) )
                    m_nodepool[next_idx].hash_prev = cur_idx; 
            }
        }
    }

    // 
    INLINE void _erase( sz_t _erase_idx, sz_t _hash_idx )
    {
        sz_t next_idx = m_nodepool[_erase_idx].hash_next;
        sz_t prev_idx = m_nodepool[_erase_idx].hash_prev;

        // if not erase header
        if ( prev_idx != sz_t(ex::IndexNone) )
        {
            m_nodepool[prev_idx].hash_next = next_idx;

            // if not erase tail
            if ( next_idx != sz_t(ex::IndexNone) )
                m_nodepool[next_idx].hash_prev = prev_idx;
        }
        else // if erase header
        {
            // recheck if not erase tail
            if ( next_idx != sz_t(ex::IndexNone) )
                m_nodepool[next_idx].hash_prev = prev_idx;

            // also change the index
            m_hashToNodeTable[_hash_idx] = next_idx;
        }

        //
        ex_check( m_nodepool.erase_at(_erase_idx) == EResult::ok, "Node[%d] already been removed", _erase_idx );
#if 0
        // TODO: need auto shrink?
        if ( size()*2 < capacity() )
            this->shrink();
#endif
    }

    //
    INLINE sz_t _insert( sz_t _hash_idx, const value_t& _val ) 
    {
        node_t* pNode = ex_new_in(m_nodepool) node_t(_val);

        //
        sz_t cur_idx = m_nodepool.index(*pNode);
        sz_t next_idx = m_hashToNodeTable[_hash_idx];

        //
        pNode->hash_next = next_idx;
        pNode->hash_prev = ex::IndexNone;
        m_hashToNodeTable[_hash_idx] = cur_idx;

        //
        if ( next_idx != sz_t(ex::IndexNone) )
            m_nodepool[next_idx].hash_prev = cur_idx; 

#if 0
        // TODO: need auto reserve?
        if ( size()*2 > capacity() )
            this->reserve(capacity()*2);
#endif

        return cur_idx;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        string = string + "HashCount: " + ex::to_str<FLAGS>(uint32(m_hashCount)) + "\n";
        string = string + "NodePool: " + "\n" + ex::to_str<FLAGS>(m_nodepool) + "\n";
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("HashPool");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member datas 
    ///////////////////////////////////////////////////////////////////////////////

protected:
    // functors
    hash_f                              m_hashFunctor;
    equal_key_f                         m_equalKeyFunctor;
    get_key_f                           m_getKeyFunctor;

    // hash data
    sz_t                                m_hashCount;
    sz_t*                               m_hashToNodeTable;
    node_pool_t                         m_nodepool;

}; // end class HashPool

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END HASHPOOL_H_1250522814
// #################################################################################
