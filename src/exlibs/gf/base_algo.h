// ======================================================================================
// File         : base_algo.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 11:46:28 AM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef BASE_ALGO_H_1281757592
#define BASE_ALGO_H_1281757592
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "pattern/Functor.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: for_each 
// ------------------------------------------------------------------

template < typename InputIter_T, typename T >
INLINE void for_each( InputIter_T _first, InputIter_T _last, Functor<void,Seq<T> > _functor )
{
    for ( ; _first != _last; ++_first )
        _functor(*_first);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename InputIter_T, typename T >
INLINE InputIter_T find( InputIter_T _first, InputIter_T _last, const T& _val )
{
    return std::find(_first, _last, _val);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename InputIter_T, typename T >
INLINE InputIter_T find_if( InputIter_T _first, InputIter_T _last, Functor<void,Seq<T> > _functor )
{
    return std::find_if( _first, _last, _functor );
}

// ------------------------------------------------------------------
// Desc: sort 
// ------------------------------------------------------------------

// ========================================================
// 2 params
// ========================================================

template < typename InputIter_T >
INLINE void sort ( InputIter_T _first, InputIter_T _last )
{
    std::sort( _first, _last );
}

// ========================================================
// 3 params
// ========================================================

template < typename InputIter_T, typename Compare_F >
INLINE void sort ( InputIter_T _first, InputIter_T _last, Compare_F _comp )
{
    std::sort( _first, _last, _comp );
}

// ------------------------------------------------------------------ 
// Desc: stable_sort 
// ------------------------------------------------------------------ 

// ========================================================
// 2 params
// ========================================================

template < typename InputIter_T >
INLINE void stable_sort ( InputIter_T _first, InputIter_T _last )
{
    std::stable_sort( _first, _last );
}

// ========================================================
// 3 params
// ========================================================

template < typename InputIter_T, typename Compare_F >
INLINE void stable_sort ( InputIter_T _first, InputIter_T _last, Compare_F _comp )
{
    std::stable_sort( _first, _last, _comp );
}

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END BASE_ALGO_H_1281757592
// #################################################################################
