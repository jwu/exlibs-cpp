// ======================================================================================
// File         : StaticDelegate.hpp
// Author       : Wu Jie 
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// (n) Parameter Delegator 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class TStaticDelegate(n)
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename RETURN_T _COMMA_TEMPLATE_TYPES >
class _CLASS_NAME_STATIC : protected TStaticDelegateBase<RETURN_T>
{
public:
    // types
    typedef RETURN_T (*pfn_t) (_DECLARE_PARAMS);

public:
    // use this to avoid default constructor
    _CLASS_NAME_STATIC ( ex::_private::CDummyInit * _pDummy = 0 )
        : TStaticDelegateBase<RETURN_T>()
    {
    }

    //
    void operator() ( _DECLARE_PARAMS ) const
    {
        m_InternalCallback( *this _COMMA_USE_PARAMS );
    }

    //
    TStaticDelegateBase<RETURN_T>::operator bool;

protected:
    typedef void (*InternalCallbackPtr_t)( const TStaticDelegateBase<RETURN_T>& _COMMA_USE_TYPES );

    _CLASS_NAME_STATIC( InternalCallbackPtr_t _internal_callback, void* _pObj, const void* _pFunc, size_t _func_size )
        : TStaticDelegateBase<RETURN_T>( _pObj, _pFunc, _func_size ),
          m_InternalCallback(_internal_callback)
    {
    }

private:
    InternalCallbackPtr_t m_InternalCallback;   

}; // end class TStaticDelegate(n)

///////////////////////////////////////////////////////////////////////////////
// class TStaticDelegate(n)_Normal
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename RETURN_T _COMMA_TEMPLATE_TYPES, typename NORMAL_FUNC >
class _CLASS_NAME_NORMAL : public _CLASS_NAME_STATIC<RETURN_T _COMMA_USE_TYPES> 
{
public:
    _CLASS_NAME_NORMAL( const NORMAL_FUNC& _func )
        : _CLASS_NAME_STATIC<RETURN_T _COMMA_USE_TYPES>( InternalCallback, NULL, (const void*)_func, 0 )
    {
    }

    //
    // InternalCallback
    //
    static void InternalCallback( const TStaticDelegateBase<RETURN_T>& _delegate _COMMA_DECLARE_PARAMS )
    {
        (NORMAL_FUNC(_delegate.NormalFuncPtr)) (_USE_PARAMS);
    }

}; // end class TStaticDelegate(n)_Normal 

///////////////////////////////////////////////////////////////////////////////
// class TStaticDelegate(n)_Member
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename RETURN_T _COMMA_TEMPLATE_TYPES, typename CALLEE_T, typename MEMBER_FUNC >
class _CLASS_NAME_MEMBER : public _CLASS_NAME_STATIC<RETURN_T _COMMA_USE_TYPES>
{
public:
    _CLASS_NAME_MEMBER( CALLEE_T& _obj, const MEMBER_FUNC& _member_func )
        : _CLASS_NAME_STATIC<RETURN_T _COMMA_USE_TYPES>( InternalCallback, &_obj, &_member_func, sizeof(_member_func) )
    {
    }

    //
    // InternalCallback
    //
    static void InternalCallback( const TStaticDelegateBase<RETURN_T>& _delegate _COMMA_DECLARE_PARAMS )
    {
        CALLEE_T* pCallee = (CALLEE_T*)_delegate.Callee;
        MEMBER_FUNC &member_func(*(MEMBER_FUNC*)(void*)(_delegate.MemberFuncPtr));
        (pCallee->*member_func)(_USE_PARAMS);
    }
}; // end class TStaticDelegate(n)_Member 

// ------------------------------------------------------------------
// Desc: T_MakeDelegate (n params) 
// ------------------------------------------------------------------

// ========================================================
// normal func delegate
// ========================================================

template < typename DUMMY_RETURN_T _COMMA_TEMPLATE_DUMMY_TYPES, typename RETURN_T _COMMA_TEMPLATE_TYPES >
INLINE _CLASS_NAME_NORMAL<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES, RETURN_T(*)(_USE_TYPES)> 
    T_MakeDelegate( _CLASS_NAME_STATIC<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES>*, RETURN_T(*_func_ptr)(_USE_TYPES) )
{
    return _CLASS_NAME_NORMAL<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES, RETURN_T(*)(_USE_TYPES)>(_func_ptr);
}

// ========================================================
// member func delegate
// ========================================================

template < typename DUMMY_RETURN_T _COMMA_TEMPLATE_DUMMY_TYPES, typename DUMMY_CALLEE_T, typename RETURN_T, typename CALLEE_T _COMMA_TEMPLATE_TYPES >
INLINE _CLASS_NAME_MEMBER<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES, DUMMY_CALLEE_T, RETURN_T(CALLEE_T::*)(_USE_TYPES)> 
    T_MakeDelegate( _CLASS_NAME_STATIC<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES>*, DUMMY_CALLEE_T& _obj, RETURN_T(CALLEE_T::* const &_func_ptr)(_USE_TYPES) )
{
    typedef RETURN_T(CALLEE_T::*MemberFuncPtr_t)(_USE_TYPES);
    return _CLASS_NAME_MEMBER<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES, DUMMY_CALLEE_T, MemberFuncPtr_t>( _obj, _func_ptr );
}

// ========================================================
// const member func delegate
// ========================================================

template < typename DUMMY_RETURN_T _COMMA_TEMPLATE_DUMMY_TYPES, typename DUMMY_CALLEE_T, typename RETURN_T, typename CALLEE_T _COMMA_TEMPLATE_TYPES >
INLINE _CLASS_NAME_MEMBER<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES, const DUMMY_CALLEE_T, RETURN_T(CALLEE_T::*)(_USE_TYPES)const> 
    T_MakeDelegate( _CLASS_NAME_STATIC<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES>*, const DUMMY_CALLEE_T& _obj, RETURN_T(CALLEE_T::* const &_func_ptr)(_USE_TYPES)const )
{
    typedef RETURN_T(CALLEE_T::*MemberFuncPtr_t)(_USE_TYPES)const;
    return _CLASS_NAME_MEMBER<DUMMY_RETURN_T _COMMA_USE_DUMMY_TYPES, const DUMMY_CALLEE_T, MemberFuncPtr_t>( _obj, _func_ptr );
}
