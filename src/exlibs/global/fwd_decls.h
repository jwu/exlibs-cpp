// ======================================================================================
// File         : fwd_decls.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:15:02 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FWDDECLS_H_1250525527
#define FWDDECLS_H_1250525527
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// fwd-decl global functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// mathop
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace mathop { 
// ######################### 

// ======================================================== 
// float op
// ======================================================== 

float floor ( float _value );
double floor ( double _value );

float ceil ( float _value );
double ceil ( double _value );

float round ( float _value );
double round ( double _value );

float trunc ( float _value );
double trunc ( double _value );

float round_away ( float _value );
double round_away ( double _value );

float log( float _value );
double log( double _value );

float log2 ( float _value );
double log2 ( double _value );

float sin( float _radian );
double sin( double _radian );

float asin( float _value );
double asin( double _value );

float cos( float _radian );
double cos( double _radian );

float acos( float _value );
double acos( double _value );

float tan( float _radian );
double tan( double _radian );

float atan( float _value );
double atan( double _value );

float atan2( float _y, float _x );
double atan2( double _y, double _x );

float fmod ( float _x, float _y );
double fmod ( double _x, double _y );

uint32 ceilpow2 ( uint32 _value );
uint32 ceilpow2_f ( float _value );
uint32 ceilpow2_f ( double _value );

uint32 floorpow2 ( uint32 _value );
uint32 floorpow2_f ( float _value );
uint32 floorpow2_f ( double _value );

// ======================================================== 
// int op 
// ======================================================== 

uint32 pow2 ( uint32 _count );

// ======================================================== 
// generic
// ======================================================== 

template <typename T> T sqrt( T _value );

template < typename T, int COUNT > bool is_equal( bool* _pResult, const T (&_pData1)[COUNT], const T (&_pData2)[COUNT] );
bool is_equal( const vec_f32_t _data1, const vec_f32_t _data2, float _epsilon );

template< typename T > bool is_zero( T _value, T _eps );
bool is_zero( const vec_f32_t _data, float _epsilon );

template <typename T> T clamp( T _value, T _min, T _max );
template < typename T, int COUNT > void clamp( T (&_pResult)[COUNT], const T (&_pData)[COUNT], const T (&_pMin)[COUNT], const T (&_pMax)[COUNT] );
void clamp( vec_f32_t& _result, const vec_f32_t _data, const vec_f32_t _min, const vec_f32_t _max );

template < typename T, int COUNT > void abs( T (&_pResult)[COUNT], const T (&_pData)[COUNT] );
void abs( vec_f32_t& _result, const vec_f32_t _data );

template < typename T > const T& max( const T& _a, const T& _b );
template < typename T > const T& min( const T& _a, const T& _b );

// ######################### 
} // end namespace mathop 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// forward class decls
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// functor
// ========================================================

#if 0
template < typename T > class TColor;
template < typename ARG_TYPE, typename RESULT_TYPE > struct Unary;
template < typename ARG_TYPE1, typename ARG_TYPE2, typename RESULT_TYPE > struct Binary;
template < typename T > struct TGet_Hash;
template < typename T > struct TCompare_LessThan;
template < typename T > struct TCompare_Equal;
#endif

// ========================================================
// math
// ========================================================

template < typename T, uint COUNT > struct TComponentType;
template < typename T, uint COUNT > class Vector;
template < typename T > class Vector2;
template < typename T > class Vector3;
template < typename T > class Vector4;
template < typename T > class Matrix2;
template < typename T > class Matrix3;
template < typename T > class Matrix4;
template < typename T > class Quaternion;
template < typename T > class Angle;
template < typename T > class Rotator;

class Color3u;
class Color4u;
class Color3f;
class Color4f;

template < typename T > class Line2D;
template < typename T > class Rect;
template < typename T > class AABRect;
template < typename T > class OBRect;

// ========================================================
// container
// ========================================================

// template < typename T, int32 SIZE = 256 > class Stack;

//
template < typename T, template < class > class TAllocator_T > class ContainerAllocator;

//
template < typename T > class StringID;
template < typename T, template <class> class TAllocator_T > class String;
    template < typename T, template <class> class TAllocator_T > class Path;
        template < typename T, template <class> class TAllocator_T > class ResPath;

//
template < typename T1, typename T2 > struct Pair;
template < typename T, template < class > class TAllocator_T > class Array;
template < template < class > class TAllocator_T > class BitArray;
template < typename T, template < class > class TAllocator_T > class Pool;
template < typename T, template < class > class TAllocator_T > class Deque;
template < typename T, template < class > class TAllocator_T > class Queue;
template < typename T, template < class > class TAllocator_T > class Stack;
template < typename T, template < class > class TAllocator_T > class List;

//

//
template < typename KEY, typename VALUE, typename COMP_FUNC, template < class > class TAllocator_T > class Map;
template < typename KEY, typename VALUE, typename COMP_FUNC, template < class > class TAllocator_T > class MultiMap;

//
template < typename KEY, typename COMP_FUNC, template < class > class TAllocator_T > class set;
template < typename KEY, typename COMP_FUNC, template < class > class TAllocator_T > class MultiSet;

//
template < typename KEY, 
           typename VALUE,
           typename HASH_FUNC, 
           typename EQUAL_KEY, 
           template < class > class TAllocator_T > class HashMap;
template < typename KEY, 
           typename VALUE, 
           typename HASH_FUNC, 
           typename EQUAL_KEY, 
           template < class > class TAllocator_T > class HashMultiMap;

//
template < typename VALUE, 
           typename HASH_FUNC, 
           typename EQUAL_KEY,
           template < class > class TAllocator_T > class HashSet;
template < typename VALUE,
           typename HASH_FUNC, 
           typename EQUAL_KEY,
           template < class > class TAllocator_T > class HashMultiSet;

// ========================================================
// helper
// ========================================================

template < typename CAllocator_T > struct NoManaged;
template < typename CAllocator_T > struct Managed;

// ========================================================
// pattern
// ========================================================

// TODO:
#if 0
template < typename T, 
           uint LEVEL = 0xFFFFFFFF, 
           template <class> class Allocator_T = Managed::Allocator,
           template <class, class> class ThreadingModel_T = TDefaultThread,
           class MutexPolicy_T = TDefaultMutex >
#endif
template < typename T, 
           uint LEVEL,
           template <class> class TAllocator_T > class SingletonHolder;

// ======================================================== 
// proerpty 
// ======================================================== 

template < typename CLASS_T, typename MEMBER_T > class MemberProperty;
template < class CLASS_T > class PropertyInstance; // NOTE: if we don't do this, gcc will not know the friend class declaration in each generic classes

///////////////////////////////////////////////////////////////////////////////
// struct/class declarations 
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// memory
// ========================================================

class Memop;
// class MemMng; // use singleton
class Allocator;
    // class Allocator_sys; // use singleton
    // class Allocator_dl283; // use singleton

// ========================================================
// file
// ========================================================

class IFile;
    class PhysicalFile;

// ======================================================== 
// serialization
// ======================================================== 

class ISerializeNode;
    class XmlSerializeNode;

// ========================================================
// xml
// ========================================================

class XmlParser;

// ========================================================
// paraser
// ========================================================

class ConfigParser;

// ======================================================== 
// property 
// ======================================================== 

class PropertyBase;

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END FWDDECLS_H_1250525527
// #################################################################################
