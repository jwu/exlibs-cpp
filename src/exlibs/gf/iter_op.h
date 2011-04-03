// ======================================================================================
// File         : Iteratorop.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:50:11 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ITERATOROP_H_1250524215
#define ITERATOROP_H_1250524215
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// defines  
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename ForwardIter1_T, typename ForwardIter2_T >
INLINE void iter_swap( ForwardIter1_T _iter1, ForwardIter2_T _iter2 ) { std::iter_swap(_iter1,_iter2); }

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename InputIter_T, typename OutputIter_T >
INLINE OutputIter_T iter_copy( InputIter_T _first, InputIter_T _last, OutputIter_T _result ) { return std::copy( _first, _last, _result ); } 

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename BidIt1_T, typename BidIt2_T >
INLINE BidIt2_T iter_copy_backward( BidIt1_T _first, BidIt2_T _last, BidIt2_T _result ) { return std::copy_backward(_first, _last, _result ); }


// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename InputIter_T, typename Size_T, class OutputIter_T >
INLINE Pair<InputIter_T,OutputIter_T> iter_copyn( InputIter_T _first, Size_T _count, OutputIter_T _result )
{
    for ( ; _count > 0; --_count )
    {
        *_result = *_first;
        ++_first;
        ++_result;
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename ForwardIter_T, typename T >
INLINE void iter_fill( ForwardIter_T _first, ForwardIter_T _last, const T& _val ) { std::fill(_first, _last, _val); }

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename OutputIter_T, typename Size_T, typename T >
INLINE void iter_fill_n( OutputIter_T _first, Size_T _count, const T& _val ) { std::fill_n(_first,_count,_val); }

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// ========================================================
// 3 params
// ========================================================

template < typename InputIter1_T, typename InputIter2_T >
INLINE Pair<InputIter1_T,InputIter2_T> iter_mismatch( InputIter1_T _first1, InputIter1_T _last1, InputIter2_T _first2 ) { return std::mismatch(_first1,_last1,_first2); }

// ========================================================
// 4 params
// ========================================================

template < typename InputIter1_T, typename InputIter2_T, typename BinaryPredicate_T >
INLINE Pair<InputIter1_T,InputIter2_T> iter_mismatch( InputIter1_T _first1, InputIter1_T _last1, InputIter2_T _first2, BinaryPredicate_T _binary_pred ) 
{
    return std::mismatch(_first1,_last1,_first2,_binary_pred); 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// ========================================================
// 3 params
// ========================================================

template < typename InputIter1_T, typename InputIter2_T >
INLINE bool iter_equal( InputIter1_T _first1, InputIter1_T _last1, InputIter2_T _first2 ) { return std::equal(_first1,_last1,_first2); }

// ========================================================
// 4 params 
// ========================================================

template < typename InputIter1_T, typename InputIter2_T, typename BinaryPredicate_T >
INLINE bool iter_equal( InputIter1_T _first1, InputIter1_T _last1, InputIter2_T _first2, BinaryPredicate_T _binary_pred ) 
{
    return std::equal(_first1,_last1,_first2,_binary_pred); 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename InputIter_T, typename Distance_T >
INLINE void iter_distance( InputIter_T _first, InputIter_T _last, Distance_T& _n )
{
    _n = std::distance( _first, _last );
}


// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END ITERATOROP_H_1250524215
// #################################################################################
