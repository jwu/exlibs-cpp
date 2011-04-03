// ======================================================================================
// File         : functors.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 11:32:33 AM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FUNCTORS_H_1281756754
#define FUNCTORS_H_1281756754
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "gf/hash.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// functors 
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// class Unary 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename ARG_T, typename RESULT_T>
struct Unary
{
    typedef ARG_T       argument_t;
    typedef RESULT_T    result_t;
};

///////////////////////////////////////////////////////////////////////////////
// class Binary 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename ARG_T1, typename ARG_T2, typename RESULT_T>
struct Binary
{
    typedef ARG_T1      first_argument_t;
    typedef ARG_T2      second_argument_t;
    typedef RESULT_T    result_t;
};      

///////////////////////////////////////////////////////////////////////////////
// class Plus 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Plus : public Binary<T,T,T> 
{
    T operator()(const T& _x, const T& _y) const { return _x + _y; }
};

///////////////////////////////////////////////////////////////////////////////
// class Minus 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Minus : public Binary<T,T,T> 
{
    T operator()(const T& _x, const T& _y) const { return _x - _y; }
};

///////////////////////////////////////////////////////////////////////////////
// class Multiplies 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Multiplies : public Binary<T,T,T>
{
    T operator()(const T& _x, const T& _y) const { return _x * _y; }
};

///////////////////////////////////////////////////////////////////////////////
// class Divides 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Divides : public Binary<T,T,T>
{
    T operator()(const T& _x, const T& _y) const { return _x / _y; }
};

//
template <typename T> inline T T_IdentityElement( Plus<T> ) { return T(0); }
template <typename T> inline T T_IdentityElement( Multiplies<T> ) { return T(1); }

///////////////////////////////////////////////////////////////////////////////
// class Modulus 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Modulus : public Binary<T,T,T> 
{
    T operator()(const T& _x, const T& _y) const { return _x % _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class Negate
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Negate : public Unary<T,T> 
{
    T operator()(const T& _x) const { return -_x; }
};


///////////////////////////////////////////////////////////////////////////////
// class EqualTo 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct EqualTo : public Binary<T,T,bool> 
{
    bool operator()(const T& _x, const T& _y) const { return _x == _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class NotEqualTo 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct NotEqualTo : public Binary<T,T,bool> 
{
    bool operator()(const T& _x, const T& _y) const { return _x != _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class Greater 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Greater : public Binary<T,T,bool> 
{
    bool operator()(const T& _x, const T& _y) const { return _x > _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class Less 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Less : public Binary<T,T,bool> 
{
    bool operator()(const T& _x, const T& _y) const { return _x < _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class GreaterEqual 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct GreaterEqual : public Binary<T,T,bool>
{
    bool operator()(const T& _x, const T& _y) const { return _x >= _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class LessEqual 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct LessEqual : public Binary<T,T,bool> 
{
    bool operator()(const T& _x, const T& _y) const { return _x <= _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class LogicalAnd 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct LogicalAnd : public Binary<T,T,bool>
{
    bool operator()(const T& _x, const T& _y) const { return _x && _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class LogicalOr 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct LogicalOr : public Binary<T,T,bool>
{
    bool operator()(const T& _x, const T& _y) const { return _x || _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class LogicalNot 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct LogicalNot : public Unary<T,bool>
{
    bool operator()(const T& _x) const { return !_x; }
};


///////////////////////////////////////////////////////////////////////////////
// class UnaryNegate 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename PREDICATE_T>
class UnaryNegate : public Unary<typename PREDICATE_T::argument_t, bool> 
{
protected:
    PREDICATE_T m_pred;

public:
    explicit UnaryNegate(const PREDICATE_T& _x) : m_pred(_x) {}
    bool operator()(const typename PREDICATE_T::argument_t& _x) const { return !m_pred(_x); }
};

// ------------------------------------------------------------------
// Desc: T_Not1
// ------------------------------------------------------------------
template <typename PREDICATE_T> 
INLINE UnaryNegate<PREDICATE_T> T_Not1(const PREDICATE_T& _pred) { return UnaryNegate<PREDICATE_T>(_pred); }


///////////////////////////////////////////////////////////////////////////////
// class BinaryNegate 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename PREDICATE_T> 
class BinaryNegate : public Binary<typename PREDICATE_T::first_argument_t, typename PREDICATE_T::second_argument_t, bool> 
{
protected:
    PREDICATE_T m_pred;

public:
    explicit BinaryNegate(const PREDICATE_T& _x) : m_pred(_x) {}
    bool operator()(const typename PREDICATE_T::first_argument_t& _x, 
                    const typename PREDICATE_T::second_argument_t& _y) const
    {
        return !m_pred(_x, _y); 
    }
};

// ------------------------------------------------------------------
// Desc: T_Not2
// ------------------------------------------------------------------
template <typename PREDICATE_T> 
INLINE BinaryNegate<PREDICATE_T> T_Not2(const PREDICATE_T& _pred) { return BinaryNegate<PREDICATE_T>(_pred); }

///////////////////////////////////////////////////////////////////////////////
// class Binder1st 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename OPERATION_T> 
class Binder1st : public Unary<typename OPERATION_T::second_argument_t, typename OPERATION_T::result_t> 
{
protected:
    OPERATION_T op;
    typename OPERATION_T::first_argument_t value;

public:
    Binder1st( const OPERATION_T& _x, const typename OPERATION_T::first_argument_t& _y )
        : op(_x), value(_y) 
    {
    }

    typename OPERATION_T::result_t operator()(const typename OPERATION_T::second_argument_t& _x) const { return op(value, _x); }
};

// ------------------------------------------------------------------
// Desc: T_Bind1st 
// ------------------------------------------------------------------
template <typename OPERATION_T, typename T> 
INLINE Binder1st<OPERATION_T> T_Bind1st(const OPERATION_T& _fn, const T& _x) 
{
    typedef typename OPERATION_T::first_argument_t ARG_T1_t;
    return std::binder1st<OPERATION_T>(_fn, ARG_T1_t(_x));
}


///////////////////////////////////////////////////////////////////////////////
// class Binder2nd 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename OPERATION_T> 
class Binder2nd : public Unary<typename OPERATION_T::first_argument_t, typename OPERATION_T::result_t> 
{
protected:
    OPERATION_T op;
    typename OPERATION_T::second_argument_t value;

public:
    Binder2nd( const OPERATION_T& _x, const typename OPERATION_T::second_argument_t& _y ) 
        : op(_x), value(_y) 
    {
    }

    typename OPERATION_T::result_t operator()(const typename OPERATION_T::first_argument_t& _x) const { return op(_x, value); }
};

// ------------------------------------------------------------------
// Desc: T_Bind2nd
// ------------------------------------------------------------------

template <typename OPERATION_T, typename T> 
INLINE Binder2nd<OPERATION_T> T_Bind2nd(const OPERATION_T& _fn, const T& _x) 
{
    typedef typename OPERATION_T::second_argument_t ARG_T2_t;
    return std::binder2nd<OPERATION_T>(_fn, ARG_T2_t(_x));
}

///////////////////////////////////////////////////////////////////////////////
// class UnaryCompose 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename OPERATION_T1, typename OPERATION_T2>
class UnaryCompose : public Unary<typename OPERATION_T2::argument_t, typename OPERATION_T1::result_t> 
{
protected:
    OPERATION_T1 m_fn1;
    OPERATION_T2 m_fn2;

public:
    UnaryCompose(const OPERATION_T1& _x, const OPERATION_T2& _y) 
        : m_fn1(_x), m_fn2(_y)
    {
    }

    typename OPERATION_T1::result_t operator()(const typename OPERATION_T2::argument_t& _x) const { return m_fn1(m_fn2(_x)); }
};

// ------------------------------------------------------------------
// Desc: T_Compose1
// ------------------------------------------------------------------

template <typename OPERATION_T1, typename OPERATION_T2> 
INLINE UnaryCompose<OPERATION_T1,OPERATION_T2> T_Compose1(const OPERATION_T1& _fn1, const OPERATION_T2& _fn2)
{
    return UnaryCompose<OPERATION_T1,OPERATION_T2>(_fn1, _fn2);
}


///////////////////////////////////////////////////////////////////////////////
// class BinaryCompose 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename OPERATION_T1, typename OPERATION_T2, typename OPERATION_T3> 
class BinaryCompose : public Unary<typename OPERATION_T2::argument_t, typename OPERATION_T1::result_t>
{
protected:
    OPERATION_T1 m_fn1;
    OPERATION_T2 m_fn2;
    OPERATION_T3 m_fn3;

public:
    BinaryCompose(const OPERATION_T1& _x, const OPERATION_T2& _y, const OPERATION_T3& _z) 
        : m_fn1(_x), m_fn2(_y), m_fn3(_z) 
    {
    }

    typename OPERATION_T1::result_t operator()(const typename OPERATION_T2::argument_t& _x) const { return m_fn1(m_fn2(_x), m_fn3(_x)); }
};

// ------------------------------------------------------------------
// Desc: T_Compose2
// ------------------------------------------------------------------

// TODO: check why compile failed in gcc
#if 0
template <typename OPERATION_T1, typename OPERATION_T2, typename OPERATION_T3>
INLINE BinaryCompose<OPERATION_T1, OPERATION_T2, OPERATION_T3> T_Compose2(const OPERATION_T1& _fn1, const OPERATION_T2& _fn2, const OPERATION_T3& _fn3)
{
#if ( EX_COMPILER == EX_MSVC )
    return std::binary_compose<OPERATION_T1,OPERATION_T2,OPERATION_T3> (_fn1, _fn2, _fn3);
#else
    return __gnu_cxx::binary_compose<OPERATION_T1,OPERATION_T2,OPERATION_T3> (_fn1, _fn2, _fn3);
#endif
}
#endif

///////////////////////////////////////////////////////////////////////////////
// class Identity 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Identity : public Unary<T,T>
{
    const T& operator()(const T& _x) const { return _x; }
};

///////////////////////////////////////////////////////////////////////////////
// class Select_1st 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename PAIR_T>
struct Select_1st : public Unary<PAIR_T, typename PAIR_T::first_t> 
{
    const typename PAIR_T::first_t& operator()(const PAIR_T& _x) const { return _x.first; }
};

///////////////////////////////////////////////////////////////////////////////
// class Select_2nd 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename PAIR_T>
struct Select_2nd : public Unary<PAIR_T, typename PAIR_T::second_t>
{
    const typename PAIR_T::second_t& operator()(const PAIR_T& _x) const { return _x.second; }
};

///////////////////////////////////////////////////////////////////////////////
// class Project_1st 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename ARG_T1, typename ARG_T2>
struct Project_1st : public Binary<ARG_T1, ARG_T2, ARG_T1> 
{
    ARG_T1 operator()(const ARG_T1& _x, const ARG_T2&) const { return _x; }
};


///////////////////////////////////////////////////////////////////////////////
// class Project_2nd 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename ARG_T1, typename ARG_T2>
struct Project_2nd : public Binary<ARG_T1, ARG_T2, ARG_T2> 
{
    ARG_T2 operator()(const ARG_T1&, const ARG_T2& _y) const { return _y; }
};


///////////////////////////////////////////////////////////////////////////////
// class ConstantVoidFunctor 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename RESULT_T>
struct ConstantVoidFunctor 
{
    typedef RESULT_T result_t;
    result_t m_val;

    ConstantVoidFunctor(const result_t& _v) : m_val(_v) {}
    const result_t& operator()() const { return m_val; }
};  

// ------------------------------------------------------------------
// Desc: T_Constant0
// ------------------------------------------------------------------
template <typename RESULT_T>
INLINE ConstantVoidFunctor<RESULT_T> T_Constant0(const RESULT_T& _val) { return ConstantVoidFunctor<RESULT_T>(_val); }

///////////////////////////////////////////////////////////////////////////////
// class ConstantUnaryFunctor 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename RESULT_T, typename ARG_T>
struct ConstantUnaryFunctor 
{
    typedef ARG_T argument_t;
    typedef  RESULT_T  result_t;
    result_t m_val;

    ConstantUnaryFunctor(const result_t& _v) : m_val(_v) {}
    const result_t& operator()(const ARG_T&) const { return m_val; }
};

//
template <typename RESULT_T>
INLINE ConstantUnaryFunctor<RESULT_T,RESULT_T> T_Constant1(const RESULT_T& _val) { return ConstantUnaryFunctor<RESULT_T,RESULT_T>(_val); }

///////////////////////////////////////////////////////////////////////////////
// class ConstantBinaryFunctor 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <typename RESULT_T, typename ARG_T1, typename ARG_T2>
struct ConstantBinaryFunctor 
{
    typedef  ARG_T1   first_argument_t;
    typedef  ARG_T2   second_argument_t;
    typedef  RESULT_T result_t;
    RESULT_T m_val;

    ConstantBinaryFunctor(const RESULT_T& _v) : m_val(_v) {}
    const result_t& operator()(const ARG_T1&, const ARG_T2&) const { return m_val; }
};

// ------------------------------------------------------------------
// Desc: T_Constant2
// ------------------------------------------------------------------
template <typename RESULT_T>
INLINE ConstantBinaryFunctor<RESULT_T,RESULT_T,RESULT_T> T_Constant2(const RESULT_T& _val) { return ConstantBinaryFunctor<RESULT_T,RESULT_T,RESULT_T>(_val); }


///////////////////////////////////////////////////////////////////////////////
// class SubtractiveRng 
// 
// Purpose: Note: this code assumes that int is 32 bits.
// 
///////////////////////////////////////////////////////////////////////////////

class SubtractiveRng : public Unary<uint, uint> 
{
private:
    uint m_table[55];
    size_t m_index1;
    size_t m_index2;

public:
    uint operator()(uint _limit) 
    {
        m_index1 = (m_index1 + 1) % 55;
        m_index2 = (m_index2 + 1) % 55;
        m_table[m_index1] = m_table[m_index1] - m_table[m_index2];
        return m_table[m_index1] % _limit;
    }

    void _M_initialize(uint _seed)
    {
        uint _k = 1;
        m_table[54] = _seed;
        size_t _i;
        for (_i = 0; _i < 54; _i++) 
        {
            size_t _ii = (21 * (_i + 1) % 55) - 1;
            m_table[_ii] = _k;
            _k = _seed - _k;
            _seed = m_table[_ii];
        }
        for (int _loop = 0; _loop < 4; _loop++) 
        {
            for (_i = 0; _i < 55; _i++)
                m_table[_i] = m_table[_i] - m_table[(1 + _i + 30) % 55];
        }
        m_index1 = 0;
        m_index2 = 31;
    }

    SubtractiveRng(uint _seed) { _M_initialize(_seed); }
    SubtractiveRng() { _M_initialize(161803398u); }
};

///////////////////////////////////////////////////////////////////////////////
// class Hash 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// general 
// ========================================================

template < typename T >
struct Hash : public Unary<T, uint32>
{
    INLINE uint operator () ( const T& _value ) const { return (uint32)_value; }
}; // end struct Hash<T>

// ========================================================
// void* 
// ========================================================

template < typename T >
struct Hash<T*>
{
    INLINE uint operator () ( const T* _value ) const { return (uint32)((size_t)_value >> 4); }
}; // end struct TShash<void*>


// ========================================================
// char*
// ========================================================

template <>
struct Hash<char*> 
{
    INLINE uint operator () ( const char*& _value ) const { return (uint32)hash_str( _value ); }
}; // end struct Hash<char*>

// ========================================================
// const char*
// ========================================================

template <>
struct Hash<const char*> 
{
    INLINE uint operator () ( const char* const & _value ) const { return (uint32)hash_str( _value ); }
}; // end struct Hash<const char*>

// ========================================================
// wchar*
// ========================================================

template <>
struct Hash<wchar*> 
{
    INLINE uint operator () ( const wchar*& _value ) const { return (uint32)hash_str( _value ); }
}; // end struct Hash<wchar*>

// ========================================================
// const wchar*
// ========================================================

template <>
struct Hash<const wchar*> 
{
    INLINE uint operator () ( const wchar* const & _value ) const { return (uint32)hash_str( _value ); }
}; // end struct Hash<const wchar*>

// ========================================================
// string_t
// ========================================================

template <>
struct Hash<string_t> 
{
    INLINE uint operator () ( const string_t & _value ) const { return (uint32)hash_str( _value.c_str() ); }
}; // end struct Hash<string_t>

// ========================================================
// string_t
// ========================================================

template <>
struct Hash<wstring_t> 
{
    INLINE uint operator () ( const wstring_t & _value ) const { return (uint32)hash_str( _value.c_str() ); }
}; // end struct Hash<wstring_t>

#if 0

// ==================================================================
//
template <typename ARG_T, typename RESULT_T>
class TPointerToUnaryFunctor : public Unary<ARG_T, RESULT_T> 
{
protected:
    RESULT_T (*m_ptr)(ARG_T);

public:
    TPointerToUnaryFunctor() {}
    explicit TPointerToUnaryFunctor(RESULT_T (*_x)(ARG_T)) : m_ptr(_x) {}
    RESULT_T operator()(ARG_T _x) const { return m_ptr(_x); }
};

//
template <typename ARG_T, typename RESULT_T>
INLINE TPointerToUnaryFunctor<ARG_T, RESULT_T> T_FuncPtr(RESULT_T (*_x)(ARG_T))
{
    return TPointerToUnaryFunctor<ARG_T, RESULT_T>(_x);
}


// ==================================================================
//
template <typename ARG_T1, typename ARG_T2, typename RESULT_T>
class TPointerToBinaryFunctor : public Binary<ARG_T1,ARG_T2,RESULT_T> 
{
protected:
    RESULT_T (*m_ptr)(ARG_T1, ARG_T2);

public:
    TPointerToBinaryFunctor() {}
    explicit TPointerToBinaryFunctor(RESULT_T (*_x)(ARG_T1, ARG_T2)) : m_ptr(_x) {} 
    RESULT_T operator()(ARG_T1 _x, ARG_T2 _y) const { return m_ptr(_x, _y); }
};

//
template <typename ARG_T1, typename ARG_T2, typename RESULT_T>
INLINE TPointerToBinaryFunctor<ARG_T1,ARG_T2,RESULT_T> T_FuncPtr(RESULT_T (*_x)(ARG_T1, ARG_T2)) 
{
    return TPointerToBinaryFunctor<ARG_T1,ARG_T2,RESULT_T>(_x);
}


// ==================================================================
//
// Adaptor function objects: pointers to member functions.

// There are a total of 16 = 2^4 function objects in this family.
//  (1) Member functions taking no arguments vs member functions taking
//       one argument.
//  (2) Call through pointer vs call through reference.
//  (3) Member function with void return type vs member function with
//      non-void return type.
//  (4) Const vs non-const member function.

// Note that choice (3) is nothing more than a workaround: according
//  to the draft, compilers should handle void and non-void the same way.
//  This feature is not yet widely implemented, though.  You can only use
//  member functions returning void if your compiler supports partial
//  specialization.

// All of this complexity is in the function objects themselves.  You can
//  ignore it by using the helper function mem_fun and mem_fun_ref,
//  which create whichever type of adaptor is appropriate.
//  (mem_fun1 and mem_fun1_ref are no longer part of the C++ standard,
//  but they are provided for backward compatibility.)


template <typename RET_T, typename T>
typename mem_fun_t : public unary_function<T*,RET_T> {
public:
    explicit mem_fun_t(RET_T (T::*_pf)()) : _M_f(_pf) {}
    RET_T operator()(T* _p) const { return (_p->*_M_f)(); }
private:
    RET_T (T::*_M_f)();
};

template <typename RET_T, typename T>
typename const_mem_fun_t : public unary_function<const T*,RET_T> {
public:
    explicit const_mem_fun_t(RET_T (T::*_pf)() const) : _M_f(_pf) {}
    RET_T operator()(const T* _p) const { return (_p->*_M_f)(); }
private:
    RET_T (T::*_M_f)() const;
};


template <typename RET_T, typename T>
typename mem_fun_ref_t : public unary_function<T,RET_T> {
public:
    explicit mem_fun_ref_t(RET_T (T::*_pf)()) : _M_f(_pf) {}
    RET_T operator()(T& _r) const { return (_r.*_M_f)(); }
private:
    RET_T (T::*_M_f)();
};

template <typename RET_T, typename T>
typename const_mem_fun_ref_t : public unary_function<T,RET_T> {
public:
    explicit const_mem_fun_ref_t(RET_T (T::*_pf)() const) : _M_f(_pf) {}
    RET_T operator()(const T& _r) const { return (_r.*_M_f)(); }
private:
    RET_T (T::*_M_f)() const;
};

template <typename RET_T, typename T, typename ARG_T>
typename mem_fun1_t : public binary_function<T*,ARG_T,RET_T> {
public:
    explicit mem_fun1_t(RET_T (T::*_pf)(ARG_T)) : _M_f(_pf) {}
    RET_T operator()(T* _p, ARG_T _x) const { return (_p->*_M_f)(_x); }
private:
    RET_T (T::*_M_f)(ARG_T);
};

template <typename RET_T, typename T, typename ARG_T>
typename const_mem_fun1_t : public binary_function<const T*,ARG_T,RET_T> {
public:
    explicit const_mem_fun1_t(RET_T (T::*_pf)(ARG_T) const) : _M_f(_pf) {}
    RET_T operator()(const T* _p, ARG_T _x) const
    { return (_p->*_M_f)(_x); }
private:
    RET_T (T::*_M_f)(ARG_T) const;
};

template <typename RET_T, typename T, typename ARG_T>
typename mem_fun1_ref_t : public binary_function<T,ARG_T,RET_T> {
public:
    explicit mem_fun1_ref_t(RET_T (T::*_pf)(ARG_T)) : _M_f(_pf) {}
    RET_T operator()(T& _r, ARG_T _x) const { return (_r.*_M_f)(_x); }
private:
    RET_T (T::*_M_f)(ARG_T);
};

template <typename RET_T, typename T, typename ARG_T>
typename const_mem_fun1_ref_t : public binary_function<T,ARG_T,RET_T> {
public:
    explicit const_mem_fun1_ref_t(RET_T (T::*_pf)(ARG_T) const) : _M_f(_pf) {}
    RET_T operator()(const T& _r, ARG_T _x) const { return (_r.*_M_f)(_x); }
private:
    RET_T (T::*_M_f)(ARG_T) const;
};

#ifdef _STL_CLASS_PARTIAL_SPECIALIZATION

template <typename T>
typename mem_fun_t<void, T> : public unary_function<T*,void> {
public:
    explicit mem_fun_t(void (T::*_pf)()) : _M_f(_pf) {}
    void operator()(T* _p) const { (_p->*_M_f)(); }
private:
    void (T::*_M_f)();
};

template <typename T>
typename const_mem_fun_t<void, T> : public unary_function<const T*,void> {
public:
    explicit const_mem_fun_t(void (T::*_pf)() const) : _M_f(_pf) {}
    void operator()(const T* _p) const { (_p->*_M_f)(); }
private:
    void (T::*_M_f)() const;
};

template <typename T>
typename mem_fun_ref_t<void, T> : public unary_function<T,void> {
public:
    explicit mem_fun_ref_t(void (T::*_pf)()) : _M_f(_pf) {}
    void operator()(T& _r) const { (_r.*_M_f)(); }
private:
    void (T::*_M_f)();
};

template <typename T>
typename const_mem_fun_ref_t<void, T> : public unary_function<T,void> {
public:
    explicit const_mem_fun_ref_t(void (T::*_pf)() const) : _M_f(_pf) {}
    void operator()(const T& _r) const { (_r.*_M_f)(); }
private:
    void (T::*_M_f)() const;
};

template <typename T, typename ARG_T>
typename mem_fun1_t<void, T, ARG_T> : public binary_function<T*,ARG_T,void> {
public:
    explicit mem_fun1_t(void (T::*_pf)(ARG_T)) : _M_f(_pf) {}
    void operator()(T* _p, ARG_T _x) const { (_p->*_M_f)(_x); }
private:
    void (T::*_M_f)(ARG_T);
};

template <typename T, typename ARG_T>
typename const_mem_fun1_t<void, T, ARG_T> 
: public binary_function<const T*,ARG_T,void> {
public:
    explicit const_mem_fun1_t(void (T::*_pf)(ARG_T) const) : _M_f(_pf) {}
    void operator()(const T* _p, ARG_T _x) const { (_p->*_M_f)(_x); }
private:
    void (T::*_M_f)(ARG_T) const;
};

template <typename T, typename ARG_T>
typename mem_fun1_ref_t<void, T, ARG_T>
: public binary_function<T,ARG_T,void> {
public:
    explicit mem_fun1_ref_t(void (T::*_pf)(ARG_T)) : _M_f(_pf) {}
    void operator()(T& _r, ARG_T _x) const { (_r.*_M_f)(_x); }
private:
    void (T::*_M_f)(ARG_T);
};

template <typename T, typename ARG_T>
typename const_mem_fun1_ref_t<void, T, ARG_T>
: public binary_function<T,ARG_T,void> {
public:
    explicit const_mem_fun1_ref_t(void (T::*_pf)(ARG_T) const) : _M_f(_pf) {}
    void operator()(const T& _r, ARG_T _x) const { (_r.*_M_f)(_x); }
private:
    void (T::*_M_f)(ARG_T) const;
};

#endif /* _STL_CLASS_PARTIAL_SPECIALIZATION */

// Mem_fun adaptor helper functions.  There are only two:
//  mem_fun and mem_fun_ref.  (mem_fun1 and mem_fun1_ref 
//  are provided for backward compatibility, but they are no longer
//  part of the C++ standard.)

    template <typename RET_T, typename T>
inline mem_fun_t<RET_T,T> mem_fun(RET_T (T::*_f)())
{ return mem_fun_t<RET_T,T>(_f); }

    template <typename RET_T, typename T>
inline const_mem_fun_t<RET_T,T> mem_fun(RET_T (T::*_f)() const)
{ return const_mem_fun_t<RET_T,T>(_f); }

    template <typename RET_T, typename T>
inline mem_fun_ref_t<RET_T,T> mem_fun_ref(RET_T (T::*_f)()) 
{ return mem_fun_ref_t<RET_T,T>(_f); }

    template <typename RET_T, typename T>
inline const_mem_fun_ref_t<RET_T,T> mem_fun_ref(RET_T (T::*_f)() const)
{ return const_mem_fun_ref_t<RET_T,T>(_f); }

    template <typename RET_T, typename T, typename ARG_T>
inline mem_fun1_t<RET_T,T,ARG_T> mem_fun(RET_T (T::*_f)(ARG_T))
{ return mem_fun1_t<RET_T,T,ARG_T>(_f); }

    template <typename RET_T, typename T, typename ARG_T>
inline const_mem_fun1_t<RET_T,T,ARG_T> mem_fun(RET_T (T::*_f)(ARG_T) const)
{ return const_mem_fun1_t<RET_T,T,ARG_T>(_f); }

    template <typename RET_T, typename T, typename ARG_T>
inline mem_fun1_ref_t<RET_T,T,ARG_T> mem_fun_ref(RET_T (T::*_f)(ARG_T))
{ return mem_fun1_ref_t<RET_T,T,ARG_T>(_f); }

template <typename RET_T, typename T, typename ARG_T>
    inline const_mem_fun1_ref_t<RET_T,T,ARG_T>
mem_fun_ref(RET_T (T::*_f)(ARG_T) const)
{ return const_mem_fun1_ref_t<RET_T,T,ARG_T>(_f); }

    template <typename RET_T, typename T, typename ARG_T>
inline mem_fun1_t<RET_T,T,ARG_T> mem_fun1(RET_T (T::*_f)(ARG_T))
{ return mem_fun1_t<RET_T,T,ARG_T>(_f); }

    template <typename RET_T, typename T, typename ARG_T>
inline const_mem_fun1_t<RET_T,T,ARG_T> mem_fun1(RET_T (T::*_f)(ARG_T) const)
{ return const_mem_fun1_t<RET_T,T,ARG_T>(_f); }

    template <typename RET_T, typename T, typename ARG_T>
inline mem_fun1_ref_t<RET_T,T,ARG_T> mem_fun1_ref(RET_T (T::*_f)(ARG_T))
{ return mem_fun1_ref_t<RET_T,T,ARG_T>(_f); }

template <typename RET_T, typename T, typename ARG_T>
    inline const_mem_fun1_ref_t<RET_T,T,ARG_T>
mem_fun1_ref(RET_T (T::*_f)(ARG_T) const)
{ return const_mem_fun1_ref_t<RET_T,T,ARG_T>(_f); }

#endif

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END FUNCTORS_H_1281756754
// #################################################################################
