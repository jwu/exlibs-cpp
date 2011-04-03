// ======================================================================================
// File         : Delegate.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:10:07 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DELEGATE_H_1250525410
#define DELEGATE_H_1250525410
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// base classes 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class _private::CDummyInit
// 
// Purpose: 
//
// Note:    Can't put the CDummyInit in the TStaticDelegateBase class, Compile error in gcc
// 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private {
// #########################

    class CDummyInit {}; // end class CDummyInit

// #########################
}; // end namespace _private 
// #########################


///////////////////////////////////////////////////////////////////////////////
// class CDelegateBase 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class CDelegateBase
{
public:
    //
    void Reset()
    {
        m_DelegateInfo.FunctionInfo.pVtable      = NULL;
        m_DelegateInfo.FunctionInfo.pObject      = NULL;
        m_DelegateInfo.FunctionInfo.pFunction    = NULL;
        m_DelegateInfo.FunctionInfo.pData        = NULL;
    }

    //
    operator bool () const { return m_DelegateInfo.FunctionInfo.pVtable != NULL; } 

protected:
    //
    union UDelegateInfo
    {
        struct SFunctionInfo
        {
            void* pVtable;
            void* pObject;
            void* pFunction;
            void* pData;
            void* pHack;
        }; // end struct SFunctionInfo 
        SFunctionInfo   FunctionInfo;
        uint8           Data[sizeof(SFunctionInfo)];

    }; // end union UDelegateInfo

    //
    UDelegateInfo   m_DelegateInfo;

    ///////////////////////////////////////////////////////////////////////////////
    // generics function 
    ///////////////////////////////////////////////////////////////////////////////
public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        string = string + "vtable: " + to_str<FLAGS>(m_DelegateInfo.FunctionInfo.pVtable) + "\n";
        string = string + "object: " + to_str<FLAGS>(m_DelegateInfo.FunctionInfo.pObject) + "\n";
        string = string + "function: " + to_str<FLAGS>(m_DelegateInfo.FunctionInfo.pFunction) + "\n";
        string = string + "data: " + to_str<FLAGS>(m_DelegateInfo.FunctionInfo.pData) + "\n";
        return string;
    }

}; // end class CDelegateBase 

///////////////////////////////////////////////////////////////////////////////
// class TStaticDelegateBase 
// 
// Purpose: 
//      Since the Functor objects are the only entities held by the caller, 
//      they must contain the data about the callee. 
//      With some care we can design a base class which can hold, in a typeless manner, 
//      the callee data, regardless of whether the callee is a ptr-to-function or object/ptr-to-member-function combo:
// 
///////////////////////////////////////////////////////////////////////////////

template < typename RETURN_T >
class TStaticDelegateBase
{
public:
    typedef RETURN_T ( TStaticDelegateBase::*MemberFuncPtr_t ) ();
    typedef RETURN_T ( *NormalFuncPtr_t ) ();

    /**
     * Default Constructor
     */
    TStaticDelegateBase()
        : Callee(NULL),
          NormalFuncPtr(NULL)
    {
    }

    /**
     * Constructor
     */
    TStaticDelegateBase( const void* _pObj, const void* _pFunc, size_t _func_size )
    {
        if ( _pObj ) // must be callee/memfunc
        {
            Callee = (void*)_pObj;
            ex::memcpy( MemberFuncPtr, _pFunc, _func_size );
        }
        else // must be ptr-to-func
        {
            NormalFuncPtr = _pFunc;
        }
    }

    // for evaluation in conditions will be changed to bool when bool exists
    operator bool () const { return (NormalFuncPtr||Callee); }


    ///////////////////////////////////////////////////////////////////
    // Note: this code depends on all ptr-to-mem-funcs being same size
    // If that is not the case then make memFunc as large as largest
    ///////////////////////////////////////////////////////////////////
    union
    {
        const void* NormalFuncPtr;
        char MemberFuncPtr[sizeof(MemberFuncPtr_t)];
    }; // end union
    void*   Callee;

}; // end class TStaticDelegateBase 

///////////////////////////////////////////////////////////////////////////////
// (n)Params delegate defines  
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// 0 params
// ========================================================

#define _CLASS_NAME          TDelegate0
#define _CLASS_NAME_STATIC   TStaticDelegate0
#define _CLASS_NAME_NORMAL   TStaticDelegate0_Normal
#define _CLASS_NAME_MEMBER   TStaticDelegate0_Member
#define _TEMPLATE_TYPES
#define _USE_TYPES
#define _DECLARE_PARAMS
#define _USE_PARAMS
#define _TEMPLATE_DUMMY_TYPES
#define _USE_DUMMY_TYPES

// ========================================================
// comma def for 0 params
// ========================================================

#define _COMMA_TEMPLATE_TYPES
#define _COMMA_TEMPLATE_DUMMY_TYPES
#define _COMMA_USE_TYPES
#define _COMMA_USE_DUMMY_TYPES
#define _COMMA_DECLARE_PARAMS
#define _COMMA_USE_PARAMS

#include "DelegateImplements.h"

// ========================================================
// comma def for multi-params
// ========================================================

#undef _COMMA_TEMPLATE_TYPES
#undef _COMMA_TEMPLATE_DUMMY_TYPES
#undef _COMMA_USE_TYPES
#undef _COMMA_USE_DUMMY_TYPES
#undef _COMMA_DECLARE_PARAMS
#undef _COMMA_USE_PARAMS

#define _COMMA_TEMPLATE_TYPES           , _TEMPLATE_TYPES
#define _COMMA_USE_TYPES                , _USE_TYPES 
#define _COMMA_DECLARE_PARAMS           , _DECLARE_PARAMS
#define _COMMA_USE_PARAMS               , _USE_PARAMS    
#define _COMMA_TEMPLATE_DUMMY_TYPES     , _TEMPLATE_DUMMY_TYPES
#define _COMMA_USE_DUMMY_TYPES          , _USE_DUMMY_TYPES 

// ========================================================
// 1 params
// ========================================================

#define _CLASS_NAME              TDelegate1
#define _CLASS_NAME_STATIC       TStaticDelegate1
#define _CLASS_NAME_NORMAL       TStaticDelegate1_Normal
#define _CLASS_NAME_MEMBER       TStaticDelegate1_Member
#define _TEMPLATE_TYPES          typename T1
#define _USE_TYPES               T1
#define _DECLARE_PARAMS          T1 _p1
#define _USE_PARAMS              _p1
#define _TEMPLATE_DUMMY_TYPES    typename DUMMY_T1
#define _USE_DUMMY_TYPES         DUMMY_T1

#include "DelegateImplements.h"

// ========================================================
// 2 params
// ========================================================

#define _CLASS_NAME              TDelegate2
#define _CLASS_NAME_STATIC       TStaticDelegate2
#define _CLASS_NAME_NORMAL       TStaticDelegate2_Normal
#define _CLASS_NAME_MEMBER       TStaticDelegate2_Member
#define _TEMPLATE_TYPES          typename T1, typename T2
#define _USE_TYPES               T1, T2
#define _DECLARE_PARAMS          T1 _p1, T2 _p2
#define _USE_PARAMS              _p1, _p2
#define _TEMPLATE_DUMMY_TYPES    typename DUMMY_T1, typename DUMMY_T2
#define _USE_DUMMY_TYPES         DUMMY_T1, DUMMY_T2

#include "DelegateImplements.h"

// ========================================================
// 3 params
// ========================================================

#define _CLASS_NAME              TDelegate3
#define _CLASS_NAME_STATIC       TStaticDelegate3
#define _CLASS_NAME_NORMAL       TStaticDelegate3_Normal
#define _CLASS_NAME_MEMBER       TStaticDelegate3_Member
#define _TEMPLATE_TYPES          typename T1, typename T2, typename T3
#define _USE_TYPES               T1, T2, T3
#define _DECLARE_PARAMS          T1 _p1, T2 _p2, T3 _p3
#define _USE_PARAMS              _p1, _p2, _p3
#define _TEMPLATE_DUMMY_TYPES    typename DUMMY_T1, typename DUMMY_T2, typename DUMMY_T3
#define _USE_DUMMY_TYPES         DUMMY_T1, DUMMY_T2, DUMMY_T3

#include "DelegateImplements.h"

// ========================================================
// 4 params
// ========================================================

#define _CLASS_NAME              TDelegate4
#define _CLASS_NAME_STATIC       TStaticDelegate4
#define _CLASS_NAME_NORMAL       TStaticDelegate4_Normal
#define _CLASS_NAME_MEMBER       TStaticDelegate4_Member
#define _TEMPLATE_TYPES          typename T1, typename T2, typename T3, typename T4
#define _USE_TYPES               T1, T2, T3, T4
#define _DECLARE_PARAMS          T1 _p1, T2 _p2, T3 _p3, T4 _p4
#define _USE_PARAMS              _p1, _p2, _p3, _p4
#define _TEMPLATE_DUMMY_TYPES    typename DUMMY_T1, typename DUMMY_T2, typename DUMMY_T3, typename DUMMY_T4
#define _USE_DUMMY_TYPES         DUMMY_T1, DUMMY_T2, DUMMY_T3, DUMMY_T4

#include "DelegateImplements.h"

// ========================================================
// 5 params
// ========================================================

#define _CLASS_NAME              TDelegate5
#define _CLASS_NAME_STATIC       TStaticDelegate5
#define _CLASS_NAME_NORMAL       TStaticDelegate5_Normal
#define _CLASS_NAME_MEMBER       TStaticDelegate5_Member
#define _TEMPLATE_TYPES          typename T1, typename T2, typename T3, typename T4, typename T5
#define _USE_TYPES               T1, T2, T3, T4, T5
#define _DECLARE_PARAMS          T1 _p1, T2 _p2, T3 _p3, T4 _p4, T5 _p5
#define _USE_PARAMS              _p1, _p2, _p3, _p4, _p5
#define _TEMPLATE_DUMMY_TYPES    typename DUMMY_T1, typename DUMMY_T2, typename DUMMY_T3, typename DUMMY_T4, typename DUMMY_T5
#define _USE_DUMMY_TYPES         DUMMY_T1, DUMMY_T2, DUMMY_T3, DUMMY_T4, DUMMY_T5

#include "DelegateImplements.h"

// ========================================================
// 6 params
// ========================================================

#define _CLASS_NAME              TDelegate6
#define _CLASS_NAME_STATIC       TStaticDelegate6
#define _CLASS_NAME_NORMAL       TStaticDelegate6_Normal
#define _CLASS_NAME_MEMBER       TStaticDelegate6_Member
#define _TEMPLATE_TYPES          typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
#define _USE_TYPES               T1, T2, T3, T4, T5, T6
#define _DECLARE_PARAMS          T1 _p1, T2 _p2, T3 _p3, T4 _p4, T5 _p5, T6 _p6
#define _USE_PARAMS              _p1, _p2, _p3, _p4, _p5, _p6
#define _TEMPLATE_DUMMY_TYPES    typename DUMMY_T1, typename DUMMY_T2, typename DUMMY_T3, typename DUMMY_T4, typename DUMMY_T5, typename DUMMY_T6
#define _USE_DUMMY_TYPES         DUMMY_T1, DUMMY_T2, DUMMY_T3, DUMMY_T4, DUMMY_T5, DUMMY_T6

#include "DelegateImplements.h"


// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END DELEGATE_H_1250525410
// #################################################################################
