// ======================================================================================
// File         : Hash.cpp
// Author       : Wu Jie 
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "Hash.h"

// #########################
namespace ex {
// #########################

///////////////////////////////////////////////////////////////////////////////
//  Hash Function Define
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//  Bob Jenkins' Hash 2
//      http://burtleburtle.net/bob/hash/doobs.html
//      by Bob Jenkins, December 1996, Public Domain.
//       hash(), hash2(), hash3, and __mix() are externally useful functions.
//       Routines to test the hash are included if SELF_TEST is defined.
//       You can use this free for any purpose.  It has no warranty.
//       
//       Obsolete.  Use Bob3 Hash instead, it is faster and more thorough.
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// __mix
//  __mix -- __mix 3 32-bit values reversibly.
//  For every delta with one or two bit set, and the deltas of all three
//    high bits or all three low bits, whether the original value of a,b,c
//    is almost all zero or is uniformly distributed,
//  * If __mix() is run forward or backward, at least 32 bits in a,b,c
//    have at least 1/4 probability of changing.
//  * If __mix() is run forward, every bit of c will change between 1/3 and
//    2/3 of the time.  (Well, 22/100 and 78/100 for some 2-bit deltas.)
//
//  __mix() was built out of 36 single-cycle latency instructions in a 
//    structure that could supported 2x parallelism, like so:
//        a -= b; 
//        a -= c; x = (c>>13);
//        b -= c; a ^= x;
//        b -= a; x = (a<<8);
//        c -= a; b ^= x;
//        c -= b; x = (b>>13);
//        ...
//    Unfortunately, superscalar Pentiums and Sparcs can't take advantage 
//    of that parallelism.  They've also turned some of those single-cycle
//    latency instructions into multi-cycle latency instructions.  Still,
//    this is the fastest good hash I could find.  There were about 2^^68
//    to choose from.  I only looked at a billion or so.
// ------------------------------------------------------------------
#ifdef __mix 
#undef __mix
#endif

#define __mix(a,b,c) \
{ \
    a -= b; a -= c; a ^= (c>>13);   \
    b -= c; b -= a; b ^= (a<<8);    \
    c -= a; c -= b; c ^= (b>>13);   \
    a -= b; a -= c; a ^= (c>>12);   \
    b -= c; b -= a; b ^= (a<<16);   \
    c -= a; c -= b; c ^= (b>>5);    \
    a -= b; a -= c; a ^= (c>>3);    \
    b -= c; b -= a; b ^= (a<<10);   \
    c -= a; c -= b; c ^= (b>>15);   \
}

// ------------------------------------------------------------------
// Desc: 
//  hash a variable-length _pData into a 32-bit value
//      @params
//        _pData     : the _pData (the unaligned variable-length array of bytes)
//        _len       : the length of the _pData, counting by bytes
//        _seed      : can be any 4-byte value
//      Returns a 32-bit value.  Every bit of the _pData affects every bit of
//      the return value.  Every 1-bit and 2-bit delta achieves avalanche.
//      About 36+6len instructions.
//      
//      The best hash table sizes are powers of 2.  There is no need to do
//      mod a prime (mod is sooo slow!).  If you need less than 32 bits,
//      use a bitmask.  For example, if you need only 10 bits, do
//        h = (h & hashmask(10));
//      In which case, the hash table should have hashsize(10) elements.
//      
//      If you are hashing n strings (ub1 **)k, do it like this:
//        for (i=0, h=0; i<n; ++i) h = hash( k[i], len[i], h);
//      
//      By Bob Jenkins, 1996.  bob_jenkins@burtleburtle.net.  You may use this
//      code any way you wish, private, educational, or commercial.  It's free.
//      
//      See http://burtleburtle.net/bob/hash/evahash.html
//      Use for hash table lookup, or anything where one collision in 2^32 is
//      acceptable.  Do NOT use for cryptographic purposes.
// ------------------------------------------------------------------
uint32 hash_bob2( const uint8* _pData, uint32 _len, uint32 _seed )
{
    register uint32 a,b,c,len;

    /* Set up the internal state */
    len = _len;
    a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
    c = _seed;           /* the previous hash value */

    /*---------------------------------------- handle most of the _pData */
    while (len >= 12)
    {
        a += (_pData[0] +((uint32)_pData[1] << 8) +((uint32)_pData[2]  << 16) +((uint32)_pData[3] << 24));
        b += (_pData[4] +((uint32)_pData[5] << 8) +((uint32)_pData[6]  << 16) +((uint32)_pData[7] << 24));
        c += (_pData[8] +((uint32)_pData[9] << 8) +((uint32)_pData[10] << 16)+((uint32)_pData[11] << 24));
        __mix(a,b,c);
        _pData += 12; len -= 12;
    }

    /*------------------------------------- handle the last 11 bytes */
    c += _len;
    switch(len)              /* all the case statements fall through */
    {
    case 11: c+=((uint32)_pData[10]<<24);
    case 10: c+=((uint32)_pData[9]<<16);
    case 9 : c+=((uint32)_pData[8]<<8);
             /* the first byte of c is reserved for the length */
    case 8 : b+=((uint32)_pData[7]<<24);
    case 7 : b+=((uint32)_pData[6]<<16);
    case 6 : b+=((uint32)_pData[5]<<8);
    case 5 : b+=_pData[4];
    case 4 : a+=((uint32)_pData[3]<<24);
    case 3 : a+=((uint32)_pData[2]<<16);
    case 2 : a+=((uint32)_pData[1]<<8);
    case 1 : a+=_pData[0];
             /* case 0: nothing left to add */
    }
    __mix(a,b,c);
    /*-------------------------------------------- report the result */
    return c;
}

///////////////////////////////////////////////////////////////////////////////
//  Bob Jenkins' Hash 3
//      http://burtleburtle.net/bob/hash/doobs.html
//        by Bob Jenkins, May 2006, Public Domain.
//       
//       These are functions for producing 32-bit hashes for hash table lookup.
//       hashword(), hashlittle(), hashlittle2(), hashbig(), __mix(), and __final() 
//       are externally useful functions.  Routines to test the hash are included 
//       if SELF_TEST is defined.  You can use this free for any purpose.  It's in
//       the public domain.  It has no warranty.
//       
//       You probably want to use hashlittle().  hashlittle() and hashbig()
//       hash byte arrays.  hashlittle() is is faster than hashbig() on
//       little-endian machines.  Intel and AMD are little-endian machines.
//       On second thought, you probably want hashlittle2(), which is identical to
//       hashlittle() except it returns two 32-bit hashes for the price of one.  
//       You could implement hashbig2() if you wanted but I haven't bothered here.
//       
//       If you want to find a hash of, say, exactly 7 integers, do
//         a = i1;  b = i2;  c = i3;
//         __mix(a,b,c);
//         a += i4; b += i5; c += i6;
//         __mix(a,b,c);
//         a += i7;
//         __final(a,b,c);
//       then use c as the hash value.  If you have a variable length array of
//       4-byte integers to hash, use hashword().  If you have a byte array (like
//       a character string), use hashlittle().  If you have several byte arrays, or
//       a __mix of things, see the comments above hashlittle().  
//       
//       Why is this so big?  I read 12 bytes at a time into 3 4-byte integers, 
//       then __mix those integers.  This is fast (you can do a lot more thorough
//       mixing with 12*3 instructions on 3 integers than you can with 3 instructions
//       on 1 byte), but shoehorning those bytes into integers efficiently is messy.
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------
#if (EX_ENDIAN == EX_LITTLE_ENDIAN)
    #define __HASH_LITTLE_ENDIAN 1
    #define __HASH_BIG_ENDIAN 0
#elif (EX_ENDIAN == EX_BIG_ENDIAN)
    #define __HASH_LITTLE_ENDIAN 0
    #define __HASH_BIG_ENDIAN 1
#endif

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------
#ifdef __rot 
#undef __rot
#endif

#define __rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))

// ------------------------------------------------------------------
// Desc: 
// __mix
//
//  This is reversible, so any information in (a,b,c) before __mix() is
//  still in (a,b,c) after __mix().
//  
//  If four pairs of (a,b,c) inputs are run through __mix(), or through
//  __mix() in reverse, there are at least 32 bits of the output that
//  are sometimes the same for one pair and different for another pair.
//  This was tested for:
//  * pairs that differed by one bit, by two bits, in any combination
//    of top bits of (a,b,c), or in any combination of bottom bits of
//    (a,b,c).
//  * "differ" is defined as +, -, ^, or ~^.  For + and -, I transformed
//    the output delta to a Gray code (a^(a>>1)) so a string of 1's (as
//    is commonly produced by subtraction) look like a single 1-bit
//    difference.
//  * the base values were pseudorandom, all zero but one bit set, or 
//    all zero plus a counter that starts at zero.
//  
//  Some k values for my "a-=c; a^=rot(c,k); c+=b;" arrangement that
//  satisfy this are
//      4  6  8 16 19  4
//      9 15  3 18 27 15
//     14  9  3  7 17  3
//  Well, "9 15 3 18 27 15" didn't quite get 32 bits diffing
//  for "differ" defined as + with a one-bit base and a two-bit delta.  I
//  used http://burtleburtle.net/bob/hash/avalanche.html to choose 
//  the operations, constants, and arrangements of the variables.
//  
//  This does not achieve avalanche.  There are input bits of (a,b,c)
//  that fail to affect some output bits of (a,b,c), especially of a.  The
//  most thoroughly mixed value is c, but it doesn't really even achieve
//  avalanche in c.
//  
//  This allows some parallelism.  Read-after-writes are good at doubling
//  the number of bits affected, so the goal of mixing pulls in the opposite
//  direction as the goal of parallelism.  I did what I could.  Rotates
//  seem to cost as much as shifts on every machine I could lay my hands
//  on, and rotates are much kinder to the top and bottom bits, so I used
//  rotates.
// ------------------------------------------------------------------
#ifdef __mix 
#undef __mix
#endif

#define __mix(a,b,c) \
{ \
    a -= c;  a ^= __rot(c, 4);  c += b; \
    b -= a;  b ^= __rot(a, 6);  a += c; \
    c -= b;  c ^= __rot(b, 8);  b += a; \
    a -= c;  a ^= __rot(c,16);  c += b; \
    b -= a;  b ^= __rot(a,19);  a += c; \
    c -= b;  c ^= __rot(b, 4);  b += a; \
}

// ------------------------------------------------------------------
// Desc:
// __final
// __final -- __final mixing of 3 32-bit values (a,b,c) into c
// 
// Pairs of (a,b,c) values differing in only a few bits will usually
// produce values of c that look totally different.  This was tested for
// * pairs that differed by one bit, by two bits, in any combination
//   of top bits of (a,b,c), or in any combination of bottom bits of
//   (a,b,c).
// * "differ" is defined as +, -, ^, or ~^.  For + and -, I transformed
//   the output delta to a Gray code (a^(a>>1)) so a string of 1's (as
//   is commonly produced by subtraction) look like a single 1-bit
//   difference.
// * the base values were pseudorandom, all zero but one bit set, or 
//   all zero plus a counter that starts at zero.
// 
// These constants passed:
//  14 11 25 16 4 14 24
//  12 14 25 16 4 14 24
// and these came close:
//   4  8 15 26 3 22 24
//  10  8 15 26 3 22 24
//  11  8 15 26 3 22 24
// ------------------------------------------------------------------
#ifdef __final
#undef __final
#endif

#define __final(a,b,c) \
{ \
    c ^= b; c -= __rot(b,14); \
    a ^= c; a -= __rot(c,11); \
    b ^= a; b -= __rot(a,25); \
    c ^= b; c -= __rot(b,16); \
    a ^= c; a -= __rot(c,4);  \
    b ^= a; b -= __rot(a,14); \
    c ^= b; c -= __rot(b,24); \
}

// ------------------------------------------------------------------
// Desc:
// hash_uint32
// This works on all machines.  To be useful, it requires
// -- that the _pData be an array of uint32's, and
// -- that the length be the number of uint32's in the _pData
//
// The function hashword() is identical to hashlittle() on little-endian
// machines, and identical to hashbig() on big-endian machines,
// except that the length has to be measured in UINT32s rather than in
// bytes.  hashlittle() is more complicated than hashword() only because
// hashlittle() has to dance around fitting the _pData bytes into registers.
//
// @params:
//      _pData     : the _pData, an array of uint32 values
//      _len       : the length of the _pData, counting by bytes
//      _seed      : can be any 4-byte value
// ------------------------------------------------------------------
uint32 hash_uint32( const uint32* _pData, uint32 _len, uint32 _seed )
{
    uint32 a,b,c;

    /* Set up the internal state */
    a = b = c = 0xdeadbeef + (((uint32)_len)<<2) + _seed;

    /*------------------------------------------------- handle most of the _pData */
    while (_len > 3)
    {
        a += _pData[0];
        b += _pData[1];
        c += _pData[2];
        __mix(a,b,c);
        _len -= 3;
        _pData += 3;
    }

    /*------------------------------------------- handle the last 3 uint32's */
    switch(_len)                     /* all the case statements fall through */
    { 
    case 3 : c+=_pData[2];
    case 2 : b+=_pData[1];
    case 1 : a+=_pData[0];
             __final(a,b,c);
    case 0:     /* case 0: nothing left to add */
             break;
    }
    /*------------------------------------------------------ report the result */
    return c;
}

// ------------------------------------------------------------------
// Desc:
// hash_uint32 (2 seed)
//  hashword2() -- same as hashword(), but take two seeds and return two
//  32-bit values.  pSeed1 and pSeed2 must both be nonnull, and *pSeed1 and *pSeed2 must
//  both be initialized with seeds.  If you pass in (*pSeed2)==0, the output 
//  (*pSeed1) will be the same as the return value from hashword().
//
//  @params:
//      _pData     : the _pData, an array of uint32 values
//      _len       : the length of the _pData, counting by bytes
//      _pSeed1    :    IN: seed OUT: primary hash value 
//      _pSeed2    :    IN: more seed OUT: secondary hash value 
// ------------------------------------------------------------------
void hash_uint32( const uint32* _pData, uint32 _len, uint32* _pSeed1, uint32* _pSeed2 )
{
    uint32 a,b,c;

    /* Set up the internal state */
    a = b = c = 0xdeadbeef + ((uint32)(_len<<2)) + *_pSeed1;
    c += *_pSeed2;

    /*------------------------------------------------- handle most of the _pData */
    while (_len > 3)
    {
        a += _pData[0];
        b += _pData[1];
        c += _pData[2];
        __mix(a,b,c);
        _len -= 3;
        _pData += 3;
    }

    /*------------------------------------------- handle the last 3 uint32's */
    switch(_len)                     /* all the case statements fall through */
    { 
    case 3 : c+=_pData[2];
    case 2 : b+=_pData[1];
    case 1 : a+=_pData[0];
             __final(a,b,c);
    case 0:     /* case 0: nothing left to add */
             break;
    }
    /*------------------------------------------------------ report the result */
    *_pSeed1=c; *_pSeed2=b;
}

// ------------------------------------------------------------------
// Desc:
// hash_little (1 seed)
//  hashlittle() -- hash a variable-length _pData into a 32-bit value
//      @params:
//          _pData : the _pData 
//          _len   : the length of the _pData, counting by bytes
//          _seed  : can be any 4-byte value
//  Returns a 32-bit value.  Every bit of the _pData affects every bit of
//  the return value.  Two _pDatas differing by one or two bits will have
//  totally different hash values.
//  
//  The best hash table sizes are powers of 2.  There is no need to do
//  mod a prime (mod is sooo slow!).  If you need less than 32 bits,
//  use a bitmask.  For example, if you need only 10 bits, do
//    h = (h & hashmask(10));
//  In which case, the hash table should have hashsize(10) elements.
//  
//  If you are hashing n strings (uint8 **)k, do it like this:
//    for (i=0, h=0; i<n; ++i) h = hashlittle( k[i], len[i], h);
//  
//  By Bob Jenkins, 2006.  bob_jenkins@burtleburtle.net.  You may use this
//  code any way you wish, private, educational, or commercial.  It's free.
//  
//  Use for hash table lookup, or anything where one collision in 2^^32 is
//  acceptable.  Do NOT use for cryptographic purposes.
// ------------------------------------------------------------------
uint32 hash_little( const void* _pData, uint32 _len, uint32 _seed )
{
    uint32 a,b,c;                                          /* internal state */
    union { const void* ptr; size_t i; } u;     /* needed for Mac Powerbook G4 */

    /* Set up the internal state */
    a = b = c = 0xdeadbeef + ((uint32)_len) + _seed;

    u.ptr = _pData;
    if (__HASH_LITTLE_ENDIAN && ((u.i & 0x3) == 0)) 
    {
        const uint32* pData32 = (const uint32 *)_pData;         /* read 32-bit chunks */

        /*------ all but last block: aligned reads and affect 32 bits of (a,b,c) */
        while (_len > 12)
        {
            a += pData32[0];
            b += pData32[1];
            c += pData32[2];
            __mix(a,b,c);
            _len -= 12;
            pData32 += 3;
        }

        /*----------------------------- handle the last (probably partial) block */
        /* 
         * "pData32[2]&0xffffff" actually reads beyond the end of the string, but
         * then masks off the part it's not allowed to read.  Because the
         * string is aligned, the masked-off tail is in the same word as the
         * rest of the string.  Every machine with memory protection I've seen
         * does it on word boundaries, so is OK with this.  But VALGRIND will
         * still catch it and complain.  The masking trick does make the hash
         * noticably faster for short strings (like English words).
         */
#ifndef VALGRIND

        switch(_len)
        {
        case 12: c+=pData32[2];             b+=pData32[1];  a+=pData32[0];  break;
        case 11: c+=pData32[2]&0xffffff;    b+=pData32[1];  a+=pData32[0];  break;
        case 10: c+=pData32[2]&0xffff;      b+=pData32[1];  a+=pData32[0];  break;
        case 9 : c+=pData32[2]&0xff;        b+=pData32[1];  a+=pData32[0];  break;
        case 8 : b+=pData32[1];             a+=pData32[0];                  break;
        case 7 : b+=pData32[1]&0xffffff;    a+=pData32[0];                  break;
        case 6 : b+=pData32[1]&0xffff;      a+=pData32[0];                  break;
        case 5 : b+=pData32[1]&0xff;        a+=pData32[0];                  break;
        case 4 : a+=pData32[0];                                             break;
        case 3 : a+=pData32[0]&0xffffff;                                    break;
        case 2 : a+=pData32[0]&0xffff;                                      break;
        case 1 : a+=pData32[0]&0xff;                                        break;
        case 0 : return c;              /* zero _len strings require no mixing */
        }

#else /* make valgrind happy */

        const uint8* pData8 = (const uint8 *)pData32;
        switch(_len)
        {
        case 12: c+=pData32[2]; b+=pData32[1]; a+=pData32[0]; break;
        case 11: c+=((uint32)pData8[10])<<16;           /* fall through */
        case 10: c+=((uint32)pData8[9])<<8;             /* fall through */
        case 9 : c+=pData8[8];                          /* fall through */
        case 8 : b+=pData32[1]; a+=pData32[0]; break;
        case 7 : b+=((uint32)pData8[6])<<16;            /* fall through */
        case 6 : b+=((uint32)pData8[5])<<8;             /* fall through */
        case 5 : b+=pData8[4];                          /* fall through */
        case 4 : a+=pData32[0]; break;
        case 3 : a+=((uint32)pData8[2])<<16;            /* fall through */
        case 2 : a+=((uint32)pData8[1])<<8;             /* fall through */
        case 1 : a+=pData8[0]; break;
        case 0 : return c;
        }

#endif /* !valgrind */

    } 
    else if (__HASH_LITTLE_ENDIAN && ((u.i & 0x1) == 0)) 
    {
        const uint16* pData16 = (const uint16 *)_pData;         /* read 16-bit chunks */
        const uint8* pData8;

        /*--------------- all but last block: aligned reads and different mixing */
        while (_len > 12)
        {
            a += pData16[0] + (((uint32)pData16[1])<<16);
            b += pData16[2] + (((uint32)pData16[3])<<16);
            c += pData16[4] + (((uint32)pData16[5])<<16);
            __mix(a,b,c);
            _len -= 12;
            pData16 += 6;
        }

        /*----------------------------- handle the last (probably partial) block */
        pData8 = (const uint8 *)pData16;
        switch(_len)
        {
        case 12: c+=pData16[4]+(((uint32)pData16[5])<<16);
                 b+=pData16[2]+(((uint32)pData16[3])<<16);
                 a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 11: c+=((uint32)pData8[10])<<16;               /* fall through */
        case 10: c+=pData16[4];
                 b+=pData16[2]+(((uint32)pData16[3])<<16);
                 a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 9 : c+=pData8[8];                              /* fall through */
        case 8 : b+=pData16[2]+(((uint32)pData16[3])<<16);
                 a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 7 : b+=((uint32)pData8[6])<<16;                /* fall through */
        case 6 : b+=pData16[2];
                 a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 5 : b+=pData8[4];                              /* fall through */
        case 4 : a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 3 : a+=((uint32)pData8[2])<<16;                /* fall through */
        case 2 : a+=pData16[0];
                 break;
        case 1 : a+=pData8[0];
                 break;
        case 0 : return c;                     /* zero _len requires no mixing */
        }
    }
    else 
    {                        /* need to read the _pData one byte at a time */
        const uint8 *pData8 = (const uint8 *)_pData;

        /*--------------- all but the last block: affect some 32 bits of (a,b,c) */
        while (_len > 12)
        {
            a += pData8[0];
            a += ((uint32)pData8[1])<<8;
            a += ((uint32)pData8[2])<<16;
            a += ((uint32)pData8[3])<<24;
            b += pData8[4];
            b += ((uint32)pData8[5])<<8;
            b += ((uint32)pData8[6])<<16;
            b += ((uint32)pData8[7])<<24;
            c += pData8[8];
            c += ((uint32)pData8[9])<<8;
            c += ((uint32)pData8[10])<<16;
            c += ((uint32)pData8[11])<<24;
            __mix(a,b,c);
            _len -= 12;
            pData8 += 12;
        }

        /*-------------------------------- last block: affect all 32 bits of (c) */
        switch(_len)                   /* all the case statements fall through */
        {
        case 12: c+=((uint32)pData8[11])<<24;
        case 11: c+=((uint32)pData8[10])<<16;
        case 10: c+=((uint32)pData8[9])<<8;
        case 9 : c+=pData8[8];
        case 8 : b+=((uint32)pData8[7])<<24;
        case 7 : b+=((uint32)pData8[6])<<16;
        case 6 : b+=((uint32)pData8[5])<<8;
        case 5 : b+=pData8[4];
        case 4 : a+=((uint32)pData8[3])<<24;
        case 3 : a+=((uint32)pData8[2])<<16;
        case 2 : a+=((uint32)pData8[1])<<8;
        case 1 : a+=pData8[0];
                 break;
        case 0 : return c;
        }
    }

    __final(a,b,c);
    return c;
}

// ------------------------------------------------------------------
// Desc: 
// hash_little (2 seed)
// hashlittle2: return 2 32-bit hash values
//
// This is identical to hashlittle(), except it returns two 32-bit hash
// values instead of just one.  This is good enough for hash table
// lookup with 2^^64 buckets, or if you want a second hash if you're not
// happy with the first, or if you want a probably-unique 64-bit ID for
// the _pData.  *_pSeed1 is better mixed than *_pSeed2, so use *_pSeed1 first.  If you want
// a 64-bit value do something like "*_pSeed1 + (((uint64_t)*_pSeed2)<<32)".
//
//  @params:
//      _pData     : the _pData to hash
//      _len       : the length of the _pData, counting by bytes
//      _pSeed1    :    IN: seed OUT: primary hash value 
//      _pSeed2    :    IN: more seed OUT: secondary hash value 
// ------------------------------------------------------------------
void hash_little( const void* _pData, uint32 _len, uint32* _pSeed1, uint32* _pSeed2 ) 
{
    uint32 a,b,c;                                          /* internal state */
    union { const void *ptr; size_t i; } u;     /* needed for Mac Powerbook G4 */

    /* Set up the internal state */
    a = b = c = 0xdeadbeef + ((uint32)_len) + *_pSeed1;
    c += *_pSeed2;

    u.ptr = _pData;
    if (__HASH_LITTLE_ENDIAN && ((u.i & 0x3) == 0)) 
    {
        const uint32* pData32 = (const uint32 *)_pData;         /* read 32-bit chunks */

        /*------ all but last block: aligned reads and affect 32 bits of (a,b,c) */
        while (_len > 12)
        {
            a += pData32[0];
            b += pData32[1];
            c += pData32[2];
            __mix(a,b,c);
            _len -= 12;
            pData32 += 3;
        }

        /*----------------------------- handle the last (probably partial) block */
        /* 
         * "pData32[2]&0xffffff" actually reads beyond the end of the string, but
         * then masks off the part it's not allowed to read.  Because the
         * string is aligned, the masked-off tail is in the same word as the
         * rest of the string.  Every machine with memory protection I've seen
         * does it on word boundaries, so is OK with this.  But VALGRIND will
         * still catch it and complain.  The masking trick does make the hash
         * noticably faster for short strings (like English words).
         */
#ifndef VALGRIND

        switch(_len)
        {
        case 12: c+=pData32[2];             b+=pData32[1];  a+=pData32[0];  break;
        case 11: c+=pData32[2]&0xffffff;    b+=pData32[1];  a+=pData32[0];  break;
        case 10: c+=pData32[2]&0xffff;      b+=pData32[1];  a+=pData32[0];  break;
        case 9 : c+=pData32[2]&0xff;        b+=pData32[1];  a+=pData32[0];  break;
        case 8 : b+=pData32[1];             a+=pData32[0];                  break;
        case 7 : b+=pData32[1]&0xffffff;    a+=pData32[0];                  break;
        case 6 : b+=pData32[1]&0xffff;      a+=pData32[0];                  break;
        case 5 : b+=pData32[1]&0xff;        a+=pData32[0];                  break;
        case 4 : a+=pData32[0];                                             break;
        case 3 : a+=pData32[0]&0xffffff;                                    break;
        case 2 : a+=pData32[0]&0xffff;                                      break;
        case 1 : a+=pData32[0]&0xff;                                        break;
        case 0 : *_pSeed1=c; *_pSeed2=b; return;  /* zero _len strings require no mixing */
        }

#else /* make valgrind happy */

        const uint8* pData8 = (const uint8 *)pData32;
        switch(_len)
        {
        case 12: c+=pData32[2]; b+=pData32[1]; a+=pData32[0]; break;
        case 11: c+=((uint32)pData8[10])<<16;           /* fall through */
        case 10: c+=((uint32)pData8[9])<<8;             /* fall through */
        case 9 : c+=pData8[8];                          /* fall through */
        case 8 : b+=pData32[1]; a+=pData32[0]; break;
        case 7 : b+=((uint32)pData8[6])<<16;            /* fall through */
        case 6 : b+=((uint32)pData8[5])<<8;             /* fall through */
        case 5 : b+=pData8[4];                          /* fall through */
        case 4 : a+=pData32[0]; break;
        case 3 : a+=((uint32)pData8[2])<<16;            /* fall through */
        case 2 : a+=((uint32)pData8[1])<<8;             /* fall through */
        case 1 : a+=pData8[0]; break;
        case 0 : *_pSeed1=c; *_pSeed2=b; return;  /* zero _len strings require no mixing */
        }

#endif /* !valgrind */

    }
    else if (__HASH_LITTLE_ENDIAN && ((u.i & 0x1) == 0)) 
    {
        const uint16 *pData16 = (const uint16 *)_pData;         /* read 16-bit chunks */
        const uint8  *pData8;

        /*--------------- all but last block: aligned reads and different mixing */
        while (_len > 12)
        {
            a += pData16[0] + (((uint32)pData16[1])<<16);
            b += pData16[2] + (((uint32)pData16[3])<<16);
            c += pData16[4] + (((uint32)pData16[5])<<16);
            __mix(a,b,c);
            _len -= 12;
            pData16 += 6;
        }

        /*----------------------------- handle the last (probably partial) block */
        pData8 = (const uint8 *)pData16;
        switch(_len)
        {
        case 12: c+=pData16[4]+(((uint32)pData16[5])<<16);
                 b+=pData16[2]+(((uint32)pData16[3])<<16);
                 a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 11: c+=((uint32)pData8[10])<<16;               /* fall through */
        case 10: c+=pData16[4];
                 b+=pData16[2]+(((uint32)pData16[3])<<16);
                 a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 9 : c+=pData8[8];                              /* fall through */
        case 8 : b+=pData16[2]+(((uint32)pData16[3])<<16);
                 a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 7 : b+=((uint32)pData8[6])<<16;                /* fall through */
        case 6 : b+=pData16[2];
                 a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 5 : b+=pData8[4];                              /* fall through */
        case 4 : a+=pData16[0]+(((uint32)pData16[1])<<16);
                 break;
        case 3 : a+=((uint32)pData8[2])<<16;                /* fall through */
        case 2 : a+=pData16[0];
                 break;
        case 1 : a+=pData8[0];
                 break;
        case 0 : *_pSeed1=c; *_pSeed2=b; return;  /* zero _len strings require no mixing */
        }

    }
    else 
    {                        /* need to read the _pData one byte at a time */
        const uint8 *pData8 = (const uint8 *)_pData;

        /*--------------- all but the last block: affect some 32 bits of (a,b,c) */
        while (_len > 12)
        {
            a += pData8[0];
            a += ((uint32)pData8[1])<<8;
            a += ((uint32)pData8[2])<<16;
            a += ((uint32)pData8[3])<<24;
            b += pData8[4];
            b += ((uint32)pData8[5])<<8;
            b += ((uint32)pData8[6])<<16;
            b += ((uint32)pData8[7])<<24;
            c += pData8[8];
            c += ((uint32)pData8[9])<<8;
            c += ((uint32)pData8[10])<<16;
            c += ((uint32)pData8[11])<<24;
            __mix(a,b,c);
            _len -= 12;
            pData8 += 12;
        }

        /*-------------------------------- last block: affect all 32 bits of (c) */
        switch(_len)                   /* all the case statements fall through */
        {
        case 12: c+=((uint32)pData8[11])<<24;
        case 11: c+=((uint32)pData8[10])<<16;
        case 10: c+=((uint32)pData8[9])<<8;
        case 9 : c+=pData8[8];
        case 8 : b+=((uint32)pData8[7])<<24;
        case 7 : b+=((uint32)pData8[6])<<16;
        case 6 : b+=((uint32)pData8[5])<<8;
        case 5 : b+=pData8[4];
        case 4 : a+=((uint32)pData8[3])<<24;
        case 3 : a+=((uint32)pData8[2])<<16;
        case 2 : a+=((uint32)pData8[1])<<8;
        case 1 : a+=pData8[0];
                 break;
        case 0 : *_pSeed1=c; *_pSeed2=b; return;  /* zero _len strings require no mixing */
        }
    }

    __final(a,b,c);
    *_pSeed1=c; *_pSeed2=b;
}

// ------------------------------------------------------------------
// Desc: 
// hash_big
//  This is the same as hashword() on big-endian machines.  It is different
//  from hashlittle() on all machines.  hashbig() takes advantage of
//  big-endian byte ordering. 
// ------------------------------------------------------------------
uint32 hash_big( const void* _pData, uint32 _len, uint32 _seed )
{
    uint32 a,b,c;
    union { const void *ptr; size_t i; } u; /* to cast _pData to (size_t) happily */

    /* Set up the internal state */
    a = b = c = 0xdeadbeef + ((uint32)_len) + _seed;

    u.ptr = _pData;
    if (__HASH_BIG_ENDIAN && ((u.i & 0x3) == 0)) 
    {
        const uint32* pData32 = (const uint32 *)_pData;         /* read 32-bit chunks */

        /*------ all but last block: aligned reads and affect 32 bits of (a,b,c) */
        while (_len > 12)
        {
            a += pData32[0];
            b += pData32[1];
            c += pData32[2];
            __mix(a,b,c);
            _len -= 12;
            pData32 += 3;
        }

        /*----------------------------- handle the last (probably partial) block */
        /* 
         * "pData32[2]<<8" actually reads beyond the end of the string, but
         * then shifts out the part it's not allowed to read.  Because the
         * string is aligned, the illegal read is in the same word as the
         * rest of the string.  Every machine with memory protection I've seen
         * does it on word boundaries, so is OK with this.  But VALGRIND will
         * still catch it and complain.  The masking trick does make the hash
         * noticably faster for short strings (like English words).
         */
#ifndef VALGRIND

        switch(_len)
        {
        case 12: c+=pData32[2]; b+=pData32[1]; a+=pData32[0]; break;
        case 11: c+=pData32[2]&0xffffff00; b+=pData32[1]; a+=pData32[0]; break;
        case 10: c+=pData32[2]&0xffff0000; b+=pData32[1]; a+=pData32[0]; break;
        case 9 : c+=pData32[2]&0xff000000; b+=pData32[1]; a+=pData32[0]; break;
        case 8 : b+=pData32[1]; a+=pData32[0]; break;
        case 7 : b+=pData32[1]&0xffffff00; a+=pData32[0]; break;
        case 6 : b+=pData32[1]&0xffff0000; a+=pData32[0]; break;
        case 5 : b+=pData32[1]&0xff000000; a+=pData32[0]; break;
        case 4 : a+=pData32[0]; break;
        case 3 : a+=pData32[0]&0xffffff00; break;
        case 2 : a+=pData32[0]&0xffff0000; break;
        case 1 : a+=pData32[0]&0xff000000; break;
        case 0 : return c;              /* zero _len strings require no mixing */
        }

#else  /* make valgrind happy */

        const uint8* pData8 = (const uint8 *)pData32;
        switch(_len)                   /* all the case statements fall through */
        {
        case 12: c+=pData32[2]; b+=pData32[1]; a+=pData32[0]; break;
        case 11: c+=((uint32)pData8[10])<<8;  /* fall through */
        case 10: c+=((uint32)pData8[9])<<16;  /* fall through */
        case 9 : c+=((uint32)pData8[8])<<24;  /* fall through */
        case 8 : b+=pData32[1]; a+=pData32[0]; break;
        case 7 : b+=((uint32)pData8[6])<<8;   /* fall through */
        case 6 : b+=((uint32)pData8[5])<<16;  /* fall through */
        case 5 : b+=((uint32)pData8[4])<<24;  /* fall through */
        case 4 : a+=pData32[0]; break;
        case 3 : a+=((uint32)pData8[2])<<8;   /* fall through */
        case 2 : a+=((uint32)pData8[1])<<16;  /* fall through */
        case 1 : a+=((uint32)pData8[0])<<24; break;
        case 0 : return c;
        }

#endif /* !VALGRIND */

    } 
    else 
    {                        /* need to read the _pData one byte at a time */
        const uint8 *pData8 = (const uint8 *)_pData;

        /*--------------- all but the last block: affect some 32 bits of (a,b,c) */
        while (_len > 12)
        {
            a += ((uint32)pData8[0])<<24;
            a += ((uint32)pData8[1])<<16;
            a += ((uint32)pData8[2])<<8;
            a += ((uint32)pData8[3]);
            b += ((uint32)pData8[4])<<24;
            b += ((uint32)pData8[5])<<16;
            b += ((uint32)pData8[6])<<8;
            b += ((uint32)pData8[7]);
            c += ((uint32)pData8[8])<<24;
            c += ((uint32)pData8[9])<<16;
            c += ((uint32)pData8[10])<<8;
            c += ((uint32)pData8[11]);
            __mix(a,b,c);
            _len -= 12;
            pData8 += 12;
        }

        /*-------------------------------- last block: affect all 32 bits of (c) */
        switch(_len)                   /* all the case statements fall through */
        {
        case 12: c+=pData8[11];
        case 11: c+=((uint32)pData8[10])<<8;
        case 10: c+=((uint32)pData8[9])<<16;
        case 9 : c+=((uint32)pData8[8])<<24;
        case 8 : b+=pData8[7];
        case 7 : b+=((uint32)pData8[6])<<8;
        case 6 : b+=((uint32)pData8[5])<<16;
        case 5 : b+=((uint32)pData8[4])<<24;
        case 4 : a+=pData8[3];
        case 3 : a+=((uint32)pData8[2])<<8;
        case 2 : a+=((uint32)pData8[1])<<16;
        case 1 : a+=((uint32)pData8[0])<<24;
                 break;
        case 0 : return c;
        }
    }

    __final(a,b,c);
    return c;
}

// ------------------------------------------------------------------
// Desc: 
// hash_big
//  This is identical to hashbig(), except it returns two 32-bit hash
//  values instead of just one.  This is good enough for hash table
//  lookup with 2^^64 buckets, or if you want a second hash if you're not
//  happy with the first, or if you want a probably-unique 64-bit ID for
//  the _pData.  *_pSeed1 is better mixed than *_pSeed2, so use *_pSeed1 first.  If you want
//  a 64-bit value do something like "*_pSeed1 + (((uint64_t)*_pSeed2)<<32)".
//
//   @params:
//       _pData     : the _pData to hash
//       _len       : the length of the _pData, counting by bytes
//       _pSeed1    :    IN: seed OUT: primary hash value 
//       _pSeed2    :    IN: more seed OUT: secondary hash value 
// ------------------------------------------------------------------
void hash_big( const void* _pData, uint32 _len, uint32* _pSeed1, uint32* _pSeed2 )
{
    uint32 a,b,c;
    union { const void *ptr; size_t i; } u; /* to cast _pData to (size_t) happily */

    /* Set up the internal state */
    a = b = c = 0xdeadbeef + ((uint32)_len) + *_pSeed1;
    c += *_pSeed2;

    u.ptr = _pData;
    if (__HASH_BIG_ENDIAN && ((u.i & 0x3) == 0)) 
    {
        const uint32* pData32 = (const uint32 *)_pData;         /* read 32-bit chunks */

        /*------ all but last block: aligned reads and affect 32 bits of (a,b,c) */
        while (_len > 12)
        {
            a += pData32[0];
            b += pData32[1];
            c += pData32[2];
            __mix(a,b,c);
            _len -= 12;
            pData32 += 3;
        }

        /*----------------------------- handle the last (probably partial) block */
        /* 
         * "pData32[2]<<8" actually reads beyond the end of the string, but
         * then shifts out the part it's not allowed to read.  Because the
         * string is aligned, the illegal read is in the same word as the
         * rest of the string.  Every machine with memory protection I've seen
         * does it on word boundaries, so is OK with this.  But VALGRIND will
         * still catch it and complain.  The masking trick does make the hash
         * noticably faster for short strings (like English words).
         */
#ifndef VALGRIND

        switch(_len)
        {
        case 12: c+=pData32[2]; b+=pData32[1]; a+=pData32[0]; break;
        case 11: c+=pData32[2]&0xffffff00; b+=pData32[1]; a+=pData32[0]; break;
        case 10: c+=pData32[2]&0xffff0000; b+=pData32[1]; a+=pData32[0]; break;
        case 9 : c+=pData32[2]&0xff000000; b+=pData32[1]; a+=pData32[0]; break;
        case 8 : b+=pData32[1]; a+=pData32[0]; break;
        case 7 : b+=pData32[1]&0xffffff00; a+=pData32[0]; break;
        case 6 : b+=pData32[1]&0xffff0000; a+=pData32[0]; break;
        case 5 : b+=pData32[1]&0xff000000; a+=pData32[0]; break;
        case 4 : a+=pData32[0]; break;
        case 3 : a+=pData32[0]&0xffffff00; break;
        case 2 : a+=pData32[0]&0xffff0000; break;
        case 1 : a+=pData32[0]&0xff000000; break;
        case 0 : *_pSeed1=c; *_pSeed2=b; return;  /* zero length strings require no mixing */
        }

#else  /* make valgrind happy */

        const uint8* pData8 = (const uint8 *)pData32;
        switch(_len)                   /* all the case statements fall through */
        {
        case 12: c+=pData32[2]; b+=pData32[1]; a+=pData32[0]; break;
        case 11: c+=((uint32)pData8[10])<<8;  /* fall through */
        case 10: c+=((uint32)pData8[9])<<16;  /* fall through */
        case 9 : c+=((uint32)pData8[8])<<24;  /* fall through */
        case 8 : b+=pData32[1]; a+=pData32[0]; break;
        case 7 : b+=((uint32)pData8[6])<<8;   /* fall through */
        case 6 : b+=((uint32)pData8[5])<<16;  /* fall through */
        case 5 : b+=((uint32)pData8[4])<<24;  /* fall through */
        case 4 : a+=pData32[0]; break;
        case 3 : a+=((uint32)pData8[2])<<8;   /* fall through */
        case 2 : a+=((uint32)pData8[1])<<16;  /* fall through */
        case 1 : a+=((uint32)pData8[0])<<24; break;
        case 0 : *_pSeed1=c; *_pSeed2=b; return;  /* zero length strings require no mixing */
        }

#endif /* !VALGRIND */

    } 
    else 
    {                        /* need to read the _pData one byte at a time */
        const uint8 *pData8 = (const uint8 *)_pData;

        /*--------------- all but the last block: affect some 32 bits of (a,b,c) */
        while (_len > 12)
        {
            a += ((uint32)pData8[0])<<24;
            a += ((uint32)pData8[1])<<16;
            a += ((uint32)pData8[2])<<8;
            a += ((uint32)pData8[3]);
            b += ((uint32)pData8[4])<<24;
            b += ((uint32)pData8[5])<<16;
            b += ((uint32)pData8[6])<<8;
            b += ((uint32)pData8[7]);
            c += ((uint32)pData8[8])<<24;
            c += ((uint32)pData8[9])<<16;
            c += ((uint32)pData8[10])<<8;
            c += ((uint32)pData8[11]);
            __mix(a,b,c);
            _len -= 12;
            pData8 += 12;
        }

        /*-------------------------------- last block: affect all 32 bits of (c) */
        switch(_len)                   /* all the case statements fall through */
        {
        case 12: c+=pData8[11];
        case 11: c+=((uint32)pData8[10])<<8;
        case 10: c+=((uint32)pData8[9])<<16;
        case 9 : c+=((uint32)pData8[8])<<24;
        case 8 : b+=pData8[7];
        case 7 : b+=((uint32)pData8[6])<<8;
        case 6 : b+=((uint32)pData8[5])<<16;
        case 5 : b+=((uint32)pData8[4])<<24;
        case 4 : a+=pData8[3];
        case 3 : a+=((uint32)pData8[2])<<8;
        case 2 : a+=((uint32)pData8[1])<<16;
        case 1 : a+=((uint32)pData8[0])<<24;
                 break;
        case 0 : *_pSeed1=c; *_pSeed2=b; return;  /* zero length strings require no mixing */
        }
    }

    __final(a,b,c);
    *_pSeed1=c; *_pSeed2=b;
}

///////////////////////////////////////////////////////////////////////////////
//  Paul Hsieh's Hash
//      http://www.azillionmonkeys.com/qed/hash.html
///////////////////////////////////////////////////////////////////////////////

#ifdef __get_uint16
#undef __get_uint16
#endif

#define __get_uint16(d) (*((const uint16 *) (d)))

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------
uint32 hash_paul( const uint8* _pData, uint32 _len )
{
    uint32 hash = _len, tmp;
    int32 rem;

    if (_len <= 0 || _pData == NULL) return 0;

    rem = _len & 3;
    _len >>= 2;

    /* Main loop */
    for ( ; _len > 0; --_len ) 
    {
        hash    += __get_uint16(_pData);
        tmp      = (__get_uint16(_pData+2) << 11) ^ hash;
        hash     = (hash << 16) ^ tmp;
        _pData  += 2*sizeof(uint16);
        hash    += hash >> 11;
    }

    /* Handle end cases */
    switch (rem)
    {
    case 3: hash += __get_uint16(_pData);
            hash ^= hash << 16;
            hash ^= _pData[sizeof(uint16)] << 18;
            hash += hash >> 11;
            break;
    case 2: hash += __get_uint16(_pData);
            hash ^= hash << 11;
            hash += hash >> 17;
            break;
    case 1: hash += *_pData;
            hash ^= hash << 10;
            hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}


///////////////////////////////////////////////////////////////////////////////
//  Undef block. 
//   undefine all the temp macros
///////////////////////////////////////////////////////////////////////////////

#undef __mix
#undef __rot
#undef __final
#undef __get_uint16

// #########################
} // end namespace ex
// #########################
