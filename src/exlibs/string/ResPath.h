// ======================================================================================
// File         : ResPath.h
// Author       : Wu Jie 
// Last Change  : 04/13/2010 | 22:29:54 PM | Tuesday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef RESPATH_H_1271169005
#define RESPATH_H_1271169005
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "Path.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class ResPath 
// 
// Purpose: 
//   repo://foo/bar/readme.txt
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class ResPath : public Path<T,TAllocator_T>
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    typedef Path< T, TAllocator_T > base_t;
    typedef ResPath <T, TAllocator_T > self_t;
    typedef StringID <T> str_id_t;

    //
	typedef typename base_t::pair_t        pair_t;          
	typedef typename base_t::sz_t          sz_t;          
    typedef typename base_t::value_t       value_t;       
	typedef typename base_t::ptr_t         ptr_t;         
	typedef typename base_t::const_ptr_t   const_ptr_t;   
	typedef typename base_t::ref_t         ref_t;         
	typedef typename base_t::const_ref_t   const_ref_t;   
	typedef typename base_t::allocator_t   allocator_t;   

    //
    typedef typename base_t::iterator           iterator;      
    typedef typename base_t::r_iterator          r_iterator;     
    typedef typename base_t::c_iterator      c_iterator; 
    typedef typename base_t::c_r_iterator     c_r_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    explicit ResPath()
        : base_t()
    {
    }

    //
    ResPath( const self_t& _path )
        : base_t(_path)
    {
    }

    //
    template < typename U, template <class> class TAllocator_U >
    ResPath( const ResPath<U,TAllocator_U>& _path )
        : base_t( _path )
    {
    }

    //
    template < typename U, template <class> class TAllocator_U >
    ResPath( const Path<U,TAllocator_U>& _path )
        : base_t(_path)
    {
        InternalCheck();
    }

    //
    template < typename U, template <class> class TAllocator_U >
    ResPath( const String<U,TAllocator_U>& _string )
        : base_t( _string.c_str() )
    {
        InternalCheck();
    }

    // 
    ResPath( const T* _c_str )
        : base_t( _c_str )
    {
        InternalCheck();
    }

    // 
    ~ResPath()
    {
    }

    //
    // repo://foo/bar/readme.txt = repo + foo/bar/readme.txt
    pair_t splitRepo () const
    {
        pair_t pair;
        sz_t idx = find ( Gen_TString<T>("://") );
        if ( idx == sz_t(ex::IndexNone) )
        {
            pair.first = self_t(*this);
            pair.second = self_t("");
        }
        else
        {
            pair.first = subpath(0,idx);
            pair.second = subpath(idx+3);
        }
        return pair;
    }

    // return the head (repo-name) part of a path.
    base_t repoName () const
    {
        pair_t result = this->splitRepo ();
        return result.first;
    }

    // return the tail (path-name) part of a path
    base_t pathName () const
    {
        pair_t result = this->splitRepo ();
        return result.second;
    }

    //
    str_id_t resTypeID () const;

    //
    str_id_t id () const 
    {
        return str_id_t( this->c_str() );
    }

    //
    base_t rawfile () const;
    base_t srcfile () const;
    base_t binfile () const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void InternalCheck ()
    {
        ex_assert ( this->find( Gen_TString<T>("://") ) != sz_t(ex::IndexNone), "invalid res-path!" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        return *this;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("ResPath");
        return strID;
    }

}; // end class ResPath

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END RESPATH_H_1271169005
// #################################################################################
