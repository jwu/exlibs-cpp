// ======================================================================================
// File         : math_op.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:14:33 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATH_OP_H_1281863675
#define MATH_OP_H_1281863675
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "meta/Mathop.h"
#include "intrinsics/intrinsics.h"

///////////////////////////////////////////////////////////////////////////////
// mathops
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex {
// #########################

// ######################### 
namespace mathop { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// float op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: floor 
//  round up
//  23.67 => 24, 23.35 => 24, -23.35 => -23, -23.67 => -23 
// ------------------------------------------------------------------ 

// float 
INLINE float floor ( float _value ) { return ::floorf(_value); }

// double 
INLINE double floor ( double _value ) { return ::floor(_value); }

// ------------------------------------------------------------------ 
// Desc: ceil 
//  round down
//  23.67 => 23, 23.35 => 23, -23.35 => -24, -23.67 => -24 
// ------------------------------------------------------------------ 

// float 
INLINE float ceil ( float _value ) { return ::ceilf(_value); }

// double 
INLINE double ceil ( double _value ) { return ::ceil(_value); }

// ------------------------------------------------------------------ 
// Desc: round 
//  round to nearest
//  23.67 => 24, 23.35 => 23, -23.35 => -23, -23.67 => -24 
// ------------------------------------------------------------------ 

// float 
INLINE float round ( float _value ) { return _value > 0.0f ? (_value + 0.5f) : (_value - 0.5f); }

// double 
INLINE double round ( double _value ) { return _value > 0.0 ? (_value + 0.5) : (_value - 0.5); }

// ------------------------------------------------------------------ 
// Desc: trunc 
//  round towards zero
//  23.67 => 23, 23.35 => 23, -23.35 => -23, -23.67 => -23 
// ------------------------------------------------------------------ 

// float 
INLINE float trunc ( float _value ) { return _value > 0.0f ? mathop::floor(_value) : mathop::ceil(_value); }

// double 
INLINE double trunc ( double _value ) { return _value > 0.0 ? mathop::floor(_value) : mathop::ceil(_value); }

// ------------------------------------------------------------------ 
// Desc: round_away 
//  round away zero
//  23.67 => 24, 23.35 => 24, -23.35 => -24, -23.67 => -24 
// ------------------------------------------------------------------ 

// float 
INLINE float round_away ( float _value ) { return _value > 0.0f ? mathop::ceil(_value) : mathop::floor(_value); }

// double 
INLINE double round_away ( double _value ) { return _value > 0.0 ? mathop::ceil(_value) : mathop::floor(_value); }

// ------------------------------------------------------------------ 
// Desc: log 
// ------------------------------------------------------------------ 

// float
INLINE float log( float _value ) { return ::logf( _value ); }

// double
INLINE double log( double _value ) { return ::log(_value); }

// ------------------------------------------------------------------ 
// Desc: log2
// ------------------------------------------------------------------ 

// float 
INLINE float log2 ( float _value ) { return mathop::log(_value)/mathop::log(2.0f); }

// double 
INLINE double log2 ( double _value ) { return mathop::log(_value)/mathop::log(2.0); }

// ------------------------------------------------------------------ 
// Desc: sin 
// ------------------------------------------------------------------ 

// float
INLINE float sin( float _radian ) { return ::sinf( _radian ); }

// double
INLINE double sin( double _radian ) { return ::sin( _radian ); }

// ------------------------------------------------------------------
// Desc: asin 
//  _value in range [-1,1]
//  return value in range [-PI/2,PI/2]
// ------------------------------------------------------------------

// float
INLINE float asin( float _value ) { return ::asinf( _value ); }

// double
INLINE double asin( double _value ) { return ::asin( _value ); }

// ------------------------------------------------------------------
// Desc: cos 
// ------------------------------------------------------------------

// float
INLINE float cos( float _radian ) { return ::cosf( _radian ); }

// double
INLINE double cos( double _radian ) { return ::cos( _radian ); }

// ------------------------------------------------------------------
// Desc: acos
//  _value in range [-1,1]
//  return value in range [0,PI/2]
// ------------------------------------------------------------------

// float
INLINE float acos( float _value ) { return ::acosf( _value ); }

// double
INLINE double acos( double _value ) { return ::acos( _value ); }

// ------------------------------------------------------------------
// Desc: tan 
// ------------------------------------------------------------------

// float
INLINE float tan( float _radian ) { return ::tanf( _radian ); }

// double
INLINE double tan( double _radian ) { return ::tan( _radian ); }

// ------------------------------------------------------------------
// Desc: atan 
// return value range in [-PI/2,PI/2]
// ------------------------------------------------------------------

// float
INLINE float atan( float _value ) { return ::atanf( _value ); }

// double
INLINE double atan( double _value ) { return ::atan( _value ); }

// ------------------------------------------------------------------
// Desc: atan2 
// ------------------------------------------------------------------

// float
INLINE float atan2( float _y, float _x ) { return ::atan2f( _y, _x ); }

// double
INLINE double atan2( double _y, double _x ) { return ::atan2( _y, _x ); }

// ------------------------------------------------------------------ 
// Desc: fmod 
// ------------------------------------------------------------------ 

// float
INLINE float fmod ( float _x, float _y ) { return ::fmodf(_x,_y); }

// double
INLINE double fmod ( double _x, double _y ) { return ::fmod(_x,_y); }

// ------------------------------------------------------------------ 
// Desc: ceilpow2
// ------------------------------------------------------------------ 

INLINE uint32 ceilpow2 ( uint32 _value ) {
    uint32 result = 1;
    while ( result < _value )
    {
        result <<= 1; 
    }
    return result;
}

// ------------------------------------------------------------------ 
// Desc: ceilpow2_f
// ------------------------------------------------------------------ 

// float
INLINE uint32 ceilpow2_f ( float _value ) {
    return mathop::ceilpow2 ( (uint32)mathop::ceil(_value) );
}

// double
INLINE uint32 ceilpow2_f ( double _value ) {
    return mathop::ceilpow2 ( (uint32)mathop::ceil(_value) );
}

// ------------------------------------------------------------------ 
// Desc: floorpow2 
// ------------------------------------------------------------------ 

INLINE uint32 floorpow2 ( uint32 _value ) {
    uint32 result = 1;
    while ( result < _value )
    {
        result <<= 1; 
    }
    result >>= 1;
    return result;
}

// ------------------------------------------------------------------ 
// Desc: floorpow2_f
// ------------------------------------------------------------------ 

// float
INLINE uint32 floorpow2_f ( float _value )
{
    return mathop::floorpow2 ( (uint32)mathop::floor(_value) );
}

// double
INLINE uint32 floorpow2_f ( double _value )
{
    return mathop::floorpow2 ( (uint32)mathop::floor(_value) );
}

///////////////////////////////////////////////////////////////////////////////
// int op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 2^_count
// ------------------------------------------------------------------

INLINE uint32 pow2( uint32 _count ) { return ((uint32)1<<_count); }

///////////////////////////////////////////////////////////////////////////////
// generic op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: setNaN
// ------------------------------------------------------------------ 

template < typename T > INLINE void setNaN( T& _value ) { (*(uint32*)&(_value)=EX_UINT32_MAX); } // Set value to NaN

// ------------------------------------------------------------------ 
// Desc: isNaN
// ------------------------------------------------------------------ 

template < typename T > INLINE bool isNaN( const T& _value ) { return ((_value)!=(_value)); } // Because NaN is not equal to itself

// ------------------------------------------------------------------
// Desc: min
// ------------------------------------------------------------------

// general
template < typename T > INLINE const T& min ( const T& _a, const T& _b ) { return _b < _a ? _b : _a; }

// gernal with custom compare function
template < typename T, typename COMP_FUNC_LESS_THAN >
INLINE const T& min( const T& _a, const T& _b, COMP_FUNC_LESS_THAN _comp ) { 
    return _comp(_b, _a) ? _b : _a; 
}

// meta
template < typename T, int COUNT >
INLINE void min( T (&_pResult)[COUNT], const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] ) {
    _private::Mathop<T,COUNT>::min( _pResult, _pData1, _pData2 );
}

// vec_f32_t
INLINE void min( vec_f32_t& _result, const vec_f32_t _data1, const vec_f32_t _data2 ) {
    _result = intri::min( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: max
// ------------------------------------------------------------------

// general
template < typename T > INLINE const T& max( const T& _a, const T& _b ) { return  _a < _b ? _b : _a; }

// gernal with custom compare function
template < typename T, typename COMP_FUNC_LESS_THAN >
INLINE const T& max( const T& _a, const T& _b, COMP_FUNC_LESS_THAN _comp ) { 
    return _comp(_a, _b) ? _b : _a; 
}

// meta
template < typename T, int COUNT >
INLINE void max( T (&_pResult)[COUNT], const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] ) {
    _private::Mathop<T,COUNT>::max( _pResult, _pData1, _pData2 );
}

// vec_f32_t
INLINE void max( vec_f32_t& _result, const vec_f32_t _data1, const vec_f32_t _data2 ) {
    _result = intri::max( _data1, _data2 );
}

// ------------------------------------------------------------------ 
// Desc: sign 
// ------------------------------------------------------------------ 

template <typename T> INLINE int sign ( T _x ) {
    if ( _x > T(1) ) return 1;
    if ( _x < T(0) ) return -1;
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: pow 
// ------------------------------------------------------------------ 

// general
template <typename T> INLINE T pow ( T _x, T _p ) { return T(::pow( double(_x), double(_p) )); }

// int
template <> INLINE int pow<int> ( int _x, int _p ) { 
    ex_assert_return ( _p >= 0, 0, "the int pow can't support minus power. cauuse it will generate a float value." );
    if (_p == 0) return 1;
    if (_p == 1) return _x;
    return _x * mathop::pow<int>(_x, _p-1);
}

// uint
template <> INLINE uint pow<uint> ( uint _x, uint _p ) { 
    if (_p == 0) return 1;
    if (_p == 1) return _x;
    return _x * mathop::pow<uint>(_x, _p-1);
}

// float
template <> INLINE float pow<float> ( float _x, float _p ) { return ::powf(_x,_p); }

// double
template <> INLINE double pow<double> ( double _x, double _p ) { return ::pow(_x,_p); }

// ------------------------------------------------------------------
// Desc: abs
// ------------------------------------------------------------------

// general
template <typename T> INLINE T abs( T _value ) { return _value >= 0 ? _value : -_value; }

// float 
template <> INLINE float abs<float>( float _value ) { return ::fabsf( _value ); }

// double
template <> INLINE double abs<double>( double _value ) { return ::fabs( _value ); }

// meta
template < typename T, int COUNT >
INLINE void abs( T (&_pResult)[COUNT], const T (&_pData)[COUNT] ) {
    _private::Mathop<T,COUNT>::abs( _pResult, _pData );
}

// vec_f32_t
INLINE void abs( vec_f32_t& _result, const vec_f32_t _data ) {
    _result = intri::abs( _data );
}

// ------------------------------------------------------------------
// Desc: sqrt
// ------------------------------------------------------------------

// general
template <typename T> INLINE T sqrt( T _value ) { return T(::sqrt(double(_value))); }

// float
template <> INLINE float sqrt<float>( float _value ) { return ::sqrtf(_value); }

// double
template <> INLINE double sqrt<double>( double _value ) { return ::sqrt(_value); }

// ------------------------------------------------------------------
// Desc: inv_sqrt
// ------------------------------------------------------------------

template <typename T> INLINE T inv_sqrt( T _value ) { 
    return T(1) / mathop::sqrt<T>(_value); 
}

// ------------------------------------------------------------------
// Desc: clamp
// ------------------------------------------------------------------

// general 
template <typename T>
INLINE T clamp ( T _value, T _min = 0, T _max = 1 ) {
    return _value < _min ? _min : _value < _max ? _value : _max;
}

// meta
template < typename T, int COUNT >
INLINE void clamp( T (&_pResult)[COUNT], const T (&_pData)[COUNT], const T (&_pMin)[COUNT], const T (&_pMax)[COUNT] ) {
    _private::Mathop<T,COUNT>::clamp( _pResult, _pData, _pMin, _pMax );
}

// vec_f32_t
INLINE void clamp( vec_f32_t& _result, const vec_f32_t _data, const vec_f32_t _min, const vec_f32_t _max ) {
    _result = intri::clamp( _data, _min, _max );
}

// TODO: this needs impl vector operator compare { 
// vector like type
// template < typename T, typename U >
// T clamp ( T _x, U _min, U _max );
// } TODO end 

// ------------------------------------------------------------------ 
// Desc: lerp
// ------------------------------------------------------------------ 

// general 
template < typename T >
INLINE T lerp ( T _ratio, T _src = 0, T _dest = 1 ) {
    return _src + _ratio * ( _dest - _src );
}

// meta 
template < typename T, int COUNT >
INLINE void lerp( T (&_pResult)[COUNT], T _ratio, const T (&_pSrc)[COUNT], const T (&_pDest)[COUNT] ) {
    _private::Mathop<T,COUNT>::lerp( _pResult, _ratio, _pSrc, _pDest );
}

// vector like type
template < typename T, typename U >
T lerp ( U _ratio, T _src, T _dest ) {
    return _src + _ratio * ( _dest - _src );
}

// ------------------------------------------------------------------ 
// Desc: lerps
// ------------------------------------------------------------------ 

// meta 
template < typename T, int COUNT >
INLINE void lerps ( T (&_pResult)[COUNT], const T (&_pRatio)[COUNT], const T (&_pSrc)[COUNT], const T (&_pDest)[COUNT] ) {
    _private::Mathop<T,COUNT>::lerps( _pResult, _pRatio, _pSrc, _pDest );
}

// ------------------------------------------------------------------
// Desc: saturate
// ------------------------------------------------------------------

// general 
template <typename T> 
INLINE T saturate( T _value ) {
    return _value < T(0) ? T(0) : _value < T(1) ? _value : T(1);
}

// meta 
template < typename T, int COUNT >
INLINE void saturate( T (&_pResult)[COUNT], const T (&_pData)[COUNT] ) {
    _private::Mathop<T,COUNT>::saturate( _pResult, _pData );
}

// vec_f32_t
INLINE void saturate( vec_f32_t& _result, const vec_f32_t _data ) {
    _result = intri::saturate( _data );
}

// ------------------------------------------------------------------ 
// Desc: epsilon
// ------------------------------------------------------------------ 

template < typename T > INLINE T epsilon () { return T(0); }
template <> INLINE float epsilon<float> () { return float(EX_FLOAT_EPS); }
template <> INLINE double epsilon<double> () { return double(EX_DOUBLE_EPS); }

// ------------------------------------------------------------------
// Desc: is_equal
// ------------------------------------------------------------------


// general
template< typename T >
INLINE bool is_equal ( T _value1, T _value2, T _eps = EX_FLOAT_EPS ) {
    return ( _value1 == _value2 );
}

// float
template<>
INLINE bool is_equal<float> ( float _value1, float _value2, float _eps ) {
    return ( mathop::abs<float>(_value1-_value2) < _eps );
}

// double
template<>
INLINE bool is_equal<double> ( double _value1, double _value2, double _eps ) {
    return ( mathop::abs<double>(_value1-_value2) < _eps );
}

// meta
template < typename T, int COUNT >
INLINE void is_equal ( bool* _pResult, const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] ) {
    _private::Mathop<T,COUNT>::isEqual( _pResult, _pData1, _pData2 );
}

// meta is_equal with epsilon
template < typename T, int COUNT >
INLINE bool is_equal ( const T (&_pData1)[COUNT], const T (&_pData2)[COUNT], T _epsilon ) {
    return _private::Mathop<T,COUNT>::isEqual( _pData1, _pData2, _epsilon );
}

// vec_f32_t
INLINE bool is_equal( const vec_f32_t _data1, const vec_f32_t _data2, float _epsilon ) {
    return intri::is_equal( _data1, _data2, _epsilon );
}

// ------------------------------------------------------------------
// Desc: is_zero
// ------------------------------------------------------------------

// genreal
template< typename T >
INLINE bool is_zero ( T _value, T _eps = EX_FLOAT_EPS ) {
    return ( _value == T(0) );
}

// float
template<>
INLINE bool is_zero<float>( float _value, float _eps ) {
    return ( mathop::abs<float>(_value) < _eps );
}

// double
template<>
INLINE bool is_zero<double>( double _value, double _eps ) {
    return ( mathop::abs<double>(_value) < _eps );
}

// meta
template < typename T, int COUNT >
INLINE bool is_zero( const T (&_pData)[COUNT], T _epsilon ) {
    return _private::Mathop<T,COUNT>::isZero( _pData, _epsilon );
}

// vec_f32_t
INLINE bool is_zero( const vec_f32_t _data, float _epsilon ) {
    return intri::is_zero( _data, _epsilon );
}

// ------------------------------------------------------------------
// Desc: set
// ------------------------------------------------------------------

// general
template < typename T, int COUNT >
INLINE void set( T (&_pResult)[COUNT], const T (&_pData)[COUNT] ) { _private::Mathop<T,COUNT>::set( _pResult, _pData ); }

// vec_f32_t
INLINE void set( vec_f32_t& _result, const vec_f32_t _data ) { _result = _data; }

// float[3]
INLINE void set( vec_f32_t& _result, const float (&_pData)[3] ) { _result = intri::set3(_pData); }

// float[4]
INLINE void set( vec_f32_t& _result, const float (&_pData)[4] ) { _result = intri::set4(_pData); }

// ------------------------------------------------------------------ 
// Desc: set3
// ------------------------------------------------------------------ 

// general
template < typename T, int COUNT >
INLINE void set3( T (&_pResult)[COUNT], T _x, T _y, T _z ) {
    _pResult[0] = _x;
    _pResult[1] = _y;
    _pResult[2] = _z;
}

// vec_f32_t
INLINE void set3( vec_f32_t& _result, float _x, float _y, float _z ) {
    _result = intri::set3( _x, _y, _z );
}

// ------------------------------------------------------------------ 
// Desc: set4 
// ------------------------------------------------------------------ 

// general
template < typename T, int COUNT >
INLINE void set4( T (&_pResult)[COUNT], T _x, T _y, T _z, T _w ) {
    _pResult[0] = _x;
    _pResult[1] = _y;
    _pResult[2] = _z;
    _pResult[3] = _w;
}

// vec_f32_t
INLINE void set4( vec_f32_t& _result, float _x, float _y, float _z, float _w ) {
    _result = intri::set4( _x, _y, _z, _w );
}

// ------------------------------------------------------------------
// Desc: splat
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void splat( T (&_pResult)[COUNT], T _scalar ) {
    _private::Mathop<T,COUNT>::splat( _pResult, _scalar );
}

// vec_f32_t
INLINE void splat( vec_f32_t& _result, float _scalar ) {
    _result = intri::splat( _scalar );
}

// ------------------------------------------------------------------
// Desc: zero
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void zero( T (&_pResult)[COUNT] ) {
    _private::Mathop<T,COUNT>::zero( _pResult );
}

// vec_f32_t
INLINE void zero( vec_f32_t& _result ) { _result = intri::zero(); }

// ------------------------------------------------------------------
// Desc: one
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void one( T (&_pResult)[COUNT] )
{
    _private::Mathop<T,COUNT>::one( _pResult );
}

// vec_f32_t 
INLINE void one( vec_f32_t& _result ) { _result = intri::one(); }

// ------------------------------------------------------------------
// Desc: add
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void add ( T (&_pResult)[COUNT], const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] ) {
    _private::Mathop<T,COUNT>::add( _pResult, _pData1, _pData2 );
}

// vec_f32_t
INLINE void add ( vec_f32_t& _result, const vec_f32_t _data1, const vec_f32_t _data2 )
{
    _result = intri::add( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: sub
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void sub( T (&_pResult)[COUNT], const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] ) {
    _private::Mathop<T,COUNT>::sub( _pResult, _pData1, _pData2 );
}

// vec_f32_t
INLINE void sub( vec_f32_t& _result, const vec_f32_t _data1, const vec_f32_t _data2 )
{
    _result = intri::sub( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: mul
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void mul( T (&_pResult)[COUNT], const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] ) {
    _private::Mathop<T,COUNT>::mul( _pResult, _pData1, _pData2 );
}

// vec_f32_t
INLINE void mul( vec_f32_t& _result, const vec_f32_t _data1, const vec_f32_t _data2 ) {
    _result = intri::mul( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: div
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void div( T (&_pResult)[COUNT], const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] ) {
    _private::Mathop<T,COUNT>::div( _pResult, _pData1, _pData2 );
}

// intri
INLINE void div( vec_f32_t& _result, const vec_f32_t _data1, const vec_f32_t _data2 ) {
    _result = intri::div( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: mul_scalar
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void mul_scalar( T (&_pResult)[COUNT], const T (&_pData)[COUNT], T _scalar ) {
    _private::Mathop<T,COUNT>::mulScalar( _pResult, _pData, _scalar );
}

// vec_f32_t
INLINE void mul_scalar( vec_f32_t& _result, const vec_f32_t _data, float _scalar )
{
    _result = intri::mul_scalar( _data, _scalar );
}

// ------------------------------------------------------------------
// Desc: div_scalar
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void div_scalar( T (&_pResult)[COUNT], const T (&_pData)[COUNT], T _scalar )
{
    _private::Mathop<T,COUNT>::divScalar( _pResult, _pData, _scalar );
}

// vec_f32_t
INLINE void div_scalar( vec_f32_t& _result, const vec_f32_t _data, float _scalar ) {
    _result = intri::div_scalar( _data, _scalar );
}

// ------------------------------------------------------------------
// Desc: mul_add
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void mul_add( T (&_pResult)[COUNT], const T (&_pData1)[COUNT], const T (&_pData2)[COUNT], const T (&_pData3)[COUNT] ) {
    _private::Mathop<T,COUNT>::mulAdd( _pResult, _pData1, _pData2, _pData3 );
}

// vec_f32_t
INLINE void mul_add( vec_f32_t& _result, const vec_f32_t _data1, const vec_f32_t _data2, const vec_f32_t _data3 ) {
    _result = intri::mul_add( _data1, _data2, _data3 );
}

// ------------------------------------------------------------------
// Desc: dot
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE T dot( const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] ) {
    return _private::Mathop<T,COUNT>::dot( _pData1, _pData2 );
}

// vec_f32_t
INLINE float dot( const vec_f32_t _data1, const vec_f32_t _data2 ) {
    return intri::cast<float>( intri::dot( _data1, _data2 ) );
}

// ------------------------------------------------------------------
// Desc: cross
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void cross( T (&_pResult)[COUNT], const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] )
{
    _private::Mathop<T,COUNT>::cross( _pResult, _pData1, _pData2 );
}

// vec_f32_t
INLINE void cross( vec_f32_t& _result, const vec_f32_t _data1, const vec_f32_t _data2 )
{
    _result = intri::cross( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: length_sqr 
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE T length_sqr( const T (&_pData)[COUNT] ) {
    return _private::Mathop<T,COUNT>::dot( _pData, _pData );
}

// vec_f32_t
INLINE float length_sqr( const vec_f32_t _data )
{
    return intri::cast<float>( intri::length_sqr(_data) );
}

// ------------------------------------------------------------------
// Desc: length 
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE T length( const T (&_pData)[COUNT] ) {
    return _private::Mathop<T,COUNT>::length( _pData );
}

// vec_f32_t
INLINE float length( const vec_f32_t _data ) {
    return intri::cast<float>( intri::length(_data) );
}

// ------------------------------------------------------------------
// Desc: mask_select 
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void mask_select( T (&_pResult)[COUNT], const T (&_pMask)[COUNT], const T (&_pTrueMaskData)[COUNT], const T (&_pFalseMaskData)[COUNT] )
{
    _private::Mathop<T,COUNT>::select( _pResult, _pMask, _pTrueMaskData, _pFalseMaskData );
}

// vec_f32_t
INLINE void mask_select( vec_f32_t& _result, const vec_f32_t _bit_mask, const vec_f32_t _mask_true_sel, const vec_f32_t _mask_false_sel ) {
    _result = intri::mask_select( _bit_mask, _mask_true_sel, _mask_false_sel );
}

// ------------------------------------------------------------------
// Desc: clamp_scalar
// ------------------------------------------------------------------

// meta 
template < typename T, int COUNT >
INLINE void clamp_scalar( T (&_pResult)[COUNT], const T (&_pData)[COUNT], T _MinScalar, T _MaxScalar ) {
    _private::Mathop<T,COUNT>::clampScalar( _pResult, _pData, _MinScalar, _MaxScalar );
}

// vec_f32_t
INLINE void clamp_scalar( vec_f32_t& _result, const vec_f32_t _data, float _min_scalar, float _max_scalar ) {
    _result = intri::clamp_scalar( _data, _min_scalar, _max_scalar );
}

// ------------------------------------------------------------------
// Desc: negative
// ------------------------------------------------------------------

// meta
template < typename T, int COUNT >
INLINE void negative( T (&_pResult)[COUNT], const T (&_pData)[COUNT] ) {
    _private::Mathop<T,COUNT>::negative( _pResult, _pData );
}

// vec_f32_t
INLINE void negative( vec_f32_t& _result, const vec_f32_t _data ) {
    _result = intri::negative( _data );
}

// ######################### 
} // end namespace mathop 
// ######################### 

// #########################
} // end namespace ex
// #########################

// #################################################################################
#endif // END MATH_OP_H_1281863675
// #################################################################################
