// ======================================================================================
// File         : Flag.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:43:57 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FLAG_H_1250523828
#define FLAG_H_1250523828
// #################################################################################

// #########################
namespace ex {
// #########################

///////////////////////////////////////////////////////////////////////////////
// flag defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T1, typename T2> 
INLINE void flags_set ( T1& _srcFlags, T2 _values ) { 
    _srcFlags = (T1)_values;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T1, typename T2> 
INLINE void flags_add ( T1& _srcFlags, T2 _values ) { 
    _srcFlags |= (T1)_values;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T1, typename T2> 
INLINE void flags_rm ( T1& _srcFlags, T2 _values ) { 
    _srcFlags &= (T1)(~_values);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T1, typename T2> 
INLINE void flags_clear ( T1& _srcFlags ) { 
    _srcFlags = (T1)0; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T1, typename T2> 
INLINE bool flags_hasAll ( const T1& _srcFlags, T2 _values ) { 
    return (_values == 0) ? (_srcFlags == (T1)_values) : (_srcFlags&(T1)_values) == (T1)_values; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T1, typename T2> 
INLINE bool flags_has ( const T1& _srcFlags, T2 _values ) { 
    return (_srcFlags&(T1)_values) != (T1)0; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T1, typename T2> 
INLINE bool flags_is ( const T1& _srcFlags, T2 _values ) { 
    return (_srcFlags == (T1)_values); 
}

// #########################
} // end namespace ex
// #########################

// #################################################################################
#endif // END FLAG_H_1250523828
// #################################################################################
