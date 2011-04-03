// ======================================================================================
// File         : HashMultiMap.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 10:48:30 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASHMULTIMAP_H_1281837486
#define HASHMULTIMAP_H_1281837486
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "Pair.h"
#include "HashPool.h"
#include "pattern/functors.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class HashMultiMap
// 
// Purpose: 
// Note: using EX_DEFAULT_CONTAINERALLOCATOR((Pair<const KEY,VALUE>)) will
//       lead to a compile error in gcc
///////////////////////////////////////////////////////////////////////////////
 
template < typename KEY, 
           typename VALUE, 
           typename HASH_FUNC = Hash<KEY>, 
           typename EQUAL_KEY = EqualTo<KEY>, 
           template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class HashMultiMap : protected HashPool< KEY, Pair<const KEY,VALUE>, HASH_FUNC, Select_1st< Pair<const KEY,VALUE> >, EQUAL_KEY, TAllocator_T >
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    typedef HashMultiMap< KEY, 
                          VALUE, 
                          HASH_FUNC, 
                          EQUAL_KEY,
                          TAllocator_T > self_t;
    typedef HashPool< KEY, 
                      Pair<const KEY,VALUE>, 
                      HASH_FUNC, 
                      Select_1st< Pair<const KEY,VALUE> >,
                      EQUAL_KEY, 
                      TAllocator_T > base_t;
    typedef KEY key_t;          
    typedef VALUE value_t;          
    typedef Pair<const KEY,VALUE> pair_t;          

public:

    ///////////////////////////////////////////////////////////////////////////////
    // class HashMultiMapIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashMultiMapIterator : public base_t::iterator
    {
    public:
        typedef HashMultiMapIterator  iter_self_t;
        typedef typename base_t::iterator   iter_base_t;

    public:
        HashMultiMapIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        value_t& operator * () const { return ((iter_base_t::m_pNode->value).value).second; }
        const key_t& key() const { return ((iter_base_t::m_pNode->value).value).first; }
    }; // end class HashMultiMapIterator 

    ///////////////////////////////////////////////////////////////////////////////
    // class HashMultiMapConstIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashMultiMapConstIterator : public base_t::c_iterator
    {
    public:
        typedef HashMultiMapConstIterator     iter_self_t;
        typedef typename base_t::c_iterator      iter_base_t;

    public:
        HashMultiMapConstIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        const value_t& operator * () const { return ((iter_base_t::m_pNode->value).value).second; }
        const key_t& key() const { return ((iter_base_t::m_pNode->value).value).first; }
    }; // end class HashMultiMapConstIterator 

    //
    typedef class HashMultiMapIterator                  iterator;           
    typedef class HashMultiMapConstIterator             c_iterator;      
    typedef std::reverse_iterator<iterator>             r_iterator;
    typedef std::reverse_iterator<c_iterator>           c_r_iterator;

public:
    //
	typedef typename base_t::sz_t               sz_t;           
	typedef typename base_t::ptr_t              ptr_t;            
	typedef typename base_t::const_ptr_t        const_ptr_t;       
	typedef typename base_t::ref_t              ref_t;          
	typedef typename base_t::const_ref_t        const_ref_t;     
	typedef typename base_t::index_allocator_t  index_allocator_t;
	typedef typename base_t::node_allocator_t   node_allocator_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    HashMultiMap( sz_t _size = 256 )
        : base_t(_size)
    {
    }

    //
    HashMultiMap( const self_t& _copy )
        : base_t(_copy)
    {
    }


    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
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
    INLINE result_t erase( const key_t& _key ) { return base_t::erase_equal(_key); }

    //
    INLINE void clear() { base_t::clear(); }
    INLINE void swap( self_t& _container ) { base_t::swap( _container ); }

    //
    INLINE sz_t insert( const key_t& _key, const value_t& _val ) { return base_t::InsertEqual(pair_t(_key,_val)); }
    INLINE sz_t insert( const pair_t& _pair ) { return base_t::InsertEqual(_pair); }

    //
    INLINE void find( const key_t& _key, Array<typename base_t::iterator>* _pResult ) { return base_t::find_equal(_key,_pResult); }
    INLINE void find( const key_t& _key, Array<typename base_t::c_iterator>* _pResult ) const { return base_t::find_equal(_key,_pResult); }


    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        c_iterator iter       = this->begin();
        c_iterator iterEnd    = this->end();
        for ( ; iter != iterEnd; ++iter )
        {
            string = string + "key: " + ex::to_str<FLAGS>(iter.key()) + "value: " + ex::to_str<FLAGS>((*iter)) + "\n";
        }
        return string;
    }

}; // end class HashMultiMap 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END HASHMULTIMAP_H_1281837486
// #################################################################################
