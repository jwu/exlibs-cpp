// ======================================================================================
// File         : ResPath.hpp
// Author       : Wu Jie 
// Last Change  : 04/13/2010 | 22:30:15 PM | Tuesday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef RESPATH_HPP_1271169017
#define RESPATH_HPP_1271169017
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

#define self_t typename ResPath<T,TAllocator_T>::self_t
#define base_t typename ResPath<T,TAllocator_T>::base_t
#define str_id_t typename ResPath<T,TAllocator_T>::str_id_t

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
base_t ResPath<T,TAllocator_T>::rawfile () const { return fsys::file::rawpath(*this); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
base_t ResPath<T,TAllocator_T>::srcfile () const { return fsys::file::srcpath(*this); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
base_t ResPath<T,TAllocator_T>::binfile () const { return fsys::file::binpath(*this); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
str_id_t ResPath<T,TAllocator_T>::resTypeID () const
{
    str_id_t src_ext( this->extName().c_str() );
    return fsys::src_to_rtype (src_ext); 
}

#undef self_t
#undef base_t
#undef str_id_t

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END RESPATH_HPP_1271169017
// #################################################################################
