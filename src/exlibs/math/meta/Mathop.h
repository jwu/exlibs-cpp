// ======================================================================================
// File         : Mathop.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:21:09 AM | Tuesday,August
// Description  : This is meta template to do math op of one/two/three sets of data 
// ======================================================================================

// #################################################################################
#ifndef MATHOP_H_1250526077
#define MATHOP_H_1250526077
// #################################################################################

// #########################
namespace ex { 
// #########################

// ######################### 
namespace _private { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
//  Mathop declaration
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class Mathop 
// 
// Purpose: general
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, int COUNT, int NEXT_IDX = COUNT >
class Mathop
{
    enum { IDX = (NEXT_IDX-1) };
    typedef Mathop<T,COUNT,IDX> mathop_next_t;

public:
    static INLINE void  set( T* _pResult, const T* _pData );
    static INLINE void  splat( T* _pResult, T _scalar );
    static INLINE void  zero( T* _pResult );
    static INLINE void  one( T* _pResult );

    static INLINE void  add( T* _pResult, const T* _pData1, const T* _pData2 );
    static INLINE void  sub( T* _pResult, const T* _pData1, const T* _pData2 );
    static INLINE void  mul( T* _pResult, const T* _pData1, const T* _pData2 );
    static INLINE void  div( T* _pResult, const T* _pData1, const T* _pData2 );
    static INLINE void  mulScalar( T* _pResult, const T* _pData, T _scalar );
    static INLINE void  divScalar( T* _pResult, const T* _pData, T _scalar );
    static INLINE void  mulAdd( T* _pResult, const T* _pData1, const T* _pData2, const T* _pData3 );
    // static INLINE void NegMulSub( T* _pResult, const T* _pData1, const T* _pData2, const T* _pData3 );

    static INLINE void  cross( T* _pResult, const T* _pData1, const T* _pData2 );
    static INLINE T     dot( const T* _pData1, const T* _pData2 );
    static INLINE T     lengthSQR( const T* _pData );
    static INLINE T     length( const T* _pData );

    static INLINE void  isEqual( bool* _pResult, const T* _pData1, const T* _pData2 );
    static INLINE bool  isEqual( const T* _pData1, const T* _pData2, T _epsilon ); 
    static INLINE bool  isZero( const T* _pData, T _epsilon);

    static INLINE void  saturate( T* _pResult, const T* _pData );
    static INLINE void  negative( T* _pResult, const T* _pData );
    static INLINE void  abs( T* _pResult, const T* _pData );

    static INLINE void  clamp( T* _pResult, const T* _pData, const T* _pMin, const T* _pMax );
    static INLINE void  clampScalar( T* _pResult, const T* _pData, T _MinScalar, T _MaxScalar );
    static INLINE void  lerp( T* _pResult, T _ratio, const T* _pSrc, const T* _pDest );
    static INLINE void  lerps( T* _pResult, const T* _pRatio, const T* _pSrc, const T* _pDest );

    static INLINE void  min( T* _pResult, const T* _pData1, const T* _pData2 );
    static INLINE void  max( T* _pResult, const T* _pData1, const T* _pData2 );
    static INLINE void  select( T* _pResult, const T* _pMask, const T* _pData1, const T* _pData2 );

}; // end class Mathop

///////////////////////////////////////////////////////////////////////////////
// class Mathop NEXT_IDX=0
// 
// Purpose: process ending
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, int COUNT >
class Mathop<T, COUNT, 0> 
{
public:
    static INLINE void  set( T* _pResult, const T* _pData ) {}
    static INLINE void  splat( T* _pResult, T _scalar ) {}
    static INLINE void  zero( T* _pResult ) {}
    static INLINE void  one( T* _pResult ) {}

    static INLINE void  add( T* _pResult, const T* _pData1, const T* _pData2 ) {}
    static INLINE void  sub( T* _pResult, const T* _pData1, const T* _pData2 ) {}
    static INLINE void  mul( T* _pResult, const T* _pData1, const T* _pData2 ) {}
    static INLINE void  div( T* _pResult, const T* _pData1, const T* _pData2 ) {}
    static INLINE void  mulScalar( T* _pResult, const T* _pData, T _scalar ) {}
    static INLINE void  divScalar( T* _pResult, const T* _pData, T _scalar ) {}
    static INLINE void  mulAdd( T* _pResult, const T* _pData1, const T* _pData2, const T* _pData3 ) {}
    // static INLINE void NegMulSub( T* _pResult, const T* _pData1, const T* _pData2, const T* _pData3 ) {}

    static INLINE void  cross( T* _pResult, const T* _pData1, const T* _pData2 ) {}
    static INLINE T     dot( const T* _pData1, const T* _pData2 ) { return T(0); }
    static INLINE T     lengthSQR( const T* _pData ) { ex_assert( false, "This function should not be called" ); }
    static INLINE T     length( const T* _pData ) { ex_assert( false, "This function should not be called" ); }

    static INLINE void  isEqual( bool* _pResult, const T* _pData1, const T* _pData2 ) {}
    static INLINE bool  isEqual( const T* _pData1, const T* _pData2, T _epsilon ) { return true; }
    static INLINE bool  isZero( const T* _pData, T _epsilon) { return true; }

    static INLINE void  saturate( T* _pResult, const T* _pData ) {}
    static INLINE void  negative( T* _pResult, const T* _pData ) {}
    static INLINE void  abs( T* _pResult, const T* _pData ) {}

    static INLINE void  clamp( T* _pResult, const T* _pData, const T* _pMin, const T* _pMax ) {}
	static INLINE void  clampScalar( T* _pResult, const T* _pData, T _MinScalar, T _MaxScalar ) {}
    static INLINE void  lerp( T* _pResult, T _ratio, const T* _pSrc, const T* _pDest ) {}
    static INLINE void  lerps( T* _pResult, const T* _pRatio, const T* _pSrc, const T* _pDest ) {}

    static INLINE void  min( T* _pResult, const T* _pData1, const T* _pData2 ) {}
    static INLINE void  max( T* _pResult, const T* _pData1, const T* _pData2 ) {}
    static INLINE void  select( T* _pResult, const T* _pMask, const T* _pData1, const T* _pData2 ) {}

}; // end class Mathop<T, N, 0>

///////////////////////////////////////////////////////////////////////////////
//  TMath specilize declaration
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class Mathsp 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, int COUNT >
class Mathsp
{
public:
    static INLINE void  cross( T* _pResult, const T* _pData1, const T* _pData2 );
}; // end class Mathsp

///////////////////////////////////////////////////////////////////////////////
// class Mathsp COUNT=4
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Mathsp<T,4>
{
public:
    static INLINE void  cross( T* _pResult, const T* _pData1, const T* _pData2 );
}; // end class Mathsp<T, 4, 4>

///////////////////////////////////////////////////////////////////////////////
// class Mathsp COUNT=3
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Mathsp<T,3>
{
public:
    static INLINE void  cross( T* _pResult, const T* _pData1, const T* _pData2 );
}; // end class Mathsp<T, 3, 3>

///////////////////////////////////////////////////////////////////////////////
// class Mathsp COUNT=2
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Mathsp<T,2>
{
public:
    static INLINE void  cross( T* _pResult, const T* _pData1, const T* _pData2 );
}; // end class Mathsp<T, 2, 2>

// ######################### 
} // end namespace _private 
// ######################### 


// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END MATHOP_H_1250526077
// #################################################################################
