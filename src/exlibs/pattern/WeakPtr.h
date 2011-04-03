// ======================================================================================
// File         : WeakPtr.h
// Author       : Wu Jie 
// Last Change  : 04/01/2010 | 21:22:02 PM | Thursday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef WEAKPTR_H_1270128124
#define WEAKPTR_H_1270128124
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SmartPtr_helpers.h"

///////////////////////////////////////////////////////////////////////////////
// temp helper macros 
///////////////////////////////////////////////////////////////////////////////

// other template
#define TEMPLATE_OTHER_DECL template < typename OTHER_T, \
                                       template <class> class TOwnerShip_OTHER_T >
#define TEMPLATE_OTHER_WEAK_PTR WeakPtr< OTHER_T, TOwnerShip_OTHER_T >

// compare template
#define TEMPLATE_COMPARE_DECL template < typename T, \
                                         template <class> class TOwnerShip_T, \
                                         typename U >
#define TEMPLATE_WEAK_PTR WeakPtr< T, TOwnerShip_T >


// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class WeakPtr 
// 
// Purpose: 
//  the weak_ptr in ex-libs do not have the weak-count, so it can only be create
//  from smart_ptr, and never handle destroy.
//  this is different than the weak-ptr in boost, which have both share-count and 
//  weak-count. It can destroy it self automatically when weak-count go to zero 
//  and no shared-use exits.
//  
//  a weak-ptr can become strong by pass itself as construtor parameter to smart-ptr.
//  aka. smart_ptr sp(weak_ptr);
//       smart_ptr sp = weak_ptr;
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T,
           template <class> class TOwnerShip_T = RefCounted >
class WeakPtr : public TOwnerShip_T<T>
{
    template < typename U,
               template <class> class TOwnerShip_U,
               void (*PFN) ( void* ) > friend class SmartPtr;

    ///////////////////////////////////////////////////////////////////////////////
    // member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    T*  m_pPointee;

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef T* ptr_t;
    typedef const T* const_ptr_t;
    typedef ptr_t& ptr_ref_t; // T* &
    typedef const ptr_t& const_ptr_ref_t; // T* const &, not miss understand as const T* const &
    typedef T& ref_t;
    typedef const T& const_ref_t;
    typedef WeakPtr< T, TOwnerShip_T > self_t;
    typedef TOwnerShip_T<T> owner_ship_t;
    typedef typename typeop::Select<owner_ship_t::DestructiveCopy, self_t, const self_t >::result_t copy_t;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    WeakPtr()
        : m_pPointee (NULL)
    {
        ConstructStaticAsserts();
    }

    //
    template < void (*PFN) (void*) >
    WeakPtr ( const SmartPtr<T,TOwnerShip_T,PFN>& _smartPtr )
        : owner_ship_t (_smartPtr)
        , m_pPointee (_smartPtr.m_pPointee)
    {
        ConstructStaticAsserts ();
    }

    //
    WeakPtr ( copy_t& _copy )
        : owner_ship_t (_copy)
        , m_pPointee (_copy.m_pPointee)
    {
        ConstructStaticAsserts ();
    }

    //
    WeakPtr& operator = ( copy_t& _copy )
    {
        WeakPtr temp(_copy);
        temp.swap(*this);
        return *this;
    }

    //
    template < void (*PFN) (void*) >
    WeakPtr& operator = ( const SmartPtr<T,TOwnerShip_T,PFN>& _smartPtr )
    {
        WeakPtr temp(_smartPtr);
        temp.swap(*this);
        return *this;
    }

    //
    template < void (*PFN) (void*) >
    WeakPtr& operator = ( SmartPtr<T,TOwnerShip_T,PFN>& _smartPtr )
    {
        WeakPtr temp(_smartPtr);
        temp.swap(*this);
        return *this;
    }

    //
    void swap( self_t& _rhs )
    {
        ex::value_swap( m_pPointee, _rhs.m_pPointee );
        owner_ship_t::swap(_rhs);
    }

    //
    ~WeakPtr()
    {
        // do nothing, I'm weak-ref
    }

    ///////////////////////////////////////////////////////////////////////////////
    // de-ref methods
    ///////////////////////////////////////////////////////////////////////////////

    //
    ptr_t operator -> ()
    {
        if ( this->count(m_pPointee) == 0  )
            return NULL;
        return m_pPointee;
    }

    const_ptr_t operator -> () const
    {
        if ( this->count(m_pPointee) == 0  )
            return NULL;
        return m_pPointee;
    }

    // NOTE: the static_cast can only detect if they are inherits relationship, but it doesn't know if down-cast valid
    template < typename CAST_T > CAST_T* cast () { return static_cast<CAST_T*> (m_pPointee); }
    template < typename CAST_T > const CAST_T* cast () const { return static_cast<const CAST_T*> (m_pPointee); }

    // get ptr
    INLINE ptr_t ptr() { return m_pPointee; }
    INLINE const_ptr_t ptr() const { return m_pPointee; }

    // get ptr_ref
    INLINE ptr_ref_t ptr_ref() { return m_pPointee; }
    INLINE const_ptr_ref_t ptr_ref() const { return m_pPointee; }

    ///////////////////////////////////////////////////////////////////////////////
    // compare functons
    ///////////////////////////////////////////////////////////////////////////////

    // Enables "if (!sp) ..."
    bool operator ! () const { return m_pPointee == NULL; }

    // compare with weak_ptr

    // operator ==
    TEMPLATE_OTHER_DECL
    INLINE bool operator == ( const TEMPLATE_OTHER_WEAK_PTR& _rhs ) const { return (*this).ptr() == _rhs.ptr(); }

    // operator !=
    TEMPLATE_OTHER_DECL
    INLINE bool operator != ( const TEMPLATE_OTHER_WEAK_PTR& _rhs ) const { return !( (*this).ptr() == _rhs.ptr() ); }

    // operator <
    TEMPLATE_OTHER_DECL
    INLINE bool operator < ( const TEMPLATE_OTHER_WEAK_PTR& _rhs ) const { return (*this).ptr() < _rhs.ptr(); }

    // operator >
    TEMPLATE_OTHER_DECL
    INLINE bool operator > ( const TEMPLATE_OTHER_WEAK_PTR& _rhs ) { return ( _rhs.ptr() < (*this).ptr() ); }

    // operator <=
    TEMPLATE_OTHER_DECL
    INLINE bool operator <= ( const TEMPLATE_OTHER_WEAK_PTR& _rhs ) { return !( _rhs.ptr() < (*this).ptr() ); }

    // operator >=
    TEMPLATE_OTHER_DECL
    INLINE bool operator >= ( const TEMPLATE_OTHER_WEAK_PTR& _rhs ) { return !( (*this).ptr() < _rhs.ptr() ); }

    // compare with smart_ptr

    // operator ==
    template < void (*PFN) (void*) >
    INLINE bool operator == ( const SmartPtr<T,TOwnerShip_T,PFN>& _rhs ) const { return (*this).ptr() == _rhs.ptr(); }

    // operator !=
    template < void (*PFN) (void*) >
    INLINE bool operator != ( const SmartPtr<T,TOwnerShip_T,PFN>& _rhs ) const { return !( (*this).ptr() == _rhs.ptr() ); }

    // operator <
    template < void (*PFN) (void*) >
    INLINE bool operator < ( const SmartPtr<T,TOwnerShip_T,PFN>& _rhs ) const { return (*this).ptr() < _rhs.ptr(); }

    // operator >
    template < void (*PFN) (void*) >
    INLINE bool operator > ( const SmartPtr<T,TOwnerShip_T,PFN>& _rhs ) { return ( _rhs.ptr() < (*this).ptr() ); }

    // operator <=
    template < void (*PFN) (void*) >
    INLINE bool operator <= ( const SmartPtr<T,TOwnerShip_T,PFN>& _rhs ) { return !( _rhs.ptr() < (*this).ptr() ); }

    // operator >=
    template < void (*PFN) (void*) >
    INLINE bool operator >= ( const SmartPtr<T,TOwnerShip_T,PFN>& _rhs ) { return !( (*this).ptr() < _rhs.ptr() ); }

private:
    // Helper for enabling 'if (sp)'
    struct SpToBool
    {
        SpToBool(int) {}
        void ValidPtr() {}
    }; // end strcut SpToBool
    typedef void (SpToBool::*sp_to_bool_t)();

public:
    // enable 'if (sp)'
    operator sp_to_bool_t () const { return !((*this).ptr()) ? NULL : &SpToBool::ValidPtr; }

private:
    // Helper for disallowing automatic conversion
    struct DisallowSpToPtr
    {
        DisallowSpToPtr(ptr_t) {}
    }; // 

public:        
    operator DisallowSpToPtr() const { return (*this).ptr(); }

    ///////////////////////////////////////////////////////////////////////////////
    // private member functions 
    ///////////////////////////////////////////////////////////////////////////////

private:

    //
    INLINE void ConstructStaticAsserts()
    {
        ex_static_assert( EX_IS_SUPERSUB_CLASS( OwnerShipHelper<T>, TOwnerShip_T<T> ), "TOwnerShip_T must inherits from OwnerShipHelper" );
    }

    // disable dereference
    ref_t operator*()
    {
        ex_static_assert( false, "Not allow use dereference" );
        ex_warning ( "dereference is not allowed" );
        return *this;
    }

    const_ref_t operator*() const
    {
        ex_static_assert( false, "Not allow use dereference" );
        ex_warning ( "dereference is not allowed" );
        return *this;
    }

}; // end class WeakPtr

///////////////////////////////////////////////////////////////////////////////
// free comparison operators for class template SmartPtr
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: sp == p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator == ( const TEMPLATE_WEAK_PTR& _sp, U* _p ) { return _sp.ptr() == _p; }

// ------------------------------------------------------------------
// Desc: p == sp
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator == ( U* _p, const TEMPLATE_WEAK_PTR& _sp ) { return _sp.ptr() == _p; }

// ------------------------------------------------------------------
// Desc: sp != p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator != ( const TEMPLATE_WEAK_PTR& _sp, U* _p ) { return !( _sp.ptr() == _p ); }
    
// ------------------------------------------------------------------
// Desc: p != sp
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator != ( U* _p, const TEMPLATE_WEAK_PTR& _sp ) { return _sp.ptr() != _p; }

// ------------------------------------------------------------------
// Desc: sp < p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator < ( const TEMPLATE_WEAK_PTR& _sp, U* _p ) { return _sp.ptr() < _p; }

// ------------------------------------------------------------------
// Desc: p < sp
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator < ( U* _p, const TEMPLATE_WEAK_PTR& _sp ) { return _sp.ptr() < _p; }

// ------------------------------------------------------------------
// Desc: sp > p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator > ( const TEMPLATE_WEAK_PTR& _sp, U* _p ) { return _p < _sp.ptr(); } 

// ------------------------------------------------------------------
// Desc: p > sp
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator > ( U* _p, const TEMPLATE_WEAK_PTR& _sp ) { return _sp.ptr() < _p; }
  
// ------------------------------------------------------------------
// Desc: sp <= p
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
inline bool operator <= ( const TEMPLATE_WEAK_PTR& _sp, U* _p ) { return !( _p < _sp.ptr() ); }
        
// ------------------------------------------------------------------
// Desc: operator<= for _lhs = raw pointer, _rhs = SmartPtr
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator <= ( U* _p, const TEMPLATE_WEAK_PTR& _sp ) { return !( _sp.ptr() < _p ); }

// ------------------------------------------------------------------
// Desc: sp >= p 
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator >= ( const TEMPLATE_WEAK_PTR& _sp, U* _p ) { return !( _sp.ptr() < _p ); }
        
// ------------------------------------------------------------------
// Desc: p >= sp 
// ------------------------------------------------------------------

TEMPLATE_COMPARE_DECL
INLINE bool operator>=( U* _p, const TEMPLATE_WEAK_PTR& _sp ) { return !( _p < _sp.ptr() ); }


// ######################### 
} // end namespace ex 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// undef temp macros 
///////////////////////////////////////////////////////////////////////////////

#undef TEMPLATE_OTHER_DECL
#undef TEMPLATE_OTHER_WEAK_PTR
#undef TEMPLATE_COMPARE_DECL
#undef TEMPLATE_WEAK_PTR

// #################################################################################
#endif // END WEAKPTR_H_1270128124
// #################################################################################


