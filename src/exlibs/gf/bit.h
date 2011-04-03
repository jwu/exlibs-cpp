// ======================================================================================
// File         : Bit.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:39:29 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef BIT_H_1250523573
#define BIT_H_1250523573
// #################################################################################

// #########################
namespace ex { 
// #########################

// ------------------------------------------------------------------
// Desc: Detect is power of 2 or not.
//  If the _value is power of 2, then it is aligned
// ------------------------------------------------------------------

INLINE bool is_powof2( uint _value )
{
    return !((_value-1) & _value);
}

// ------------------------------------------------------------------
// Desc: Detect is aligned or not.
//  If the mod of the _value with _align is 0, then it is aligned
// ------------------------------------------------------------------

INLINE bool is_aligned( uint _value, uint _align )
{
    ex_assert( is_powof2(_align), "_align must be pow of 2" );
    return ( (_value & (_align-1)) == 0 );
}

// ------------------------------------------------------------------
// Desc: Get the minimum alignment needed by a type
// ------------------------------------------------------------------

// ========================================================
// general
// ========================================================

template < typename T >
INLINE uint32 alignof()
{
    return __alignof(T);
}

// ========================================================
// void 
// ========================================================

template <>
INLINE uint32 alignof<void>()
{
    return 1;
}

// ------------------------------------------------------------------
// Desc: bitmask
// ------------------------------------------------------------------

INLINE uint32 bitmask( uint32 _count ) 
{
    return mathop::pow2(_count)-1;
}

// ------------------------------------------------------------------
// Desc: use bits from 0 to _count.
// ------------------------------------------------------------------

INLINE uint32 usebits( uint32 _value, uint32 _count )
{
    return (_value & bitmask(_count));
}

// ------------------------------------------------------------------
// Desc: get bit at _bit_pos
// ------------------------------------------------------------------

INLINE uint32 getbit( uint32 _value, uint32 _bit_pos )
{
    return (_value & mathop::pow2(_bit_pos));
}

///////////////////////////////////////////////////////////////////////////////
// bit rotation
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, typename U >
INLINE T bit_rotl ( T _value, U _rotCount )
{
    const uint size = sizeof(T) * 4;
    _rotCount %= size;
    return (_value << _rotCount) | (_value >> (size - _rotCount));
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, typename U >
INLINE T bit_rotr ( T _value, U _rotCount )
{
    const uint size = sizeof(T) * 4;
    _rotCount %= size;
    return (_value >> _rotCount) | (_value << (size - _rotCount));
}

///////////////////////////////////////////////////////////////////////////////
// 64-bit op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE uint64 gen_uint64 ( uint32 _highVal, uint32 _lowVal ) 
{
    return ((uint64(_highVal))<<32ull) + uint64(_lowVal);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE int64 gen_int64 ( int32 _highVal, int32 _lowVal ) 
{
    return ((int64(_highVal))<<32ll) + int64(_lowVal);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE void split_uint64 ( uint64 _value, uint32* _pHighVal, uint32* _pLowVal )
{
    if ( _pLowVal )
    {
        (*_pLowVal) = uint32(_value & 0xffffffffull);
    }

    if ( _pHighVal )
    {
        (*_pHighVal) = uint32(_value>>32ull);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE void split_int64 ( int64 _value, int32* _pHighVal, int32* _pLowVal )
{
    if ( _pLowVal )
    {
        (*_pLowVal) = int32(_value & 0xffffffffull);
    }

    if ( _pHighVal )
    {
        (*_pHighVal) = int32(_value>>32ull);
    }
}

///////////////////////////////////////////////////////////////////////////////
// swap byte
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <int N>
INLINE void swap_n_bytes ( void* _pValue )
{
    uint8* p = (uint8*)_pValue;
    uint32 i = 0;
    uint32 j = N - 1;
    uint8  t;
    
    while(i < j)
    {
        t = p[i];

        p[i] = p[j];
        p[j] = t;

        i++;
        j--;
    }
}

// ------------------------------------------------------------------ 
// Desc: swap_n_bytes specialisation for 1 byte. Does nothing (no swapping needed).
// ------------------------------------------------------------------ 

template <>
INLINE void swap_n_bytes<1> ( void* _pValue )
{
    EX_UNUSED(_pValue);
}

// ------------------------------------------------------------------ 
// Desc: swap_n_bytes specialisation for 2 bytes.
// ------------------------------------------------------------------ 

template <>
INLINE void swap_n_bytes<2> ( void* _pValue )
{
    uint16* pVal = (uint16*)_pValue;
    *pVal = (((*pVal) >> 8) & 0xff) | (((*pVal) & 0xff) << 8);
}

// ------------------------------------------------------------------ 
// Desc: swap_n_bytes specialisation for 4 bytes.
// ------------------------------------------------------------------ 

template <>
INLINE void swap_n_bytes<4> ( void* _pValue )
{
#if ( EX_PLATFORM == EX_WIN32 ) && ( EX_COMPILER == EX_MSVC )
    __asm
    {
        mov     esi, _pValue
        mov		eax, [esi]
        bswap	eax
        mov     [esi], eax
    }
#else
    // TODO: other platform
#endif
}

// ------------------------------------------------------------------ 
// Desc: swap_n_bytes specialisation for 8 bytes.
// ------------------------------------------------------------------ 

template <>
INLINE void swap_n_bytes<8> ( void* _pValue )
{
#if ( EX_PLATFORM == EX_WIN32 ) && ( EX_COMPILER == EX_MSVC )
    __asm
    {
        mov     esi, _pValue
        mov		eax, [esi]
        mov		ebx, [esi+4]
        bswap	eax
        bswap	ebx		
        mov     [esi], ebx
        mov     [esi+4], eax
    }
#else
    // TODO: other platform
#endif
}

// ######################### 
} // end namespace _private 
// ######################### 


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void swap_byte ( T& _value )
{ 
    _private::swap_n_bytes<sizeof(T)>(&_value);    
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T>
INLINE T swap_byte ( const T& _value )
{
    T v = _value;
    swap_byte(v);
    return v;
}

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END BIT_H_1250523573
// #################################################################################
