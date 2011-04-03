// ======================================================================================
// File         : string_defs.cpp
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:25:26 PM | Sunday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exLibs.h"
#include "String.h"
#include "StringID.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// String
///////////////////////////////////////////////////////////////////////////////

template <> string_t string_t::null = string_t();
template <> wstring_t wstring_t::null = wstring_t();

template <> String<char,NoManaged<NullType>::TAllocator > String<char,NoManaged<NullType>::TAllocator >::null = String<char,NoManaged<NullType>::TAllocator >();
template <> String<wchar,NoManaged<NullType>::TAllocator > String<wchar,NoManaged<NullType>::TAllocator >::null = String<wchar,NoManaged<NullType>::TAllocator >();

///////////////////////////////////////////////////////////////////////////////
// StringID
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <> string_id_t string_id_t::null = string_id_t();
template <> wstring_id_t wstring_id_t::null = wstring_id_t();

template <> string_id_t string_id_t::s_folder = string_id_t();
template <> wstring_id_t wstring_id_t::s_folder = wstring_id_t();

template <> string_id_t string_id_t::s_config = string_id_t();
template <> wstring_id_t wstring_id_t::s_config = wstring_id_t();

template <> string_id_t string_id_t::s___root__ = string_id_t();
template <> wstring_id_t wstring_id_t::s___root__ = wstring_id_t();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <> StringID<char>::string_set_t* StringID<char>::s_pStringSet = NULL;
template <> StringID<wchar>::string_set_t* StringID<wchar>::s_pStringSet = NULL;


// ######################### 
} // end namespace ex 
// ######################### 

