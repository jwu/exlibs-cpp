// ======================================================================================
// File         : CRC.cpp
// Author       : Wu Jie 
// Last Change  : 08/08/2009 | 12:29:08 PM | Saturday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "CRC.h"

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace _private { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint32 calc_crc ( int _crcSize, const uint8* _pData, uint _len )
{
    ex_assert( _pData, "invalid _pData value" );
    ex_assert( ex::is_powof2(_crcSize), "_crcSize should be power of 2" );
    register uint32 result = ~0UL;

#if EX_USE_CRC_TABLE

// ======================================================== 
#if EX_USE_CRC_TABLE_FAST 
// ======================================================== 

    uint32 i;

    if (_len && ((size_t)_pData & 2))
    {            
        result = CRC_Table0[(result ^ *_pData++) & 0xff] ^ (result >> 8);
        result = CRC_Table0[(result ^ *_pData++) & 0xff] ^ (result >> 8);
        _len -= 2;
    }

    if (_len && ((size_t)_pData & 1))
    {
        result = CRC_Table0[(result ^ *_pData++) & 0xff] ^ (result >> 8);
        _len--;
    }

    const uint32 *buf_array = (const uint32*)_pData;

    for (i = 0; i < (_len >> 2); ++i)
    {
        uint32 val = buf_array[i];

#if (EX_ENDIAN == EX_BIG_ENDIAN)
        swap_byte(val);
#endif

        result ^= val;

        result = CRC_Table3[(result) & 0xff] ^ 
            CRC_Table2[((result) >> 8) & 0xff] ^
            CRC_Table1[((result) >> 16) & 0xff] ^ 
            CRC_Table0[(result) >> 24];
    }

    _pData += (i << 2);
    _len -= (i << 2);

    if (_len & 2)
    {
        result = CRC_Table0[(result ^ *_pData++) & 0xff] ^ (result >> 8);
        result = CRC_Table0[(result ^ *_pData++) & 0xff] ^ (result >> 8);
    }

    if (_len & 1)
        result = CRC_Table0[(result ^ *_pData++) & 0xff] ^ (result >> 8);

    result ^= 0xffffffff;
    result &= ((((uint32)1 << (_crcSize - 1)) - 1) << 1) | 1;

// ======================================================== 
#else // else if use normal crc
// ======================================================== 

    // Align on 4-bytes boundaries
    for (; ((uint32)(size_t)(void*)_pData) & (sizeof(uint32) - 1); _pData++, _len--) 
    {
        result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ *_pData]);

        if (_len == 0) 
        {
            result ^= 0xffffffff;
            result &= ((((uint32)1 << (_crcSize - 1)) - 1) << 1) | 1;
            return result;
        }
    }

    uint32 count = _len >> 2;

    // 4-by-4
    for(unsigned i = 0; i < count; ++i)                    
    {        
        uint32 val = *(uint32 const*)_pData;

#if (EX_ENDIAN == EX_BIG_ENDIAN)
        swap_byte(val);
#endif

        result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ (val & 0xff)]);
        result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ ((val & 0xff00) >> 8)]);
        result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ ((val & 0xff0000) >> 16)]);
        result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ ((val & 0xff000000) >> 24)]);

        _pData += 4;
    }

    // one-by-one
    count = _len - (count << 2);
    for(unsigned i = 0; i < count; ++i)                    
        result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ *_pData++]);

    result ^= 0xffffffff;
    result &= ((((uint32)1 << (_crcSize - 1)) - 1) << 1) | 1;

// ======================================================== 
#endif // END EX_USE_CRC_TABLE_FAST
// ======================================================== 

#else
    ex_warning ( "CRC Hash is disabled. Please Enable EX_USE_CRC_TABLE in config.h" );
#endif // END !EX_USE_CRC_TABLE

    return result;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint32 calc_crc_hash_str ( int _crcSize, const char* _pData )
{
    ex_assert( _pData, "invalid _pData value" );
    ex_assert( ex::is_powof2(_crcSize), "_crcSize should be power of 2" );
    register uint32 result = ~0UL;

#if EX_USE_CRC_TABLE
    const char* p = _pData;
    uint32 m = 0x7efefeff, n = ~m, i;

    // Align on 4-bytes boundaries
    for ( ; ((uint32)(size_t)(void*)p) & (sizeof(uint32) - 1); ++p ) 
    {
        if (!*p)
        {
            result ^= 0xffffffff;
            result &= ((((uint32)1 << (_crcSize - 1)) - 1) << 1) | 1;
            return result;
        }

        result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ *p]);
    }

    // Process bytes 4-by-4 as much as possible, then one-by-one for the bytes left
    for (;;) 
    {
        i = *(uint32 const*)p;

#if (EX_ENDIAN == EX_BIG_ENDIAN)
        swap_byte(i);
#endif

        if (!(((i + m) ^ ~i) & n)) 
        {
            p += sizeof(uint32);

#if EX_USE_CRC_TABLE_FAST 
            result ^= i;
            result = CRC_Table3[ (result) & 0xff] ^ 
                CRC_Table2[((result) >> 8) & 0xff] ^
                CRC_Table1[((result) >> 16) & 0xff] ^ 
                CRC_Table0[ (result) >> 24];
#else
            result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ (i & 0xff)]);
            result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ ((i & 0xff00) >> 8)]);
            result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ ((i & 0xff0000) >> 16)]);
            result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ ((i & 0xff000000) >> 24)]);
#endif
        }
        else 
        {
            // Process left bytes
            for ( i = sizeof(uint32); i; ++p, --i ) 
            {
                if (!*p)
                {
                    result ^= 0xffffffff;
                    result &= ((((uint32)1 << (_crcSize - 1)) - 1) << 1) | 1;
                    return result;
                }

                result = ((result >> 8) ^ CRC_Table0[(result & 0xFFUL) ^ *p]);
            }

            result ^= 0xffffffff;
            result &= ((((uint32)1 << (_crcSize - 1)) - 1) << 1) | 1;
            return result;
        }

    } // for

#else
    ex_warning ( "CRC Hash is disabled. Please Enable EX_USE_CRC_TABLE in config.h" );
#endif // END !EX_USE_CRC_TABLE

    return result;
}

// ######################### 
} // end namespace _private 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 
