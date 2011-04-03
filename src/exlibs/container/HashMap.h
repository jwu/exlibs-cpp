// ======================================================================================
// File         : HashMap.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 11:29:22 AM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASHMAP_H_1281756578
#define HASHMAP_H_1281756578
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
// class HashMap
// 
// Purpose: 
// Note: using EX_DEFAULT_CONTAINER_ALLOCATOR((Pair<const KEY,VALUE>)) will
//       lead to a compile error in gcc
///////////////////////////////////////////////////////////////////////////////
 
template < typename KEY, 
           typename VALUE, 
           typename HASH_FUNC = Hash<KEY>, 
           typename EQUAL_KEY = EqualTo<KEY>, 
           template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class HashMap : protected HashPool< KEY, Pair<const KEY,VALUE>, HASH_FUNC, Select_1st< Pair<const KEY,VALUE> >, EQUAL_KEY, TAllocator_T >
{

    ///////////////////////////////////////////////////////////////////////////////
    // public typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    typedef HashMap< KEY, 
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
    // class HashMapIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashMapIterator : public base_t::iterator
    {
    public:
        typedef HashMapIterator       iter_self_t;
        typedef typename base_t::iterator   iter_base_t;

    public:
        HashMapIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        value_t& operator * () const { return ((iter_base_t::m_pNode->value).value).second; }
        const key_t& key() const { return ((iter_base_t::m_pNode->value).value).first; }
        const pair_t& pair() const { return (iter_base_t::m_pNode->value).value; }
    }; // end class HashMapIterator 

    ///////////////////////////////////////////////////////////////////////////////
    // class HashMapRIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashMapRIterator : public base_t::r_iterator
    {
    public:
        typedef HashMapRIterator       iter_self_t;
        typedef typename base_t::r_iterator   iter_base_t;

    public:
        HashMapRIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        value_t& operator * () const { return ((*iter_base_t::base()).value).second; }
        const key_t& key() const { return ((*iter_base_t::base()).value).first; }
        const pair_t& pair() const { return (*iter_base_t::base()).value; }
    }; // end class HashMapRIterator 

    ///////////////////////////////////////////////////////////////////////////////
    // class HashMapConstIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashMapConstIterator : public base_t::c_iterator
    {
    public:
        typedef HashMapConstIterator          iter_self_t;
        typedef typename base_t::c_iterator     iter_base_t;

    public:
        HashMapConstIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        const value_t& operator * () const { return ((iter_base_t::m_pNode->value).value).second; }
        const key_t& key() const { return ((iter_base_t::m_pNode->value).value).first; }
        const pair_t& pair() const { return (iter_base_t::m_pNode->value).value; }
    }; // end class HashMapConstIterator 

    ///////////////////////////////////////////////////////////////////////////////
    // class HashMapRConstIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class HashMapRConstIterator : public base_t::c_r_iterator
    {
    public:
        typedef HashMapRConstIterator          iter_self_t;
        typedef typename base_t::c_r_iterator     iter_base_t;

    public:
        HashMapRConstIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        const value_t& operator * () const { return ((*iter_base_t::base()).value).second; }
        const key_t& key() const { return ((*iter_base_t::base()).value).first; }
        const pair_t& pair() const { return (*iter_base_t::base()).value; }
    }; // end class HashMapRConstIterator 

    //
    typedef class HashMapIterator               iterator;           
    typedef class HashMapConstIterator          c_iterator;      
    typedef class HashMapRIterator              r_iterator;           
    typedef class HashMapRConstIterator         c_r_iterator;      

public:
    //
	typedef typename base_t::sz_t                   sz_t;           
	typedef typename base_t::ptr_t                  ptr_t;            
	typedef typename base_t::const_ptr_t            const_ptr_t;       
	typedef typename base_t::ref_t                  ref_t;          
	typedef typename base_t::const_ref_t            const_ref_t;     
	typedef typename base_t::index_allocator_t      index_allocator_t;
	typedef typename base_t::node_allocator_t       node_allocator_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    HashMap( sz_t _size = 16 )
        : base_t(_size)
    {
    }

    //
    HashMap( const self_t& _copy )
        : base_t(_copy)
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE bool operator == ( const self_t& _comp ) const 
    { 
        if ( size() != _comp.size() ) 
            return false;

        c_iterator it_mine = begin();
        for ( ; it_mine != end(); ++it_mine )
        {
            c_iterator it_yours = _comp.find(it_mine.key());
            if ( it_yours == _comp.end() ) // confirm the key can find the value.
                return false;
            if ( *it_mine != *it_yours ) // check the value is the same
                return false;
        }

        return true;
    }
    INLINE bool operator != ( const self_t& _comp ) const { return !(this->operator == (_comp)); }

    //
    INLINE value_t& operator [] ( const key_t& _key )
    {
        iterator iter = find (_key);
        if ( iter != end() )
            return *iter;

        Pair<sz_t,result_t> result = insert ( _key, value_t() );
        return *(to_iter (result.first));
    }

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
    INLINE Pair<sz_t,result_t> insert( const key_t& _key, const value_t& _val ) { return base_t::InsertUnique(pair_t(_key,_val)); }
    INLINE Pair<sz_t,result_t> insert( const pair_t& _pair ) { return base_t::InsertUnique(_pair); }

    //
    INLINE iterator find( const key_t& _key ) { return base_t::find_unique(_key); }
    INLINE c_iterator find( const key_t& _key ) const { return base_t::find_unique(_key); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        // NOTE: the HashMapPool store the early item at the end.
        string_t string;
        for ( c_iterator iter = begin(); iter != end(); ++iter )
        {
            string = string + "[" + ex::to_str<FLAGS>(iter.key()) + "]: " + ex::to_str<FLAGS>((*iter)) + "\n";
        }
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("HashMap");
        return strID;
    }

}; // end class HashMap 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END HASHMAP_H_1281756578
// #################################################################################

