// ======================================================================================
// File         : Intrinsics.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:51:08 PM | Monday,August
// Description  : SSE optimization
//                  vec_float4 :  |127| w,z,y,x |0| ==> 0X|w|z|y|x|
//                  _MM_SHUFFLE(w, z, y, x) ==> (w<<6) | (z<<4) | (y<<2) | x
// ======================================================================================

// #################################################################################
#ifndef INTRINSICS_H_1250524276
#define INTRINSICS_H_1250524276
// #################################################################################

// ############################################################################
// Note: don't use namespace here, this header already been in namespace ex 
// ############################################################################

///////////////////////////////////////////////////////////////////////////////
// macros 
///////////////////////////////////////////////////////////////////////////////

// TODO: if no use
#if 0
/**
 * =======================================
 * EX_MAKE_MASK_M128
 * =======================================
 */
#define EX_MAKE_MASK_M128( MASK_NAME, _w, _z, _y, _x )                  \
    static const EX_ALIGN(16) int32 _##MASK_NAME[] = { _x, _y, _z, _w }; \
    const vec_float4 MASK_NAME = _mm_load_ps((float*)_##MASK_NAME);
#endif

///////////////////////////////////////////////////////////////////////////////
// template specilize
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: cast
//          vec_float4 to float
// ------------------------------------------------------------------

template <>
INLINE float cast( const vec_float4& _data ) {
    return *((float*)(&_data));
}

// ------------------------------------------------------------------
// Desc: get
// ------------------------------------------------------------------

INLINE float get( const vec_float4 _data, int _idx ) {
    const int max_count = 4;
    ex_assert( _idx >= 0 && _idx < max_count, " vec_float4 support %d components of float to get", max_count );
    return ((float*)(&_data))[_idx];
}

// ------------------------------------------------------------------
// Desc: getref
// ------------------------------------------------------------------

INLINE float& getref( vec_float4& _data, int _idx ) {
    const int max_count = 4;
    ex_assert( _idx >= 0 && _idx < max_count, " vec_float4 support %d components of float to get", max_count );
    return ((float*)(&_data))[_idx];
}

///////////////////////////////////////////////////////////////////////////////
// intrinsics
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: set3
// ------------------------------------------------------------------

// float[3]
INLINE vec_float4 set3( const float (&_pData)[3] ) {
    return (vec_float4){ _pData[0], _pData[1], _pData[2], 1.0f };
}

// 3 x float
INLINE vec_float4 set3( float _x, float _y, float _z ) {
    return (vec_float4){ _x, _y, _z, 1.0f };
}

// ------------------------------------------------------------------
// Desc: set4
// ------------------------------------------------------------------

// float[4]
INLINE vec_float4 set4( const float (&_pData)[4] ) {
    return (vec_float4){ _pData[0], _pData[1], _pData[2], _pData[3] };
}

// 4 x float
INLINE vec_float4 set4( float _x, float _y, float _z, float _w ) {
    return (vec_float4){ _x, _y, _z, _w };
}

// ------------------------------------------------------------------
// Desc: splat
// ------------------------------------------------------------------

INLINE vec_float4 splat( float _scalar ) {
    // TODO: confirm the assamble compiled by this
    // return vec_splat_s32( _scalar );
	// return vec_splat( (vec_float4)vec_lvlx(0, &_scalar), 0 );
    return (vec_float4){ _scalar, _scalar, _scalar, _scalar };
}

// ------------------------------------------------------------------
// Desc: zero
// ------------------------------------------------------------------

INLINE vec_float4 zero() { 
    return ex::splat( 0.0f ); 
}

// ------------------------------------------------------------------
// Desc: one
// ------------------------------------------------------------------

INLINE vec_float4 one() {
    return ex::splat( 1.0f );
}

// ------------------------------------------------------------------
// Desc: add
// ------------------------------------------------------------------

INLINE vec_float4 add( const vec_float4 _data1, const vec_float4 _data2 ) {
    return vec_add( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: sub
// ------------------------------------------------------------------

INLINE vec_float4 sub( const vec_float4 _data1, const vec_float4 _data2 ) {
    return vec_sub( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: mul
// ------------------------------------------------------------------

INLINE vec_float4 mul( const vec_float4 _data1, const vec_float4 _data2 ) {
    return vec_madd( _data1, _data2, ex::zero() );
}

// ------------------------------------------------------------------
// Desc: div
// ------------------------------------------------------------------

INLINE vec_float4 div( const vec_float4 _data1, const vec_float4 _data2 ) {
    float* pInv = (float*)(&_data2);
    return vec_madd( _data1, (vec_float4){ 1.0f/pInv[0], 1.0f/pInv[1], 1.0f/pInv[2], 1.0f/pInv[3] }, ex::zero() );
}

// ------------------------------------------------------------------
// Desc: mul_scalar
// ------------------------------------------------------------------

INLINE vec_float4 mul_scalar( const vec_float4 _data, float _scalar ) {
    return vec_madd( _data, ex::splat(_scalar), ex::zero() );
}

// ------------------------------------------------------------------
// Desc: div_scalar
// ------------------------------------------------------------------

INLINE vec_float4 div_scalar( const vec_float4 _data, float _scalar ) {
    return vec_madd( _data, ex::splat(1.0f/_scalar), ex::zero() );
}

// ------------------------------------------------------------------
// Desc: mul_add
// ------------------------------------------------------------------

INLINE vec_float4 mul_add( const vec_float4 _data1, const vec_float4 _data2, const vec_float4 _data3 ) {
    return vec_madd( _data1, _data2, _data3 );
}

// ------------------------------------------------------------------
// Desc: dot3
// ------------------------------------------------------------------

INLINE vec_float4 dot3( const vec_float4 _data1, const vec_float4 _data2 ) {
    vec_float4 result;
    result = vec_madd( _data1, _data2, (vec_float4)(0.0f) );
    result = vec_madd( vec_sld( _data1, _data1, 4 ), vec_sld( _data2, _data2, 4 ), result );
    return vec_madd( vec_sld( _data1, _data1, 8 ), vec_sld( _data2, _data2, 8 ), result );
}

// ------------------------------------------------------------------
// Desc: dot
// ------------------------------------------------------------------

INLINE vec_float4 dot( const vec_float4 _data1, const vec_float4 _data2 ) {
    vec_float4 result;
    result = vec_madd( _data1, _data2, (vec_float4)(0.0f) );
    result = vec_madd( vec_sld( _data1, _data1, 4 ), vec_sld( _data2, _data2, 4 ), result );
    return vec_add( vec_sld( result, result, 8 ), result );
}

// ------------------------------------------------------------------
// Desc: cross 
// ------------------------------------------------------------------

INLINE vec_float4 cross( const vec_float4 _data1, const vec_float4 _data2 ) {
    vec_float4 tmp0, tmp1, tmp2, tmp3;
    tmp0 = vec_perm( _data1, _data1, _VECTORMATH_PERM_YZXW );
    tmp1 = vec_perm( _data2, _data2, _VECTORMATH_PERM_ZXYW );
    tmp2 = vec_perm( _data1, _data1, _VECTORMATH_PERM_ZXYW );
    tmp3 = vec_perm( _data2, _data2, _VECTORMATH_PERM_YZXW );
    return vec_nmsub( tmp2, tmp3, vec_madd( tmp0, tmp1, (vec_float4)(0.0f) ) );
}

// ------------------------------------------------------------------
// Desc: length_sqr 
// ------------------------------------------------------------------

INLINE vec_float4 length_sqr( const vec_float4 _data ) {
    return intri::dot( _data, _data );
}

// ------------------------------------------------------------------
// Desc: length 
// ------------------------------------------------------------------

INLINE vec_float4 length( const vec_float4 _data ) {
    return sqrtf4( intri::length_sqr(_data) );
}

// ------------------------------------------------------------------
// Desc: is_equal
// ------------------------------------------------------------------

INLINE bool is_equal( const vec_float4 _data1, const vec_float4 _data2, float _epsilon = EX_FLOAT_EPS ) {
    return vec_all_in( vec_sub(_data1, _data2), intri::splat(_epsilon) );
}

// ------------------------------------------------------------------
// Desc: is_zero
// ------------------------------------------------------------------

INLINE bool is_zero( const vec_float4 _data, float _epsilon = EX_FLOAT_EPS ) {
    return ex::is_equal( _data, intri::zero(), _epsilon );
}

// ------------------------------------------------------------------
// Desc: mask_select 
// ------------------------------------------------------------------

INLINE vec_float4 mask_select( const vec_float4 _bit_mask, const vec_float4 _mask_true_sel, const vec_float4 _mask_false_sel )
{
    return vec_sel( _mask_true_sel, _mask_false_sel, (vec_uint4)_bit_mask );
}

// ------------------------------------------------------------------
// Desc: clamp 
// ------------------------------------------------------------------

INLINE vec_float4 clamp( const vec_float4 _data, const vec_float4 _min, const vec_float4 _max ) {
    return vec_min( _max, vec_max( _min, _data ) );
}

// ------------------------------------------------------------------
// Desc: clamp_scalar
// ------------------------------------------------------------------

INLINE vec_float4 clamp_scalar( const vec_float4 _data, float _min_scalar, float _max_scalar ) {
    return intri::clamp( _data, intri::splat(_min_scalar), intri::splat(_max_scalar) );
}

// ------------------------------------------------------------------
// Desc: saturate
// ------------------------------------------------------------------

INLINE vec_float4 saturate( const vec_float4 _data ) {
    return intri::clamp_scalar( _data, 0.0f, 1.0f );
}

// ------------------------------------------------------------------
// Desc: negative
// ------------------------------------------------------------------

INLINE vec_float4 negative( const vec_float4 _data ) {
    return (vec_float4)vec_xor( (vec_uint4)_data, (vec_uint4)(0x80000000) );
}

// ------------------------------------------------------------------
// Desc: abs
// ------------------------------------------------------------------

INLINE vec_float4 abs( const vec_float4 _data ) {
    return vec_abs( _data );
}

// ------------------------------------------------------------------
// Desc: min
// ------------------------------------------------------------------

INLINE vec_float4 min( const vec_float4 _data1, const vec_float4 _data2 ) {
    return vec_min( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: max
// ------------------------------------------------------------------

INLINE vec_float4 max( const vec_float4 _data1, const vec_float4 _data2 ) {
    return vec_max( _data1, _data2 );
}

// #################################################################################
#endif // END INTRINSICS_H_1250524276
// #################################################################################
