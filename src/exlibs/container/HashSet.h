// ======================================================================================
// File         : HashSet.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 10:48:45 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASHSET_H_1281840526
#define HASHSET_H_1281840526
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "HashPool.h"
#include "pattern/functors.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class HashSet
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename VALUE, typename HASH_FUNC = Hash<VALUE>, typename EQUAL_KEY = EqualTo<VALUE>, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class HashSet : protected HashPool< VALUE, VALUE, HASH_FUNC, Identity<VALUE>, EQUAL_KEY, TAllocator_T >
{

    ///////////////////////////////////////////////////////////////////////////////
    // public typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef HashSet< VALUE, HASH_FUNC, EQUAL_KEY, TAllocator_T > self_t;
    typedef HashPool< VALUE, VALUE, HASH_FUNC, Identity<VALUE>, EQUAL_KEY, TAllocator_T > base_t;

    typedef VALUE                                   key_t;          
    typedef VALUE                                   value_t;          

	typedef typename base_t::sz_t                   sz_t;           
	typedef typename base_t::ptr_t                  ptr_t;            
	typedef typename base_t::const_ptr_t            const_ptr_t;       
	typedef typename base_t::ref_t                  ref_t;          
	typedef typename base_t::const_ref_t            const_ref_t;     
	typedef typename base_t::index_allocator_t      index_allocator_t;
	typedef typename base_t::node_allocator_t       node_allocator_t;

public:

    ///////////////////////////////////////////////////////////////////////////////
    // class HashSetIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashSetIterator : public base_t::iterator
    {
    public:
        typedef HashSetIterator  iter_self_t;
        typedef typename base_t::iterator   iter_base_t;

    public:
        HashSetIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        value_t& operator * () const { return (iter_base_t::m_pNode->value).value; }
    }; // end class HashSetIterator 

    ///////////////////////////////////////////////////////////////////////////////
    // class HashSetConstIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashSetConstIterator : public base_t::c_iterator
    {
    public:
        typedef HashSetConstIterator     iter_self_t;
        typedef typename base_t::c_iterator      iter_base_t;

    public:
        HashSetConstIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        const value_t& operator * () const { return (iter_base_t::m_pNode->value).value; }
    }; // end class HashSetConstIterator 

    //
    typedef class HashSetIterator                   iterator;           
    typedef class HashSetConstIterator              c_iterator;      
    typedef std::reverse_iterator<iterator>         r_iterator;
    typedef std::reverse_iterator<c_iterator>       c_r_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    HashSet( sz_t _size = 256 )
        : base_t(_size)
    {
    }

    //
    HashSet( const self_t& _copy )
        : base_t(_copy)
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member function defines 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    INLINE index_allocator_t index_allocator() { return base_t::index_allocator(); }
    INLINE node_allocator_t node_allocator() { return base_t::node_allocator(); }

    //
    INLINE iterator begin() { return base_t::begin(); }
    INLINE c_iterator begin() const { return base_t::begin(); }

    //
    INLINE iterator end() { return base_t::end(); }
    INLINE c_iterator end() const { return base_t::end(); }

    //
    INLINE r_iterator rbegin() { return base_t::rbegin(); }
    INLINE c_r_iterator rbegin() const { return base_t::rbegin(); }

    //
    INLINE r_iterator rend() { return base_t::rend(); }
    INLINE c_r_iterator rend() const { return base_t::rend(); }

    //
    INLINE iterator to_iter( sz_t _idx )                 { return base_t::to_iter(_idx); }
    INLINE c_iterator to_iter( sz_t _idx ) const      { return base_t::to_iter(_idx); }

    //
    INLINE result_t resize( sz_t _new_size ) { return base_t::resize(_new_size); }
    INLINE bool empty() const { return base_t::empty(); }
    INLINE sz_t size() const { return base_t::size(); }
    INLINE sz_t max_size() const { return base_t::max_size(); }

    //
    INLINE iterator erase( iterator _pos ) { return base_t::erase( _pos ); }
    INLINE iterator erase( iterator _first, iterator _last ) { return base_t::erase( _first, _last ); }
    INLINE result_t erase( const key_t& _key ) { return base_t::erase_unique(_key); }

    //
    INLINE void clear() { base_t::clear(); }
    INLINE void swap( self_t& _container ) { base_t::swap( _container ); }

    //
    INLINE Pair<sz_t,result_t> insert( const value_t& _val ) { return base_t::InsertUnique(_val); }

    //
    INLINE iterator find( const key_t& _key ) { return base_t::find_unique(_key); }
    INLINE c_iterator find( const key_t& _key ) const { return base_t::find_unique(_key); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const { return base_t::template to_str<FLAGS>(); } // NOTE: check comments abount T_ObjToString in exlibs/String/String.h for detail

}; // end class HashSet 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END HASHSET_H_1281840526
// #################################################################################
