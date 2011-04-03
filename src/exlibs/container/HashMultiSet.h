// ======================================================================================
// File         : HashMultiSet.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 10:48:34 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASHMULTISET_H_1281840515
#define HASHMULTISET_H_1281840515
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
// class HashMultiSet
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename VALUE, typename HASH_FUNC = Hash<VALUE>, typename EQUAL_KEY = EqualTo<VALUE>, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class HashMultiSet : protected HashPool< VALUE, VALUE, HASH_FUNC, Identity<VALUE>, EQUAL_KEY, TAllocator_T >
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    typedef HashMultiSet< VALUE, HASH_FUNC, EQUAL_KEY, TAllocator_T > self_t;
    typedef HashPool< VALUE, VALUE, HASH_FUNC, Identity<VALUE>, EQUAL_KEY, TAllocator_T > base_t;
    typedef VALUE key_t;          
    typedef VALUE value_t;          

    //
	typedef typename base_t::sz_t                   sz_t;           
	typedef typename base_t::ptr_t                  ptr_t;            
	typedef typename base_t::const_ptr_t            const_ptr_t;       
	typedef typename base_t::ref_t                  ref_t;          
	typedef typename base_t::const_ref_t            const_ref_t;     
	typedef typename base_t::index_allocator_t      index_allocator_t;
	typedef typename base_t::node_allocator_t       node_allocator_t;


    ///////////////////////////////////////////////////////////////////////////////
    // class HashMultiSetIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashMultiSetIterator : public base_t::iterator
    {
    public:
        typedef HashMultiSetIterator  iter_self_t;
        typedef typename base_t::iterator   iter_base_t;

    public:
        HashMultiSetIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        value_t& operator * () const { return (iter_base_t::m_pNode->value).value; }
    }; // end class HashMultiSetIterator 

    ///////////////////////////////////////////////////////////////////////////////
    // class HashMultiSetConstIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashMultiSetConstIterator : public base_t::c_iterator
    {
    public:
        typedef HashMultiSetConstIterator     iter_self_t;
        typedef typename base_t::c_iterator      iter_base_t;

    public:
        HashMultiSetConstIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        const value_t& operator * () const { return (iter_base_t::m_pNode->value).value; }
    }; // end class HashMultiSetConstIterator 

    // iterator typedefs
    typedef class HashMultiSetIterator                  iterator;           
    typedef class HashMultiSetConstIterator             c_iterator;      
    typedef std::reverse_iterator<iterator>             r_iterator;
    typedef std::reverse_iterator<c_iterator>           c_r_iterator;

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
    INLINE sz_t erase( const key_t& _key ) { return base_t::erase_equal(_key); }

    //
    INLINE void clear() { base_t::clear(); }
    INLINE void swap( self_t& _container ) { base_t::swap( _container ); }

    //
    INLINE sz_t insert( const value_t& _val ) { return base_t::InsertEqual(_val); }

    //
    INLINE void find( const key_t& _key, Array<iterator>* _pResult ) { return base_t::find_equal(_key,_pResult); }
    INLINE void find( const key_t& _key, Array<c_iterator>* _pResult ) const { return base_t::find_equal(_key,_pResult); }

}; // end class HashMultiSet 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END HASHMULTISET_H_1281840515
// #################################################################################
