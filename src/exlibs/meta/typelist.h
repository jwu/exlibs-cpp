// ======================================================================================
// File         : TypeList.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:08:54 AM | Tuesday,August
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
// The author or Addison-Welsey Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// #################################################################################
#ifndef TYPELIST_H_1250525342
#define TYPELIST_H_1250525342
// #################################################################################

// #########################
namespace ex { 
// #########################


///////////////////////////////////////////////////////////////////////////////
// class TypeList 
// 
// Purpose: 
// The building block of typelists of any length
// Use it through the LOKI_TYPELIST_NN macros
// Defines nested types:
//     Head (first element, a non-typelist type by convention)
//     Tail (second element, can be another typelist)
// 
///////////////////////////////////////////////////////////////////////////////

template < class T, class U >
struct TypeList
{
   typedef T head_t;
   typedef U tail_t;
}; // end class TypeList


///////////////////////////////////////////////////////////////////////////////
// TypeList utility algorithms
///////////////////////////////////////////////////////////////////////////////


// #########################
namespace typelist { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class MakeTypeList 
// 
// Purpose: 
// Takes a number of arguments equal to its numeric suffix
// The arguments are type names.
// MakeTypeList<T1, T2, ...>::result_t
// returns a typeList that is of T1, T2, ...
// 
///////////////////////////////////////////////////////////////////////////////


// ========================================================
// general
// ========================================================

template
<
    typename T1  = NullType, typename T2  = NullType, typename T3  = NullType,
    typename T4  = NullType, typename T5  = NullType, typename T6  = NullType,
    typename T7  = NullType, typename T8  = NullType, typename T9  = NullType,
    typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
    typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
    typename T16 = NullType, typename T17 = NullType, typename T18 = NullType
> 
struct MakeTypeList
{
private:
    typedef typename MakeTypeList
    <
        T2 , T3 , T4 , 
        T5 , T6 , T7 , 
        T8 , T9 , T10, 
        T11, T12, T13,
        T14, T15, T16, 
        T17, T18
    >
    ::result_t tail_result_t;

public:
    typedef TypeList<T1, tail_result_t> result_t;

}; // end struct MakeTypeList

// ========================================================
// nulltype 
// ========================================================

template <>
struct MakeTypeList<>
{
    typedef NullType result_t;
}; // end class MakeTypeList

///////////////////////////////////////////////////////////////////////////////
// class length
// 
// Purpose: 
// Computes the length of a typelist
// Invocation (TypeList_T is a typelist):
// length<TypeList_T>::value
// returns a compile-time constant containing the length of TypeList_T, not counting
//     the end terminator (which by convention is NullType)
// 
///////////////////////////////////////////////////////////////////////////////

template < class TypeList_T > struct length;
template <> struct length<NullType> { enum { value = 0 }; };
template < class T, class U > struct length< TypeList<T, U> > { enum { value = 1 + length<U>::value }; };

///////////////////////////////////////////////////////////////////////////////
// class TypeAt 
// 
// Purpose: 
// Finds the type at a given index in a typelist
// Invocation (TypeList_T is a typelist and index is a compile-time integral 
//     constant):
// TypeAt<TypeList_T, index>::result_t
// returns the type in position 'index' in TypeList_T
// If you pass an out-of-bounds index, the result is a compile-time error
// 
///////////////////////////////////////////////////////////////////////////////

template < class TypeList_T, uint index > struct TypeAt;
template < class Head, class Tail > struct TypeAt<TypeList<Head, Tail>, 0> { typedef Head result_t; };
template < class Head, class Tail, uint i > struct TypeAt<TypeList<Head, Tail>, i> { typedef typename TypeAt<Tail, i - 1>::result_t result_t; };

///////////////////////////////////////////////////////////////////////////////
// class TypeAtNonStrict
// 
// Purpose: 
// Finds the type at a given index in a typelist
// Invocations (TypeList_T is a typelist and index is a compile-time integral 
//     constant):
// a) TypeAt<TypeList_T, index>::result_t
// returns the type in position 'index' in TypeList_T, or NullType if index is 
//     out-of-bounds
// b) TypeAt<TypeList_T, index, D>::result_t
// returns the type in position 'index' in TypeList_T, or D if index is out-of-bounds
// 
///////////////////////////////////////////////////////////////////////////////

//
template < class TypeList_T, uint index, typename DefaultType = NullType > 
struct TypeAtNonStrict 
{ 
    typedef DefaultType result_t; 
};

//
template < class Head, class Tail, typename DefaultType > 
struct TypeAtNonStrict<TypeList<Head, Tail>, 0, DefaultType> 
{
    typedef Head result_t; 
};

//
template < class Head, class Tail, uint i, typename DefaultType > 
struct TypeAtNonStrict<TypeList<Head, Tail>, i, DefaultType> 
{ 
    typedef typename TypeAtNonStrict<Tail, i - 1, DefaultType>::result_t result_t; 
};

///////////////////////////////////////////////////////////////////////////////
// class IndexOf
// 
// Purpose: 
// Finds the index of a type in a typelist
// Invocation (TypeList_T is a typelist and T is a type):
// IndexOf<TypeList_T, T>::value
// returns the position of T in TypeList_T, or NullType if T is not found in TypeList_T
// 
///////////////////////////////////////////////////////////////////////////////


//
template <class TypeList_T, class T> struct IndexOf;

//
template <class T> 
struct IndexOf<NullType, T> 
{ 
    enum { value = -1 }; 
};

//
template <class T, class Tail> 
struct IndexOf<TypeList<T, Tail>, T> 
{ 
    enum { value = 0 }; 
};

//
template <class Head, class Tail, class T>
struct IndexOf<TypeList<Head, Tail>, T>
{
private:
    enum { temp = IndexOf<Tail, T>::value };
public:
    enum { value = (temp == -1 ? -1 : 1 + temp) };
};

///////////////////////////////////////////////////////////////////////////////
// class Append 
// 
// Purpose: 
// Appends a type or a typelist to another
// Invocation (TypeList_T is a typelist and T is either a type or a typelist):
// Append<TypeList_T, T>::result_t
// returns a typelist that is TypeList_T followed by T and NullType-terminated
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T, class T> struct Append;

//
template <> 
struct Append<NullType, NullType>
{
    typedef NullType result_t;
};

//
template <class T> 
struct Append<NullType, T>
{
    typedef TypeList<T,NullType> result_t;
};

//
template <class Head, class Tail>
struct Append<NullType, TypeList<Head, Tail> >
{
    typedef TypeList<Head, Tail> result_t;
};

//
template <class Head, class Tail, class T>
struct Append<TypeList<Head, Tail>, T>
{
    typedef TypeList<Head, typename Append<Tail, T>::result_t> result_t;
};
        
///////////////////////////////////////////////////////////////////////////////
// class erase 
// 
// Purpose: 
// Erases the first occurence, if any, of a type in a typelist
// Invocation (TypeList_T is a typelist and T is a type):
// erase<TypeList_T, T>::result_t
// returns a typelist that is TypeList_T without the first occurence of T
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T, class T> struct erase;

// Specialization 1
template <class T>
struct erase<NullType, T>
{
    typedef NullType result_t;
};

// Specialization 2
template <class T, class Tail>
struct erase<TypeList<T, Tail>, T>
{
    typedef Tail result_t;
};

// Specialization 3
template <class Head, class Tail, class T>
struct erase<TypeList<Head, Tail>, T>
{
    typedef TypeList<Head, typename erase<Tail, T>::result_t> result_t;
};

////////////////////////////////////////////////////////////////////////////////
// class template EraseAll
// Erases all first occurences, if any, of a type in a typelist
// Invocation (TypeList_T is a typelist and T is a type):
// EraseAll<TypeList_T, T>::result_t
// returns a typelist that is TypeList_T without any occurence of T
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class EraseAll 
// 
// Purpose: 
// Erases all first occurences, if any, of a type in a typelist
// Invocation (TypeList_T is a typelist and T is a type):
// EraseAll<TypeList_T, T>::result_t
// returns a typelist that is TypeList_T without any occurence of T
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T, class T> struct EraseAll;

//
template <class T>
struct EraseAll<NullType, T>
{
    typedef NullType result_t;
};

//
template <class T, class Tail>
struct EraseAll<TypeList<T, Tail>, T>
{
    // Go all the way down the list removing the type
    typedef typename EraseAll<Tail, T>::result_t result_t;
};

//
template <class Head, class Tail, class T>
struct EraseAll<TypeList<Head, Tail>, T>
{
    // Go all the way down the list removing the type
    typedef TypeList<Head, typename EraseAll<Tail, T>::result_t> result_t;
};

///////////////////////////////////////////////////////////////////////////////
// class NoDuplicates 
// 
// Purpose: 
// Removes all duplicate types in a typelist
// Invocation (TypeList_T is a typelist):
// NoDuplicates<TypeList_T, T>::result_t
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T> struct NoDuplicates;

//
template <> 
struct NoDuplicates<NullType>
{
    typedef NullType result_t;
};

//
template <class Head, class Tail>
struct NoDuplicates< TypeList<Head, Tail> >
{
private:
    typedef typename NoDuplicates<Tail>::result_t L1;
    typedef typename erase<L1, Head>::result_t L2;
public:
    typedef TypeList<Head, L2> result_t;
};

///////////////////////////////////////////////////////////////////////////////
// class Replace 
// 
// Purpose: 
// Replaces the first occurence of a type in a typelist, with another type
// Invocation (TypeList_T is a typelist, T, U are types):
// Replace<TypeList_T, T, U>::result_t
// returns a typelist in which the first occurence of T is replaced with U
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T, class T, class U> struct Replace;

//
template <class T, class U>
struct Replace<NullType, T, U>
{
    typedef NullType result_t;
};

//
template <class T, class Tail, class U>
struct Replace<TypeList<T, Tail>, T, U>
{
    typedef TypeList<U, Tail> result_t;
};

//
template <class Head, class Tail, class T, class U>
struct Replace<TypeList<Head, Tail>, T, U>
{
    typedef TypeList<Head, typename Replace<Tail, T, U>::result_t> result_t;
};

///////////////////////////////////////////////////////////////////////////////
// class ReplaceAll 
// 
// Purpose: 
// Replaces all occurences of a type in a typelist, with another type
// Invocation (TypeList_T is a typelist, T, U are types):
// Replace<TypeList_T, T, U>::result_t
// returns a typelist in which all occurences of T is replaced with U
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T, class T, class U> struct ReplaceAll;

//
template <class T, class U>
struct ReplaceAll<NullType, T, U>
{
    typedef NullType result_t;
};

//
template <class T, class Tail, class U>
struct ReplaceAll<TypeList<T, Tail>, T, U>
{
    typedef TypeList<U, typename ReplaceAll<Tail, T, U>::result_t> result_t;
};

//
template <class Head, class Tail, class T, class U>
struct ReplaceAll<TypeList<Head, Tail>, T, U>
{
    typedef TypeList<Head, typename ReplaceAll<Tail, T, U>::result_t> result_t;
};

///////////////////////////////////////////////////////////////////////////////
// class Reverse 
// 
// Purpose: 
// Reverses a typelist
// Invocation (TypeList_T is a typelist):
// Reverse<TypeList_T>::result_t
// returns a typelist that is TypeList_T reversed
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T> struct Reverse;

//
template <>
struct Reverse<NullType>
{
    typedef NullType result_t;
};

//
template <class Head, class Tail>
struct Reverse< TypeList<Head, Tail> >
{
    typedef typename Append< typename Reverse<Tail>::result_t, Head>::result_t result_t;
};

///////////////////////////////////////////////////////////////////////////////
// class MostDerived
// 
// Purpose: 
// Finds the type in a typelist that is the most derived from a given type
// Invocation (TypeList_T is a typelist, T is a type):
// MostDerived<TypeList_T, T>::result_t
// returns the type in TypeList_T that's the most derived from T
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T, class T> struct MostDerived;

//
template <class T>
struct MostDerived<NullType, T>
{
    typedef T result_t;
};

//
template <class Head, class Tail, class T>
struct MostDerived<TypeList<Head, Tail>, T>
{
private:
    typedef typename MostDerived<Tail, T>::result_t candidate_t;
public:
    typedef typename typeop::Select< EX_IS_SUPERSUB_CLASS(candidate_t,Head), Head, candidate_t >::result_t result_t;
};

///////////////////////////////////////////////////////////////////////////////
// class DerivedToFront
// 
// Purpose: 
// Arranges the types in a typelist so that the most derived types appear first
// Invocation (TypeList_T is a typelist):
// DerivedToFront<TypeList_T>::result_t
// returns the reordered TypeList_T 
// 
///////////////////////////////////////////////////////////////////////////////

//
template <class TypeList_T> struct DerivedToFront;

//
template <>
struct DerivedToFront<NullType>
{
    typedef NullType result_t;
};

//
template <class Head, class Tail>
struct DerivedToFront< TypeList<Head, Tail> >
{
private:
    typedef typename MostDerived<Tail, Head>::result_t the_most_derived_t;
    typedef typename Replace<Tail, the_most_derived_t, Head>::result_t temp_t; 
    typedef typename DerivedToFront<temp_t>::result_t derived_to_front_t;
public:
    typedef TypeList<the_most_derived_t, derived_to_front_t> result_t;
};
        
// #########################
} // end namespace typelist 
// #########################


///////////////////////////////////////////////////////////////////////////////
// class Seq 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// general ver.
// ========================================================

template
<
    class T01=NullType,class T02=NullType,class T03=NullType,class T04=NullType,class T05=NullType,
    class T06=NullType,class T07=NullType,class T08=NullType,class T09=NullType,class T10=NullType,
    class T11=NullType,class T12=NullType,class T13=NullType,class T14=NullType,class T15=NullType,
    class T16=NullType,class T17=NullType,class T18=NullType,class T19=NullType,class T20=NullType
>
struct Seq
{
private:
    typedef typename Seq< T02, T03, T04, T05, T06, T07, T08, T09, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20>::typelist_t tail_t;
public:
    typedef TypeList<T01, tail_t> typelist_t;
}; // end struct Seq
    
// ========================================================
// null ver.
// ========================================================

template<> struct Seq<> { typedef NullType typelist_t; }; // end struct Seq<>


// #########################
} // end namespace ex 
// #########################

// use Seq instead of EX_TYPELIST macro, it would be more clear, and compile faster
#define EX_DISABLE_TYPELIST_MACROS 1
#ifndef EX_DISABLE_TYPELIST_MACROS

///////////////////////////////////////////////////////////////////////////////
// TypeList help macros
//      macros LOKI_TYPELIST_1, LOKI_TYPELIST_2, ... LOKI_TYPELIST_50
//      Each takes a number of arguments equal to its numeric suffix
//      The arguments are type names. LOKI_TYPELIST_NN generates a typelist containing 
//          all types passed as arguments, in that order.
//      Example: LOKI_TYPELIST_2(char, int) generates a type containing char and int.
///////////////////////////////////////////////////////////////////////////////

#define EX_TYPELIST_1(T1) ::ex::TypeList<T1, ::ex::NullType>

#define EX_TYPELIST_2(T1, T2) ::ex::TypeList<T1, EX_TYPELIST_1(T2) >

#define EX_TYPELIST_3(T1, T2, T3) ::ex::TypeList<T1, EX_TYPELIST_2(T2, T3) >

#define EX_TYPELIST_4(T1, T2, T3, T4) \
    ::ex::TypeList<T1, EX_TYPELIST_3(T2, T3, T4) >

#define EX_TYPELIST_5(T1, T2, T3, T4, T5) \
    ::ex::TypeList<T1, EX_TYPELIST_4(T2, T3, T4, T5) >

#define EX_TYPELIST_6(T1, T2, T3, T4, T5, T6) \
    ::ex::TypeList<T1, EX_TYPELIST_5(T2, T3, T4, T5, T6) >

#define EX_TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) \
    ::ex::TypeList<T1, EX_TYPELIST_6(T2, T3, T4, T5, T6, T7) >

#define EX_TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) \
    ::ex::TypeList<T1, EX_TYPELIST_7(T2, T3, T4, T5, T6, T7, T8) >

#define EX_TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
    ::ex::TypeList<T1, EX_TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9) >

#define EX_TYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) \
    ::ex::TypeList<T1, EX_TYPELIST_9(T2, T3, T4, T5, T6, T7, T8, T9, T10) >

#define EX_TYPELIST_11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) \
    ::ex::TypeList<T1, EX_TYPELIST_10(T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) >

#define EX_TYPELIST_12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) \
    ::ex::TypeList<T1, EX_TYPELIST_11(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12) >

#define EX_TYPELIST_13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) \
    ::ex::TypeList<T1, EX_TYPELIST_12(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13) >

#define EX_TYPELIST_14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14) \
    ::ex::TypeList<T1, EX_TYPELIST_13(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14) >

#define EX_TYPELIST_15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15) \
    ::ex::TypeList<T1, EX_TYPELIST_14(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15) >

#define EX_TYPELIST_16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16) \
    ::ex::TypeList<T1, EX_TYPELIST_15(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16) >

#define EX_TYPELIST_17(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17) \
    ::ex::TypeList<T1, EX_TYPELIST_16(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17) >

#define EX_TYPELIST_18(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18) \
    ::ex::TypeList<T1, EX_TYPELIST_17(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18) >

#define EX_TYPELIST_19(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19) \
    ::ex::TypeList<T1, EX_TYPELIST_18(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19) >

#define EX_TYPELIST_20(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) \
    ::ex::TypeList<T1, EX_TYPELIST_19(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) >

#define EX_TYPELIST_21(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) \
    ::ex::TypeList<T1, EX_TYPELIST_20(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) >

#define EX_TYPELIST_22(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) \
    ::ex::TypeList<T1, EX_TYPELIST_21(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) >

#define EX_TYPELIST_23(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) \
    ::ex::TypeList<T1, EX_TYPELIST_22(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) >

#define EX_TYPELIST_24(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) \
    ::ex::TypeList<T1, EX_TYPELIST_23(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) >

#define EX_TYPELIST_25(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) \
    ::ex::TypeList<T1, EX_TYPELIST_24(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25) >

#define EX_TYPELIST_26(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26) \
    ::ex::TypeList<T1, EX_TYPELIST_25(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26) >

#define EX_TYPELIST_27(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27) \
    ::ex::TypeList<T1, EX_TYPELIST_26(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27) >

#define EX_TYPELIST_28(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28) \
    ::ex::TypeList<T1, EX_TYPELIST_27(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28) >

#define EX_TYPELIST_29(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29) \
    ::ex::TypeList<T1, EX_TYPELIST_28(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29) >

#define EX_TYPELIST_30(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) \
    ::ex::TypeList<T1, EX_TYPELIST_29(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) >

#define EX_TYPELIST_31(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) \
    ::ex::TypeList<T1, EX_TYPELIST_30(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) >

#define EX_TYPELIST_32(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) \
    ::ex::TypeList<T1, EX_TYPELIST_31(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) >

#define EX_TYPELIST_33(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) \
    ::ex::TypeList<T1, EX_TYPELIST_32(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) >

#define EX_TYPELIST_34(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) \
    ::ex::TypeList<T1, EX_TYPELIST_33(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) >

#define EX_TYPELIST_35(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35) \
    ::ex::TypeList<T1, EX_TYPELIST_34(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35) >

#define EX_TYPELIST_36(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36) \
    ::ex::TypeList<T1, EX_TYPELIST_35(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36) >

#define EX_TYPELIST_37(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37) \
    ::ex::TypeList<T1, EX_TYPELIST_36(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37) >

#define EX_TYPELIST_38(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38) \
    ::ex::TypeList<T1, EX_TYPELIST_37(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38) >

#define EX_TYPELIST_39(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39) \
    ::ex::TypeList<T1, EX_TYPELIST_38(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39) >

#define EX_TYPELIST_40(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) \
    ::ex::TypeList<T1, EX_TYPELIST_39(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) >

#define EX_TYPELIST_41(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) \
    ::ex::TypeList<T1, EX_TYPELIST_40(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) >

#define EX_TYPELIST_42(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) \
    ::ex::TypeList<T1, EX_TYPELIST_41(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) >

#define EX_TYPELIST_43(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) \
    ::ex::TypeList<T1, EX_TYPELIST_42(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) >

#define EX_TYPELIST_44(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) \
    ::ex::TypeList<T1, EX_TYPELIST_43(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) >

#define EX_TYPELIST_45(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45) \
    ::ex::TypeList<T1, EX_TYPELIST_44(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45) >

#define EX_TYPELIST_46(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46) \
    ::ex::TypeList<T1, EX_TYPELIST_45(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46) >

#define EX_TYPELIST_47(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47) \
    ::ex::TypeList<T1, EX_TYPELIST_46(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47) >

#define EX_TYPELIST_48(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48) \
    ::ex::TypeList<T1, EX_TYPELIST_47(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48) >

#define EX_TYPELIST_49(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48, T49) \
    ::ex::TypeList<T1, EX_TYPELIST_48(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48, T49) >

#define EX_TYPELIST_50(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50) \
    ::ex::TypeList<T1, EX_TYPELIST_49(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
        T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
        T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
        T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50) >

#endif // end ifndef EX_DISABLE_TYPELIST_MACROS

// #################################################################################
#endif // END TYPELIST_H_1250525342
// #################################################################################

