// ======================================================================================
// File         : TypeTraits.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:09:35 AM | Tuesday,August
// Description  : 
// ======================================================================================

////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Wesley Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// #################################################################################
#ifndef TYPETRAITS_H_1250525379
#define TYPETRAITS_H_1250525379
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class IsCustomUInt 
// 
// Purpose: 
// Offers a means to integrate nonstandard built-in unsigned integral types
// (such as unsigned __int64 or unsigned long long int) with the TypeTraits 
//     class template defined below.
// Invocation: IsCustomUInt<T> where T is any type
// Defines 'value', an enum that is 1 iff T is a custom built-in unsigned
//     integral type
//
// Use:
// Specialize this class template for nonstandard unsigned integral types
//     and define value = 1 in those specializations
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct IsCustomUInt
{
    enum { Result = false };
}; // end struct IsCustomUInt        

///////////////////////////////////////////////////////////////////////////////
// class IsCustomInt 
// 
// Purpose: 
// Offers a means to integrate nonstandard built-in unsigned integral types
// (such as unsigned __int64 or unsigned long long int) with the TypeTraits 
//     class template defined below.
// Invocation: IsCustomInt<T> where T is any type
// Defines 'value', an enum that is 1 iff T is a custom built-in signed
//     integral type
//
// Use:
// Specialize this class template for nonstandard unsigned integral types
//     and define value = 1 in those specializations
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct IsCustomInt
{
    enum { Result = false };
}; // end struct IsCustomInt

///////////////////////////////////////////////////////////////////////////////
// class TIsCustomFloat
// 
// Purpose: 
// Offers a means to integrate nonstandard floating point types with the
//     TypeTraits class template defined below.
// Invocation: isCustomFloat<T> where T is any type
// Defines 'value', an enum that is 1 iff T is a custom built-in
//     floating point type
//
// Use:
// Specialize this class template for nonstandard unsigned integral types
//     and define value = 1 in those specializations
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct isCustomFloat
{
    enum { Result = false };
}; // end struct isCustomFloat

////////////////////////////////////////////////////////////////////////////////
// Helper types for class template TypeTraits defined below
////////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private {
// #########################

///////////////////////////////////////////////////////////////////////////////
// standard typedefs
///////////////////////////////////////////////////////////////////////////////

typedef Seq<uint,uint8,uint16,uint32,uint64>::typelist_t   uints_t;
typedef Seq<int,int8,int16,int32,int64>::typelist_t        ints_t;
typedef Seq<bool,BOOL>::typelist_t                         booleans_t;
typedef Seq<char,wchar>::typelist_t                        characters_t;
typedef Seq<const char*,const wchar*>::typelist_t          strings_t;
typedef Seq<float, double, long double>::typelist_t        floats_t;

///////////////////////////////////////////////////////////////////////////////
// IsFunctionPointerRaw
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template <typename T>
struct IsFunctionPointerRaw
{enum{Result = 0};};

// ------------------------------------------------------------------
// Desc: normal params 
// ------------------------------------------------------------------

template <typename T>
struct IsFunctionPointerRaw<T(*)()> 
{enum {Result = 1};};

template <typename T, 
    typename P01>
struct IsFunctionPointerRaw<T(*)(P01)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02>
struct IsFunctionPointerRaw<T(*)(
    P01, P02)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20)> 
{enum {Result = 1};};

// ------------------------------------------------------------------
// Desc: ... params 
// ------------------------------------------------------------------

template <typename T>
struct IsFunctionPointerRaw<T(*)(
    ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01>
struct IsFunctionPointerRaw<T(*)(
    P01, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15,
    ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, ...)> 
{enum {Result = 1};};

template <typename T, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsFunctionPointerRaw<T(*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20,
    ...)> 
{enum {Result = 1};};

///////////////////////////////////////////////////////////////////////////////
// IsMemberFunctionPointerRaw
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template <typename T>
struct IsMemberFunctionPointerRaw
{enum{Result = 0};};

// ------------------------------------------------------------------
// Desc: normal params
// ------------------------------------------------------------------

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)()> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20)> 
{enum {Result = 1};};

// ------------------------------------------------------------------
// Desc: ... params
// ------------------------------------------------------------------

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)(
    ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15,
    ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, ...)> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20,
    ...)> 
{enum {Result = 1};};

// ------------------------------------------------------------------
// Desc: const normal params
// ------------------------------------------------------------------

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)() const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20) const> 
{enum {Result = 1};};

// ------------------------------------------------------------------
// Desc: const ... params 
// ------------------------------------------------------------------

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)(
    ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15,
    ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, ...) const> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20,
    ...) const> 
{enum {Result = 1};};

// ------------------------------------------------------------------
// Desc: volatile normal params
// ------------------------------------------------------------------

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)() volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20) volatile> 
{enum {Result = 1};};

// ------------------------------------------------------------------
// Desc: volatile ... params
// ------------------------------------------------------------------

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)(
    ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15,
    ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, ...) volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20,
    ...) volatile> 
{enum {Result = 1};};

// ------------------------------------------------------------------
// Desc: const volatile normal params
// ------------------------------------------------------------------

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)() const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20) const volatile> 
{enum {Result = 1};};

// ------------------------------------------------------------------
// Desc: const volatile ... params
// ------------------------------------------------------------------

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)(
    ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05,
    P06, P07, P08, P09, P10,
    P11, P12, P13, P14, P15,
    ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, ...) const volatile> 
{enum {Result = 1};};

template <typename T, typename S, 
    typename P01, typename P02, typename P03, typename P04, typename P05,
    typename P06, typename P07, typename P08, typename P09, typename P10,
    typename P11, typename P12, typename P13, typename P14, typename P15,
    typename P16, typename P17, typename P18, typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, 
    P06, P07, P08, P09, P10, 
    P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20,
    ...) const volatile> 
{enum {Result = 1};};
        
////////////////////////////////////////////////////////////////////////////////
// class template TypeTraitsImpl
//
// Figures out at compile time various properties of any given type
// Invocations (T is a type, TypeTraitsImpl<T>::Propertie):
//
// - isPointer       : returns true if T is a pointer type
// - pointee_t       : returns the type to which T points if T is a pointer 
//                     type, NullType otherwise
// - isReference     : returns true if T is a reference type
// - referred_t      : returns the type to which T refers if T is a reference 
//                     type, remain T otherwise
// - isMemberPointer : returns true if T is a pointer to member type
// - isUnsignedInt   : returns true if T is a standard unsigned integral type
// - isSignedInt     : returns true if T is a standard signed integral type
// - isIntegral      : returns true if T is a standard integral type
// - isFloat         : returns true if T is a standard floating-point type
// - isArith         : returns true if T is a standard arithmetic type
// - IsFundamental   : returns true if T is a standard fundamental type
// - isUnsignedInt   : returns true if T is a unsigned integral type
// - isSignedInt     : returns true if T is a signed integral type
// - isIntegral      : returns true if T is a integral type
// - isFloat         : returns true if T is a floating-point type
// - isArith         : returns true if T is a arithmetic type
// - IsFundamental   : returns true if T is a fundamental type
// - ParameterType   : returns the optimal type to be used as a parameter for 
//                     functions that take Ts
// - isConst         : returns true if T is a const-qualified type
// - non_const_t     : Type with removed 'const' qualifier from T, if any
// - isVolatile      : returns true if T is a volatile-qualified type
// - non_volatile_t  : Type with removed 'volatile' qualifier from T, if any
// - unqualified_t   : Type with removed 'const' and 'volatile' qualifiers from 
//                     T, if any
// - parameter_t     : returns the optimal type to be used as a parameter 
//                       for functions that take 'const T's
//
////////////////////////////////////////////////////////////////////////////////

template < typename T >
class TypeTraitsImpl
{

    ///////////////////////////////////////////////////////////////////////////////
    // private parts 
    ///////////////////////////////////////////////////////////////////////////////

private:

    // ------------------------------------------------------------------
    // Desc: ReferenceTraits 
    // ------------------------------------------------------------------

    template <class U> struct ReferenceTraits
    {
        enum { Result = false };
        typedef U referred_t;
        typedef U& reference_t;
    };
    
    template <class U> struct ReferenceTraits<U&>
    {
        enum { Result = true };
        typedef U referred_t;
        typedef U& reference_t;
    };

    // ------------------------------------------------------------------
    // Desc: UnReference 
    // ------------------------------------------------------------------

    template <class U> struct UnReference
    {
        typedef U non_reference_t;
    };
    
    template <class U> struct UnReference<U&>
    {
        typedef U non_reference_t;
    };
           
    // ------------------------------------------------------------------
    // Desc: PointerTraits
    // ------------------------------------------------------------------

    template <class U> struct PointerTraits
    {
        enum { Result = false };
        typedef NullType pointee_t;
        typedef U* pointer_t;
    };
    
    template <class U> struct PointerTraits<U&>
    {
        enum { Result = false };
        typedef NullType pointee_t;
        typedef InvalidType pointer_t; // NOTE: pointer to reference is illegal
    };
    
    template <class U> struct PointerTraits<U*>
    {
        enum { Result = true };
        typedef U pointee_t;
        typedef U* pointer_t;
    };
    
    template <class U> struct PointerTraits<U*&>
    {
        enum { Result = true };
        typedef U pointee_t;
        typedef U* pointer_t;
    };

    // ------------------------------------------------------------------
    // Desc: UnPointer 
    // ------------------------------------------------------------------

    template <class U> struct UnPointer
    {
        typedef U non_pointer_t;
    };
    
    template <class U> struct UnPointer<U*>
    {
        typedef U non_pointer_t;
    };

    template <class U> struct UnPointer<U*&>
    {
        typedef U non_pointer_t;
    };

    // ------------------------------------------------------------------ 
    // Desc: ConstPointee 
    //  NOTE: includes the referred.
    //        when you write U*/U&, it will be const U*/const U&
    // ------------------------------------------------------------------ 

    template <class U> struct ConstPointee 
    {
        typedef const U const_pointee_t;
    };

    template <class U> struct ConstPointee <U&> 
    {
        typedef const U& const_pointee_t;
    };

    template <class U> struct ConstPointee <U*> 
    {
        typedef const U* const_pointee_t;
    };
    
    template <class U> struct ConstPointee<const U>
    {
        typedef const U const_pointee_t;
    };

    template <class U> struct ConstPointee<const U&>
    {
        typedef const U& const_pointee_t;
    };

    // ------------------------------------------------------------------ 
    // Desc: 
    //  NOTE: when U = U*, the const U will be U const *, which means the pointer
    //        will be const. so if you want const U*, you should write TypeTraitsImpl<TypeTraitsImpl<int>::const_pointee_t>::const_t
    // ------------------------------------------------------------------ 

    template <class U> struct Const
    {
        typedef const U const_t;
    };

    template <class U> struct Const<U&>
    {
        // NOTE: the const U when U = U& will write as U const & which lead to 
        //       Warnning C4181 in msvc "qualifier applied to reference type; ignored", 
        //       the U const & will be ignored, instead the compiler will use U&.
        typedef U& const_t; 
    };
    
    template <class U> struct Const<const U>
    {
        typedef const U const_t;
    };

    template <class U> struct Const<const U&>
    {
        typedef const U& const_t;
    };
     
    // ------------------------------------------------------------------
    // Desc: 
    // ------------------------------------------------------------------

    template <class U> struct UnConst
    {
        typedef U non_const_t;
        enum { isConst = false };
    };
    
    template <class U> struct UnConst<const U>
    {
        typedef U non_const_t;
        enum { isConst = true };
    };

    template <class U> struct UnConst<const U&>
    {
        typedef U& non_const_t;
        enum { isConst = true };
    };

    // ------------------------------------------------------------------
    // Desc: 
    // ------------------------------------------------------------------

    template <class U> struct Volatile
    {
        typedef volatile U volatile_t;
    };
   
    template <class U> struct Volatile<U&>
    {
        // NOTE: same as Const
        typedef U& volatile_t;
    };
   
    template <class U> struct Volatile<volatile U>
    {
        typedef volatile U volatile_t;
    };

    template <class U> struct Volatile<volatile U&>
    {
        typedef volatile U& volatile_t;
    };

    // ------------------------------------------------------------------
    // Desc: 
    // ------------------------------------------------------------------

    template <class U> struct UnVolatile
    {
        typedef U non_volatile_t;
        enum { isVolatile = false };
    };
   
    template <class U> struct UnVolatile<volatile U>
    {
        typedef U non_volatile_t;
        enum { isVolatile = true };
    };

    template <class U> struct UnVolatile<volatile U&>
    {
        typedef U& non_volatile_t;
        enum { isVolatile = true };
    };
      
    // ------------------------------------------------------------------
    // Desc: PToMTraits
    // ------------------------------------------------------------------

    template <class U> struct PToMTraits
    {
        enum { Result = false };
    };
    
    template <class U, class V> struct PToMTraits<U V::*>
    {
        enum { Result = true };
    };
    
    template <class U, class V> struct PToMTraits<U V::*&>
    {
        enum { Result = true };
    };
    
    // ------------------------------------------------------------------
    // Desc: FunctionPointerTraits
    // ------------------------------------------------------------------

    template <class U> struct FunctionPointerTraits
    {
        enum{ Result = _private::IsFunctionPointerRaw<U>::Result };
    };
    
    // ------------------------------------------------------------------
    // Desc: PToMFunctionTraits
    // ------------------------------------------------------------------

    template <typename U> struct PToMFunctionTraits
    {
        enum{ Result = _private::IsMemberFunctionPointerRaw<U>::Result };
    };

    ///////////////////////////////////////////////////////////////////////////////
    // public parts 
    ///////////////////////////////////////////////////////////////////////////////
    
public:

    // ======================================================== 
    // pre-typedefs 
    // ======================================================== 

    //
    typedef typename Const<T>::const_t const_t;
    typedef typename UnConst<T>::non_const_t non_const_t;
    typedef typename ConstPointee<T>::const_pointee_t const_pointee_t;

    typedef typename Volatile<T>::volatile_t volatile_t;
    typedef typename UnVolatile<T>::non_volatile_t non_volatile_t;
    typedef typename UnVolatile<typename UnConst<T>::non_const_t>::non_volatile_t unqualified_t;

    typedef typename PointerTraits<unqualified_t>::pointee_t pointee_t;
    typedef typename PointerTraits<T>::pointer_t pointer_t;
    typedef typename UnPointer<T>::non_pointer_t non_pointer_t;

    typedef typename ReferenceTraits<T>::referred_t referred_t;
    typedef typename ReferenceTraits<T>::reference_t reference_t;
    typedef typename UnReference<T>::non_reference_t non_reference_t;

    // ======================================================== 
    // judge functions 
    // ======================================================== 

    //
    enum { isConst                  = UnConst<T>::isConst };
    enum { isVolatile               = UnVolatile<T>::isVolatile };
    enum { isReference              = ReferenceTraits<unqualified_t>::Result };
    enum { isFunction               = FunctionPointerTraits<typename typeop::TypeToPointer<T>::type_t >::Result };
    enum { isFunctionPointer        = FunctionPointerTraits< typename ReferenceTraits<unqualified_t>::referred_t >::Result };
    enum { isMemberFunctionPointer  = PToMFunctionTraits< typename ReferenceTraits<unqualified_t>::referred_t >::Result };
    enum { isMemberPointer          = PToMTraits< typename ReferenceTraits<unqualified_t>::referred_t >::Result || isMemberFunctionPointer };
    enum { isPointer                = PointerTraits< typename ReferenceTraits<unqualified_t>::referred_t >::Result || isFunctionPointer };

    //
    enum { isBooleans       = typelist::IndexOf<_private::booleans_t, unqualified_t>::value >= 0 || typelist::IndexOf<_private::booleans_t, typename ReferenceTraits<unqualified_t>::referred_t>::value >= 0 };
    enum { isUnsignedInt    = typelist::IndexOf<_private::uints_t, unqualified_t>::value >= 0 || typelist::IndexOf<_private::uints_t, typename ReferenceTraits<unqualified_t>::referred_t>::value >= 0 };
    enum { isSignedInt      = typelist::IndexOf<_private::ints_t, unqualified_t>::value >= 0 || typelist::IndexOf<_private::ints_t, typename ReferenceTraits<unqualified_t>::referred_t>::value >= 0 };
    enum { isCharacter      = typelist::IndexOf<_private::characters_t, unqualified_t>::value >= 0 || typelist::IndexOf<_private::characters_t, typename ReferenceTraits<unqualified_t>::referred_t>::value >= 0 };
    enum { isIntegral       = isUnsignedInt || isSignedInt || isCharacter };
    enum { isFloat          = typelist::IndexOf<_private::floats_t, unqualified_t>::value >= 0 || typelist::IndexOf<_private::floats_t, typename ReferenceTraits<unqualified_t>::referred_t>::value >= 0};
    enum { isArith          = isIntegral || isFloat || isBooleans };
    enum { isAtomic         = isArith || typeop::Conversion<T,void>::IsSameType };
    enum { isEnum           = false };

    //
    enum { isString         = typelist::IndexOf<_private::strings_t, unqualified_t>::value >= 0 || typelist::IndexOf<_private::strings_t, typename ReferenceTraits<unqualified_t>::referred_t>::value >= 0 };
            
    //
    enum { isCustomUnsignedInt    = isUnsignedInt || IsCustomUInt<unqualified_t>::Result };
    enum { isCustomSignedInt      = isSignedInt || IsCustomInt<unqualified_t>::Result };
    enum { isCustomIntegral       = isIntegral || isUnsignedInt || isSignedInt };
    enum { isCustomFloat          = isFloat || isCustomFloat<unqualified_t>::Result };
    enum { isCustomArith          = isCustomIntegral || isCustomFloat };
    enum { isCustomAtomic         = isAtomic };

    // 
    enum { needConstructor        = !isAtomic || !isPointer };

    //
    static INLINE const string_id_t& type_name () { return T::type_name(); }
    
    // ======================================================== 
    // post-typedefs 
    // ======================================================== 

    // parameter_t
    typedef typename typeop::Select<isArith || isPointer || isMemberPointer, T, typename typeop::TypeToParam<T>::type_t>::result_t parameter_t;

}; // end class TypeTraitsImpl
       
// #########################
} // end namespace _private 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class TypeTraits 
// 
// Purpose: 
// NOTE: template function can't partial specialize, that's why we use TypeTraits<T>::type_name () 
//       instead of TTypeName<T>() directly.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class TypeTraits : public _private::TypeTraitsImpl<T>
{
}; // end class TypeTraits 

///////////////////////////////////////////////////////////////////////////////
// fwd-decls
///////////////////////////////////////////////////////////////////////////////

// atomic
template <> class TypeTraits<bool>;
template <> class TypeTraits<int>;
template <> class TypeTraits<uint>;
template <> class TypeTraits<int8>;
template <> class TypeTraits<int16>;
template <> class TypeTraits<int32>;
template <> class TypeTraits<int64>;
template <> class TypeTraits<uint8>;
template <> class TypeTraits<uint16>;
template <> class TypeTraits<uint32>;
template <> class TypeTraits<uint64>;
template <> class TypeTraits<float>;
template <> class TypeTraits<double>;
template <> class TypeTraits<char>;
template <> class TypeTraits<const char*>;
template <> class TypeTraits<const wchar*>;

// static array
template < typename T, uint SIZE > class TypeTraits<T[SIZE]>;

///////////////////////////////////////////////////////////////////////////////
// typeop defines after TypeTraits
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace typeop { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T > INLINE const string_id_t& type_name ( const T& _val ) { return TypeTraits<T>::type_name(); }

// ######################### 
} // end namespace typeop 
// ######################### 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END TYPETRAITS_H_1250525379
// #################################################################################
