// ======================================================================================
// File         : hash.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 11:34:25 AM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASH_H_1250523906
#define HASH_H_1250523906
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "crc.h"
#include "str_op.h"

// #########################
namespace ex {
// #########################

///////////////////////////////////////////////////////////////////////////////
// config
///////////////////////////////////////////////////////////////////////////////

#define EX_HASH_PAUL 0x01
#define EX_HASH_BOB2 0x02
#define EX_HASH_BOB3 0x03
#define EX_HASH_CRC  0x04

// setup as you wish
#define EX_HASH_METHOD EX_HASH_BOB3
#define EX_HASH_SEED    0xFF

///////////////////////////////////////////////////////////////////////////////
// Conclusion
///////////////////////////////////////////////////////////////////////////////

/// This library offers many different hashing function with different collision efficiency & execution speed. 
// - CRC   : Classic Cyclic Redundancy check
// - CRC4  : Same as CRC, but process 4 bytes at a time and is faster (while giving the same value than CRC)
// - Bob2  : Algorithm from Doctor Dobb's web site (http://burtleburtle.net/bob/hash/doobs.html)
// - Bob3  : Algorithm from Doctor Dobb's web site (http://burtleburtle.net/bob/hash/doobs.html)
// - Paul  : Written by Paul Hsieh (http://www.azillionmonkeys.com/qed/hash.html)

// Speed (vs CRC):
// - CRC   : 1.00 (reference speed)
// - CRC4  : 2.08 times faster than CRC
// - Bob2  : 1.81 times faster than CRC
// - Bob3  : 3.00 times faster than CRC TODO: not test
// - Paul  : 2.85 times faster than CRC

// Average Collisions generated when parsing 'Iliad' by Homer & 'The Holy Bible'
// - CRC   : 0% collision on an average dictionary of around 30000 words
// - CRC4  : Same as CRC
// - Bob2  : 0% collision on an average dictionary of around 30000 words
// - Bob3  : 0% collision on an average dictionary of around 30000 words TODO: not test
// - Paul  : 0.02% collision on an average dictionary of around 30000 words

///////////////////////////////////////////////////////////////////////////////
//  Bob Jenkins' Hash 2
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

EX_LIBS_DLL uint32 hash_bob2( const uint8* _pData, uint32 _len, uint32 _seed = 0 );

///////////////////////////////////////////////////////////////////////////////
//  Bob Jenkins' Hash 3
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: hash_uint32 
// ------------------------------------------------------------------

EX_LIBS_DLL uint32 hash_uint32( const uint32* _pData, uint32 _len, uint32 _seed = 0 );
EX_LIBS_DLL void hash_uint32( const uint32* _pData, uint32 _len, uint32* _pSeed1, uint32* _pSeed2 );

// ------------------------------------------------------------------
// Desc: hash_little
// ------------------------------------------------------------------

EX_LIBS_DLL uint32 hash_little( const void* _pData, uint32 _len, uint32 _seed );
EX_LIBS_DLL void hash_little( const void* _pData, uint32 _len, uint32* _pSeed1, uint32* _pSeed2 );

// ------------------------------------------------------------------
// Desc: hash_big
// ------------------------------------------------------------------

EX_LIBS_DLL uint32 hash_big( const void* _pData, uint32 _len, uint32 _seed );
EX_LIBS_DLL void hash_big( const void* _pData, uint32 _len, uint32* _pSeed1, uint32* _pSeed2 );

// ------------------------------------------------------------------
// Desc: hash_bob3 ( 1 seed )
// ------------------------------------------------------------------

// ========================================================
// uint32
// ========================================================

INLINE uint32 hash_bob3( const uint32* _pData, uint32 _len, uint32 _seed = 0 )
{
    return hash_uint32( _pData, _len, _seed );
}

// ========================================================
// void* 
// ========================================================

INLINE uint32 hash_bob3( const void* _pData, uint32 _len, uint32 _seed = 0 )
{
#if (EX_ENDIAN == EX_LITTLE_ENDIAN)
    return hash_little( _pData, _len, _seed );
#else
    return hash_big( _pData, _len, _seed );
#endif
}

// ------------------------------------------------------------------
// Desc: hash_bob3 ( 2 seed )
// ------------------------------------------------------------------

// ========================================================
// uint32
// ========================================================

INLINE void hash_bob3( const uint32* _pData, uint32 _len, uint32* _pSeed1, uint32* _pSeed2 )
{
    hash_uint32( _pData, _len, _pSeed1, _pSeed2 );
}

// ========================================================
// void* 
// ========================================================

INLINE void hash_bob3( const void* _pData, uint32 _len, uint32* _pSeed1, uint32* _pSeed2 )
{
#if (EX_ENDIAN == EX_LITTLE_ENDIAN)
    hash_little( _pData, _len, _pSeed1, _pSeed2 );
#else
    hash_big( _pData, _len, _pSeed1, _pSeed2 );
#endif
}

///////////////////////////////////////////////////////////////////////////////
//  Paul Hsieh's Hash
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

EX_LIBS_DLL uint32 hash_paul( const uint8* _pData, uint32 _len );

///////////////////////////////////////////////////////////////////////////////
// CRC Hash
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: uint32 
// ------------------------------------------------------------------ 

template <int CRC_SIZE>
uint32 hash_crc ( const uint8* _pData, uint32 _len )
{
    return _private::calc_crc ( CRC_SIZE, _pData, _len );
}

// ------------------------------------------------------------------ 
// Desc: uint32 
// ------------------------------------------------------------------ 

template <int CRC_SIZE>
uint32 hash_crc ( const char* _pData )
{
    return _private::calc_crc_hash_str ( CRC_SIZE, _pData );
}

///////////////////////////////////////////////////////////////////////////////
//  General Hash Method
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: EX_HASH user configure
// ------------------------------------------------------------------

#define EX_HASH_METHOD  EX_HASH_BOB3
#define EX_HASH_SEED    0xFF

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------
// Desc: string with length 
// ------------------------------------------------------------------

// ======================================================== 
// const char*
// ======================================================== 

INLINE uint32 hash_str( const void* _str, uint32 _bytes )
{
#if (EX_HASH_METHOD == EX_HASH_PAUL)
    return hash_paul( (uint8*)_str, _bytes );
#elif (EX_HASH_METHOD == EX_HASH_BOB2)
    return hash_bob2( (uint8*)_str, _bytes, EX_HASH_SEED );
#elif (EX_HASH_METHOD == EX_HASH_BOB3)
    return hash_bob3( (void*)_str, _bytes, EX_HASH_SEED );
#elif (EX_HASH_METHOD == EX_HASH_CRC)
    return hash_crc<32> ( _str );
#endif
}

// ######################### 
} // end namespace _private 
// ######################### 

// ------------------------------------------------------------------
// Desc: string without length
// ------------------------------------------------------------------

// ======================================================== 
// const char* 
// ======================================================== 

INLINE uint32 hash_str( const char* _str )
{
    return _private::hash_str( _str, ex::str::len(_str) );
}

// ======================================================== 
// const wchar* 
// ======================================================== 

INLINE uint32 hash_str( const wchar* _str )
{
    return _private::hash_str( _str, ex::str::len(_str) * 2 );
}

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------
// Desc: hash_use string
// ------------------------------------------------------------------

INLINE uint32 hash_use( int _method, const void* _str, uint32 _bytes )
{
    switch( _method ) {
    case EX_HASH_PAUL:
        return hash_paul( (uint8*)_str, _bytes );

    case EX_HASH_BOB2:
        return hash_bob2( (uint8*)_str, _bytes, EX_HASH_SEED );

    case EX_HASH_BOB3:
        return hash_bob3( (void*)_str, _bytes, EX_HASH_SEED );

    case EX_HASH_CRC:
        return hash_crc<32> ( (uint8*)_str, _bytes );

    default:
        ex_assert( false, "Hash method not found!" ); // NOTE: can't use ex_warning at header define before Debug/Log.h
        return 0;
    }
}

// ######################### 
} // end namespace _private 
// ######################### 

// ------------------------------------------------------------------
// Desc: hash_use void*
// ------------------------------------------------------------------

// ======================================================== 
// const char*
// ======================================================== 

INLINE uint32 hash_use( int _hash_method, const char* _str )
{
    return _private::hash_use( _hash_method, _str, ex::str::len(_str) );
}

// ======================================================== 
// const wchar* 
// ======================================================== 

INLINE uint32 hash_use( int _hash_method, const wchar* _str )
{
    return _private::hash_use( _hash_method, _str, ex::str::len(_str) * 2 );
}

// #########################
} // end namespace ex
// #########################

// #################################################################################
#endif // END HASH_H_1250523906
// #################################################################################
