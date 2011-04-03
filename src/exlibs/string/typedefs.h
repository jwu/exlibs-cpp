// ======================================================================================
// File         : typedefs.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 11:14:07 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TYPEDEFS_H_1281842049
#define TYPEDEFS_H_1281842049
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// typedefs 
///////////////////////////////////////////////////////////////////////////////

// strings
typedef String<char,::ex::Managed<EX_ALLOCATOR>::TAllocator>  string_t;
typedef String<wchar,::ex::Managed<EX_ALLOCATOR>::TAllocator> wstring_t;
typedef String<tchar,::ex::Managed<EX_ALLOCATOR>::TAllocator> tstring_t;

// stringID
typedef StringID<char> string_id_t;
typedef StringID<wchar> wstring_id_t;
typedef StringID<tchar> tstring_id_t;

// path
typedef Path<char,::ex::Managed<EX_ALLOCATOR>::TAllocator> path_t;
typedef Path<wchar,::ex::Managed<EX_ALLOCATOR>::TAllocator> wpath_t;
typedef Path<tchar,::ex::Managed<EX_ALLOCATOR>::TAllocator> tpath_t;

// resPath
typedef ResPath<char,::ex::Managed<EX_ALLOCATOR>::TAllocator> r_path_t;
typedef ResPath<wchar,::ex::Managed<EX_ALLOCATOR>::TAllocator> r_wpath_t;
typedef ResPath<tchar,::ex::Managed<EX_ALLOCATOR>::TAllocator> r_tpath_t;

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END TYPEDEFS_H_1281842049
// #################################################################################
