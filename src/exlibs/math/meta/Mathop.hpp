// ======================================================================================
// File         : Mathop.hpp
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:21:25 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATHOP_HPP_1250525322
#define MATHOP_HPP_1250525322
// #################################################################################

// #########################
namespace ex { 
// #########################

// ######################### 
namespace _private { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
//  Mathop static function defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Mathop::Set
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::set( T* _pResult, const T* _pData )
{
    _pResult[IDX] = _pData[IDX];
    mathop_next_t::set( _pResult, _pData );
}

// ------------------------------------------------------------------
// Desc: Mathop::splat
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::splat( T* _pResult, T _scalar )
{
    _pResult[IDX] = _scalar;
    mathop_next_t::splat( _pResult, _scalar );
}

// ------------------------------------------------------------------
// Desc: Mathop::zero
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::zero( T* _pResult )
{
    _pResult[IDX] = T(0);
    mathop_next_t::zero( _pResult );
}

// ------------------------------------------------------------------
// Desc: Mathop::one
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::one( T* _pResult )
{
    _pResult[IDX] = T(1);
    mathop_next_t::one( _pResult );
}

// ------------------------------------------------------------------
// Desc: Mathop::add
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::add( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[IDX] = _pData1[IDX] + _pData2[IDX];
    mathop_next_t::add( _pResult, _pData1, _pData2 );
}

// ------------------------------------------------------------------
// Desc: Mathop::sub
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::sub( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[IDX] = _pData1[IDX] - _pData2[IDX];
    mathop_next_t::sub( _pResult, _pData1, _pData2 );
}

// ------------------------------------------------------------------
// Desc: Mathop::mul
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::mul( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[IDX] = _pData1[IDX] * _pData2[IDX];
    mathop_next_t::mul( _pResult, _pData1, _pData2 );
}

// ------------------------------------------------------------------
// Desc: Mathop::div
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::div( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[IDX] = _pData1[IDX] / _pData2[IDX];
    mathop_next_t::div( _pResult, _pData1, _pData2 );
}

// ------------------------------------------------------------------
// Desc: Mathop::mulScalar
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::mulScalar( T* _pResult, const T* _pData, T _scalar )
{
    _pResult[IDX] = _pData[IDX] * _scalar;
    mathop_next_t::mulScalar( _pResult, _pData, _scalar );
}

// ------------------------------------------------------------------
// Desc: Mathop::divScalar
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::divScalar( T* _pResult, const T* _pData, T _scalar )
{
    T inv_scalar = T(1)/_scalar;
    _pResult[IDX] = _pData[IDX] * inv_scalar;
    mathop_next_t::mulScalar( _pResult, _pData, inv_scalar );
}

// ------------------------------------------------------------------
// Desc: Mathop::mulAdd
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::mulAdd( T* _pResult, const T* _pData1, const T* _pData2, const T* _pData3 )
{
    _pResult[IDX] = _pData1[IDX] * _pData2[IDX] + _pData3[IDX];
    mathop_next_t::mulAdd( _pResult, _pData1, _pData2, _pData3 );
}

// ------------------------------------------------------------------
// Desc: Mathop::cross
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::cross( T* _pResult, const T* _pData1, const T* _pData2 )
{
    Mathsp<T,COUNT>::cross( _pResult, _pData1, _pData2 ); 
}

// ------------------------------------------------------------------
// Desc: Mathop::dot
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE T Mathop<T, COUNT, NEXT_IDX>::dot( const T* _pData1, const T* _pData2 )
{
    return _pData1[IDX]*_pData2[IDX] + mathop_next_t::dot( _pData1, _pData2 );
}

// ------------------------------------------------------------------
// Desc: Mathop::lengthSQR 
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE T Mathop<T, COUNT, NEXT_IDX>::lengthSQR( const T* _pData )
{
    return dot( _pData, _pData );
}

// ------------------------------------------------------------------
// Desc: Mathop::length 
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE T Mathop<T, COUNT, NEXT_IDX>::length( const T* _pData )
{
    return mathop::sqrt<T>( dot( _pData, _pData ) );
}

// ------------------------------------------------------------------
// Desc: Mathop::isEqual
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::isEqual( bool* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[IDX] = (_pData1[IDX] == _pData2[IDX]);
    mathop_next_t::isEqual( _pResult, _pData1, _pData2 );
}

// ------------------------------------------------------------------
// Desc: Mathop::isEqual with epsilon
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE bool Mathop<T, COUNT, NEXT_IDX>::isEqual( const T* _pData1, const T* _pData2, T _epsilon )
{
    return mathop::is_equal<T>( _pData1[IDX], _pData2[IDX], _epsilon ) && mathop_next_t::isEqual( _pData1, _pData2, _epsilon );
}

// ------------------------------------------------------------------
// Desc: Mathop::isZero 
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE bool Mathop<T, COUNT, NEXT_IDX>::isZero( const T* _pData, T _epsilon)
{
    return mathop::is_zero<T>( _pData[IDX], _epsilon ) && mathop_next_t::isZero( _pData, _epsilon );
}

// ------------------------------------------------------------------
// Desc: Mathop::saturate
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::saturate( T* _pResult, const T* _pData )
{
    clampScalar( _pResult, _pData, T(0), T(1) );
}

// ------------------------------------------------------------------
// Desc: Mathop::negative
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::negative( T* _pResult, const T* _pData )
{
    _pResult[IDX] = -_pData[IDX];
    mathop_next_t::negative( _pResult, _pData );
}

// ------------------------------------------------------------------
// Desc: Mathop::abs
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::abs( T* _pResult, const T* _pData )
{
    _pResult[IDX] = mathop::abs<T>(_pData[IDX]);
    mathop_next_t::abs( _pResult, _pData );
}

// ------------------------------------------------------------------
// Desc: Mathop::clamp 
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::clamp( T* _pResult, const T* _pData, const T* _pMin, const T* _pMax )
{
    _pResult[IDX] = mathop::clamp<T>( _pData[IDX], _pMin[IDX], _pMax[IDX] );
    mathop_next_t::clamp( _pResult, _pData, _pMin, _pMax );
}

// ------------------------------------------------------------------
// Desc: Mathop::clampScalar
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::clampScalar( T* _pResult, const T* _pData, T _MinScalar, T _MaxScalar )
{
    _pResult[IDX] = mathop::clamp<T>( _pData[IDX], _MinScalar, _MaxScalar );
    mathop_next_t::clampScalar( _pResult, _pData, _MinScalar, _MaxScalar );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::lerp( T* _pResult, T _ratio, const T* _pSrc, const T* _pDest )
{
    _pResult[IDX] = mathop::lerp<T>( _ratio, _pSrc[IDX], _pDest[IDX] );
    mathop_next_t::lerp( _pResult, _ratio, _pSrc, _pDest );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, int COUNT, int NEXT_IDX >
INLINE void  Mathop<T, COUNT, NEXT_IDX>::lerps( T* _pResult, const T* _pRatio, const T* _pSrc, const T* _pDest )
{
    _pResult[IDX] = mathop::lerp<T>( _pRatio[IDX], _pSrc[IDX], _pDest[IDX] );
    mathop_next_t::lerps( _pResult, _pRatio, _pSrc, _pDest );
}

// ------------------------------------------------------------------
// Desc: Mathop::min
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::min( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[IDX] = _pData1[IDX] < _pData2[IDX] ? _pData1[IDX] : _pData2[IDX];
    mathop_next_t::min( _pResult, _pData1, _pData2 );
}

// ------------------------------------------------------------------
// Desc: Mathop::max
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::max( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[IDX] = _pData1[IDX] > _pData2[IDX] ? _pData1[IDX] : _pData2[IDX];
    mathop_next_t::max( _pResult, _pData1, _pData2 );
}

// ------------------------------------------------------------------
// Desc: Mathop::select
// ------------------------------------------------------------------

template < typename T, int COUNT, int NEXT_IDX >
INLINE void Mathop<T, COUNT, NEXT_IDX>::select( T* _pResult, const T* _pMask, const T* _pData1, const T* _pData2 )
{
    _pResult[IDX] = _pMask[IDX] ? _pData1[IDX] : _pData2[IDX];
    mathop_next_t::select( _pResult, _pMask, _pData1, _pData2 );
}

///////////////////////////////////////////////////////////////////////////////
//  TMath specilize defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Mathsp::cross
// ------------------------------------------------------------------

// ========================================================
// general
// ========================================================

template < typename T, int COUNT >
INLINE void Mathsp<T, COUNT>::cross( T* _pResult, const T* _pData1, const T* _pData2 )
{
    ex_static_assert( false, "count must <= 4" );
}

// ========================================================
// Mathsp::cross 4
// ========================================================

template < typename T >
INLINE void Mathsp<T, 4>::cross( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[0] = _pData1[1] * _pData2[2] - _pData1[2] * _pData2[1];
    _pResult[1] = _pData1[2] * _pData2[0] - _pData1[0] * _pData2[2];
    _pResult[2] = _pData1[0] * _pData2[1] - _pData1[1] * _pData2[0];
    _pResult[3] = T(0);
}

// ========================================================
// Mathsp::cross 3
// ========================================================

template < typename T >
INLINE void Mathsp<T, 3>::cross( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[0] = _pData1[1] * _pData2[2] - _pData1[2] * _pData2[1];
    _pResult[1] = _pData1[2] * _pData2[0] - _pData1[0] * _pData2[2];
    _pResult[2] = _pData1[0] * _pData2[1] - _pData1[1] * _pData2[0];
}

// ========================================================
// Mathsp::cross 2
// NOTE: remember, in 2d, the cross product is a scalar, in 3d is a vector.
// ========================================================

template < typename T >
INLINE void Mathsp<T, 2>::cross( T* _pResult, const T* _pData1, const T* _pData2 )
{
    _pResult[0] = _pData1[0] * _pData2[1] - _pData1[1] * _pData2[0];
}

// ######################### 
} // end namespace _private 
// ######################### 


// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END MATHOP_HPP_1250525322
// #################################################################################
