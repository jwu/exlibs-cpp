// ======================================================================================
// File         : Intrinsics.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:51:25 PM | Monday,August
// Description  : SSE optimization
//                  __m128 :  |127| w,z,y,x |0| ==> 0X|w|z|y|x|
//                  _MM_SHUFFLE(w, z, y, x) ==> (w<<6) | (z<<4) | (y<<2) | x
// ======================================================================================

// #################################################################################
#ifndef INTRINSICS_H_1250524294
#define INTRINSICS_H_1250524294
// #################################################################################

// ############################################################################
// Note: don't use namespace here, this header already been in namespace ex 
// ############################################################################

///////////////////////////////////////////////////////////////////////////////
// macros 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

#define EX_MAKE_MASK_M128( MASK_NAME, _w, _z, _y, _x )                  \
    static const EX_ALIGN(16) int32 _##MASK_NAME[] = { _x, _y, _z, _w }; \
    const __m128 MASK_NAME = _mm_load_ps((float*)_##MASK_NAME);

///////////////////////////////////////////////////////////////////////////////
// template specilize
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc:  __m128 to float
// ------------------------------------------------------------------

template <>
INLINE float cast( const __m128& _data )
{
#if (EX_COMPILER == EX_MSVC)
    return _data.m128_f32[0];
#else
    return _mm_cvtss_f32(_data);
#endif
}

// ------------------------------------------------------------------
// Desc: get 
// ------------------------------------------------------------------

INLINE float get( const __m128 _data, int _idx )
{
    ex_assert( _idx >= 0 && _idx < 4, " __m128 support 4 components of float to get" );
#if ( EX_COMPILER == EX_MSVC )
    return _data.m128_f32[_idx];
#else 
    return ((float*)&_data)[_idx];
#endif
}

// ------------------------------------------------------------------
// Desc: getref 
// ------------------------------------------------------------------

// TODO: find way to fix the bug
INLINE float& getref( __m128& _data, int _idx )
{
    ex_assert( _idx >= 0 && _idx < 4, " __m128 support 4 components of float to get" );
#if ( EX_COMPILER == EX_MSVC )
    return _data.m128_f32[_idx];
#else 
    return ((float*)&_data)[_idx];
#endif
}

///////////////////////////////////////////////////////////////////////////////
// intrinsics
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: set3
// ------------------------------------------------------------------

// float[3]
INLINE __m128 set3( const float (&_pData)[3] ) {
    return _mm_set_ps( 1.0f, _pData[2], _pData[1], _pData[0] );
}

// 3 x float
INLINE __m128 set3( float _x, float _y, float _z ) {
    return _mm_set_ps( 1.0f, _z, _y, _x );
}

// ------------------------------------------------------------------
// Desc: set4
// ------------------------------------------------------------------

// float[4]
INLINE __m128 set4( const float (&_pData)[4] ) {
    return _mm_set_ps( _pData[3], _pData[2], _pData[1], _pData[0] );
}

// 4 x float
INLINE __m128 set4( float _x, float _y, float _z, float _w ) {
    return _mm_set_ps( _w, _z, _y, _x );
}

// ------------------------------------------------------------------
// Desc: splat
// ------------------------------------------------------------------

INLINE __m128 splat( float _scalar ) {
    return _mm_set_ps1(_scalar);
}

// ------------------------------------------------------------------
// Desc: zero
// ------------------------------------------------------------------

INLINE __m128 zero() {
    return _mm_setzero_ps();
}

// ------------------------------------------------------------------
// Desc: one
// ------------------------------------------------------------------

INLINE __m128 one() {
    return _mm_set_ps1(1.0f);
}

// ------------------------------------------------------------------
// Desc: add
// ------------------------------------------------------------------

INLINE __m128 add( const __m128 _data1, const __m128 _data2 ) {
    return _mm_add_ps( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: sub
// ------------------------------------------------------------------

INLINE __m128 sub( const __m128 _data1, const __m128 _data2 ) {
    return _mm_sub_ps( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: mul
// ------------------------------------------------------------------

INLINE __m128 mul( const __m128 _data1, const __m128 _data2 ) {
    return _mm_mul_ps( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: div
// ------------------------------------------------------------------

INLINE __m128 div( const __m128 _data1, const __m128 _data2 ) {
    return _mm_div_ps( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: mul_scalar
// ------------------------------------------------------------------

INLINE __m128 mul_scalar( const __m128 _data, float _scalar ) {
    return _mm_mul_ps( _data, _mm_set_ps1(_scalar) );
}

// ------------------------------------------------------------------
// Desc: div_scalar
// ------------------------------------------------------------------

INLINE __m128 div_scalar( const __m128 _data, float _scalar ) {
    return _mm_div_ps( _data, _mm_set_ps1(_scalar) );
}

// ------------------------------------------------------------------
// Desc: mul_add
// ------------------------------------------------------------------

INLINE __m128 mul_add( const __m128 _data1, const __m128 _data2, const __m128 _data3 ) {
    return _mm_add_ps( _mm_mul_ps( _data1, _data2 ), _data3 );
}

// ------------------------------------------------------------------
// Desc: dot3
// ------------------------------------------------------------------

INLINE __m128 dot3( const __m128 _data1, const __m128 _data2 ) {
    __m128 mul = _mm_mul_ps(_data1, _data2); 
    __m128 y   = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 1, 1, 1));
    __m128 z   = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 2, 2, 2));
    __m128 yz  = _mm_add_ss(y,z); 
    __m128 xyz = _mm_add_ss(mul, yz);
    return _mm_shuffle_ps(xyz, xyz, _MM_SHUFFLE(0, 0, 0, 0));
}

// ------------------------------------------------------------------
// Desc: dot
// ------------------------------------------------------------------

INLINE __m128 dot( const __m128 _data1, const __m128 _data2 ) {
    /*
     * v = 0X|w|z|y|x| 
     * v = 0X|3|2|1|0| 
     * _MM_SHUFFLE(w,z,y,x)
     */
    __m128 v0, v1;

    v0 = _mm_mul_ps( _data1, _data2 ); /* v0 = ( w1*w2, z1*z2, y1*y2, x1*x2 ) */
	
    v1 = _mm_shuffle_ps( v0, v0, _MM_SHUFFLE(1, 0, 3, 2) ); /* v1 = ( y1*y2, x1*x2, w1*w2, z1*z2 ) */
    v0 = _mm_add_ps( v0, v1 );                              /* v0 = ( w1*w2+y1*y2, z1*z2+x1*x2, y1*y2+w1*w2, x1*x2+z1*z2 )*/
    v1 = _mm_shuffle_ps( v0, v0, _MM_SHUFFLE(0, 1, 0, 1) ); /* v1 = ( x1*x2+z1*z2, y1*y2+w1*w2, ... )*/
    return _mm_add_ps( v0, v1 );                              /* v0 = ( x1*x2+y1*y2+z1*z2+w1*w2, ... )*/
}

// ------------------------------------------------------------------
// Desc: cross 
// ------------------------------------------------------------------

INLINE __m128 cross( const __m128 _data1, const __m128 _data2 ) {
    __m128 v0;
    __m128 v1;
    __m128 v2;

    v0 = _mm_shuffle_ps(_data1, _data1, _MM_SHUFFLE(3, 0, 2, 1));	// v0 = (y, z, x, w)
    v1 = _mm_shuffle_ps(_data2, _data2, _MM_SHUFFLE(3, 1, 0, 2));	// v1 = (z, x, y, w)
    v2 = _mm_mul_ps(v0, v1);										// v2 = v0 * v1;

    v0 = _mm_shuffle_ps(_data1, _data1, _MM_SHUFFLE(3, 1, 0, 2));	// v0 = (z, x, y, w)
    v1 = _mm_shuffle_ps(_data2, _data2, _MM_SHUFFLE(3, 0, 2, 1));	// v1 = (y, z, x, w)
    v1 = _mm_mul_ps(v0, v1);										// v2 = v0 * v1;

    return _mm_sub_ps(v2, v1);
}

// ------------------------------------------------------------------
// Desc: length_sqr 
// ------------------------------------------------------------------

INLINE __m128 length_sqr( const __m128 _data ) {
    return intri::dot( _data, _data );
}

// ------------------------------------------------------------------
// Desc: length 
// ------------------------------------------------------------------

INLINE __m128 length( const __m128 _data ) {
    /*
     * v = 0X|w|z|y|x| 
     * v = 0X|3|2|1|0| 
     * _MM_SHUFFLE(w,z,y,x)
     */
    __m128 v0, v1;

    v0 = _mm_mul_ps( _data, _data ); /* v0 = ( w1*w2, z1*z2, y1*y2, x1*x2 ) */
	
    v1 = _mm_shuffle_ps( v0, v0, _MM_SHUFFLE(1, 0, 3, 2) ); /* v1 = ( y1*y2, x1*x2, w1*w2, z1*z2 ) */
    v0 = _mm_add_ps( v0, v1 );                              /* v0 = ( w1*w2+y1*y2, z1*z2+x1*x2, y1*y2+w1*w2, x1*x2+z1*z2 )*/
    v1 = _mm_shuffle_ps( v0, v0, _MM_SHUFFLE(0, 1, 0, 1) ); /* v1 = ( x1*x2+z1*z2, y1*y2+w1*w2, ... )*/
    v0 = _mm_add_ps( v0, v1 );                              /* v0 = ( x1*x2+y1*y2+z1*z2+w1*w2, ... )*/
    return _mm_sqrt_ps(v0);
}

// ------------------------------------------------------------------
// Desc: is_equal
// ------------------------------------------------------------------

INLINE bool is_equal( const __m128 _data1, const __m128 _data2, float _epsilon = EX_FLOAT_EPS ) {
    __m128 abs = _mm_max_ps(_mm_sub_ps(_data1,_data2), _mm_sub_ps(_data2,_data1));
    __m128 cmp = _mm_cmpgt_ps(abs, _mm_set_ps1(_epsilon));
    return !_mm_movemask_ps(cmp);
}

// ------------------------------------------------------------------
// Desc: is_zero 
// ------------------------------------------------------------------

INLINE bool is_zero( const __m128 _data, float _epsilon = EX_FLOAT_EPS ) {
    __m128 abs = _mm_max_ps(_data, _mm_sub_ps(_mm_setzero_ps(),_data));
    __m128 cmp = _mm_cmpgt_ps(abs, _mm_set_ps1(_epsilon));
    return !_mm_movemask_ps(cmp);
}

// ------------------------------------------------------------------
// Desc: mask_select 
// ------------------------------------------------------------------

INLINE __m128 mask_select( const __m128 _bit_mask, const __m128 _mask_true_sel, const __m128 _mask_false_sel ) {
    __m128 v0 = _mm_andnot_ps( _bit_mask, _mask_false_sel );
    __m128 v1 = _mm_and_ps( _bit_mask, _mask_true_sel );
    return _mm_or_ps( v0, v1 );
}

// ------------------------------------------------------------------
// Desc: clamp 
// ------------------------------------------------------------------

INLINE __m128 clamp( const __m128 _data, const __m128 _min, const __m128 _max ) {
    __m128 min_mask = _mm_cmplt_ps(_data, _min);
    __m128 max_mask = _mm_cmpgt_ps(_data, _max);

    return intri::mask_select( min_mask, _min, intri::mask_select( max_mask, _max, _data ) );
}

// ------------------------------------------------------------------
// Desc: clamp_scalar
// ------------------------------------------------------------------

INLINE __m128 clamp_scalar( const __m128 _data, float _min_scalar, float _max_scalar ) {
    return intri::clamp( _data, _mm_set_ps1(_min_scalar), _mm_set_ps1(_max_scalar) );
}

// ------------------------------------------------------------------
// Desc: saturate
// ------------------------------------------------------------------

INLINE __m128 saturate( const __m128 _data ) {
    return intri::clamp_scalar( _data, 0.0f, 1.0f );
}

// ------------------------------------------------------------------
// Desc: negative
// ------------------------------------------------------------------

INLINE __m128 negative( const __m128 _data ) {
    EX_MAKE_MASK_M128( mask, 0x80000000, 0x80000000, 0x80000000, 0x80000000 );
    return _mm_xor_ps( _data, mask );
}

// ------------------------------------------------------------------
// Desc: abs
// ------------------------------------------------------------------

INLINE __m128 abs( const __m128 _data ) {
    EX_MAKE_MASK_M128( mask, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF );
    return _mm_and_ps( _data, mask );
}

// ------------------------------------------------------------------
// Desc: min
// ------------------------------------------------------------------

INLINE __m128 min ( const __m128 _data1, const __m128 _data2 ) {
    return _mm_min_ps( _data1, _data2 );
}

// ------------------------------------------------------------------
// Desc: max
// ------------------------------------------------------------------

INLINE __m128 max ( const __m128 _data1, const __m128 _data2 ) {
    return _mm_max_ps( _data1, _data2 );
}

// #################################################################################
#endif // END INTRINSICS_H_1250524294
// #################################################################################
