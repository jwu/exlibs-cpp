// ======================================================================================
// File         : singleton_macro.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 00:32:34 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef SINGLETON_MACRO_H_1250526122
#define SINGLETON_MACRO_H_1250526122
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// SingletonHolder helper macros
///////////////////////////////////////////////////////////////////////////////

// NOTE: Write EX_DECL_SINGLETON in the singleton class declaration, then write EX_IMPL_SINGLETON,_2,_3 in the define file.

// ------------------------------------------------------------------ 
// Desc: EX_DECL_SINGLETON 
// ------------------------------------------------------------------ 

#define EX_DECL_SINGLETON(_CLASSNAME) \
    public: \
        static _CLASSNAME& instance(); \
        static void destroy(); \
        static bool is_destroyed(); \
        /* ---------- back to private at the end ---------- */ \
    private:

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define __EX_DEF_SINGLETON( _SINGLETON_T, _CLASSNAME ) \
        template <> _SINGLETON_T::object_ptr_t _SINGLETON_T::s_instance = NULL; \
        template <> bool _SINGLETON_T::s_isDestroyed = false; \
        _CLASSNAME& _CLASSNAME::instance() \
        { \
            return _SINGLETON_T::instance(); \
        } \
        void _CLASSNAME::destroy() /*for Manually destroy Singleton*/ \
        { \
            _SINGLETON_T::destroyInstance(); \
        } \
        bool _CLASSNAME::is_destroyed() /*for check if singleton have been destroyed in deinit stage*/ \
        { \
            return _SINGLETON_T::is_destroyed(); \
        }

// ------------------------------------------------------------------ 
// Desc: EX_IMPL_SINGLETON
// ------------------------------------------------------------------ 

// ======================================================== 
//  _CLASSNAME, 
//  _LEVEL = 0xFFFFFFFF, 
//  _ALLOCATOR_T = Managed<EX_ALLOCATOR>::TAllocator >
// ======================================================== 

#define EX_DEF_SINGLETON( _CLASSNAME ) \
        typedef ::ex::SingletonHolder< _CLASSNAME > _CLASSNAME##singleton_t; \
        __EX_DEF_SINGLETON (_CLASSNAME##singleton_t,_CLASSNAME)

// ======================================================== 
//  _CLASSNAME, _LEVEL,
//  _ALLOCATOR_T = Managed<EX_ALLOCATOR>::TAllocator >
// ======================================================== 

#define EX_DEF_SINGLETON_2( _CLASSNAME, _LEVEL ) \
        typedef ::ex::SingletonHolder< _CLASSNAME, _LEVEL > _CLASSNAME##singleton_t; \
        __EX_DEF_SINGLETON (_CLASSNAME##singleton_t,_CLASSNAME)


// ======================================================== 
//  _CLASSNAME, _LEVEL, _ALLOCATOR_T
// ======================================================== 

#define EX_DEF_SINGLETON_3( _CLASSNAME, _LEVEL, _ALLOCATOR_T ) \
        typedef ::ex::SingletonHolder< _CLASSNAME, _LEVEL, _ALLOCATOR_T > _CLASSNAME##singleton_t; \
        __EX_DEF_SINGLETON (_CLASSNAME##singleton_t,_CLASSNAME)

// ====== UNUSED BELOW! ====== UNUSED BELOW! ====== UNUSED BELOW! ====== UNUSED BELOW! ====== 

///////////////////////////////////////////////////////////////////////////////
// useless code
//  because we have SingletonHolder, we will not use this old method.
///////////////////////////////////////////////////////////////////////////////

// UNUSED { 
#define __NEVER_USE__ 1
#ifndef __NEVER_USE__

///////////////////////////////////////////////////////////////////////////////
// EX_DEF_SINGLETON
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define __EX_DEF_SINGLETON( _SINGLETON_T, _CLASSNAME ) \
    public: \
        static INLINE _CLASSNAME& instance() \
        { \
            return _SINGLETON_T::instance(); \
        } \
        static INLINE void destroy() /*for Manually destroy Singleton*/ \
        { \
            _SINGLETON_T::destroyInstance(); \
        } \
        static INLINE bool is_destroyed() /*for check if singleton have been destroyed in deinit stage*/ \
        { \
            return _SINGLETON_T::is_destroyed(); \
        }

// ------------------------------------------------------------------ 
// Desc: inline singleton define 
// ------------------------------------------------------------------ 

// ======================================================== 
//  _CLASSNAME, 
//  _LEVEL = 0xFFFFFFFF, 
//  _ALLOCATOR_T = Managed<EX_ALLOCATOR>::TAllocator >
// ======================================================== 

#define EX_DEF_SINGLETON( _CLASSNAME ) \
    public: \
        typedef ::ex::SingletonHolder< _CLASSNAME > singleton_t; \
        __EX_DEF_SINGLETON(singleton_t,_CLASSNAME) \
        /* ---------- back to private at the end ---------- */ \
    private:

// ======================================================== 
//  _CLASSNAME, 
//  _LEVEL = 0xFFFFFFFF, 
//  _ALLOCATOR_T = Managed<EX_ALLOCATOR>::TAllocator >
// ======================================================== 

#define EX_DEF_SINGLETON_2( _CLASSNAME, _LEVEL ) \
    public: \
        typedef ::ex::SingletonHolder< _CLASSNAME, _LEVEL > singleton_t; \
        __EX_DEF_SINGLETON(singleton_t,_CLASSNAME) \
        /* ---------- back to private at the end ---------- */ \
    private:

// ======================================================== 
//  _CLASSNAME, _LEVEL, _ALLOCATOR_T
// ======================================================== 

#define EX_DEF_SINGLETON_3( _CLASSNAME, _LEVEL, _ALLOCATOR_T ) \
    public: \
        typedef ::ex::SingletonHolder< _CLASSNAME, _LEVEL, _ALLOCATOR_T > singleton_t; \
        __EX_DEF_SINGLETON(singleton_t,_CLASSNAME) \
        /* ---------- back to private at the end ---------- */ \
    private:

///////////////////////////////////////////////////////////////////////////////
// memory manage ver. 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Used to declare a singleton with class construction parameters.
// Example:
//      EX_DECL_SINGLETON_PARAMS(FooClass, (int a, float b, class_xxx& c), (a, b, c));
//      FooClass(int a, float b, class_xxx& c);
// ------------------------------------------------------------------

#define EX_DECL_SINGLETON_PARAMS(_CLASSNAME, _PDECL, _PDEF)		            \
    public:                                                                 \
		static _CLASSNAME* createInstance _PDECL					        \
		{															        \
			ex_assert(s_instance == NULL,"instance have been created");    \
			s_instance = ex_new _CLASSNAME _PDEF;					        \
			return s_instance;										        \
		}															        \
		static void destroyInstance()								        \
		{															        \
			ex_delete(s_instance);								            \
			s_instance = NULL;										        \
		}															        \
		static _CLASSNAME& instance() { return (*s_instance); }	        \
	protected:														        \
		_CLASSNAME _PDECL;											        \
		virtual ~_CLASSNAME();												\
        _CLASSNAME (const _CLASSNAME&);	                                    \
        void operator=(const _CLASSNAME&);							        \
		static _CLASSNAME* s_instance;								        \
    public:                                                                 \
        template <typename T> friend void ex::_private::Delete( T* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line );        \
        template <typename T> friend void ex::_private::DeleteNomng( T* _ptr, Allocator* _pAllocator );                                                                  \
        template <typename T> friend void ex::_private::DeleteArray( T* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line );   \
        template <typename T> friend void ex::_private::DeleteArrayNomng( T* _ptr, Allocator* _pAllocator ); \
        typedef _CLASSNAME singleton_t; \
        /* ---------- back to private at the end ---------- */ \
    private: 

// ------------------------------------------------------------------
// Desc: Used to declare a singleton without any class construction parameters
// ------------------------------------------------------------------

#define EX_DECL_SINGLETON(_CLASSNAME) \
    EX_DECL_SINGLETON_PARAMS(_CLASSNAME, (), )


// ------------------------------------------------------------------
// Desc: Singleton class definition macro helper
// ------------------------------------------------------------------

#define EX_IMPL_SINGLETON(_CLASSNAME) \
	_CLASSNAME* _CLASSNAME::s_instance = NULL;


///////////////////////////////////////////////////////////////////////////////
// system allocate memory ver. 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: same perperse with EX_DECL_SINGLETON_PARAMS, but use system 
//  memory allocator, ex_new ==> new, ex_delete ==> delete
// ------------------------------------------------------------------

#define EX_DECL_SINGLETON_PARAMS_NOMANAGE(_CLASSNAME, _PDECL, _PDEF)		\
    public:                                                                 \
		static _CLASSNAME* createInstance _PDECL					        \
		{															        \
			ex_assert(s_instance == NULL,"instance have been created");    \
			s_instance = new _CLASSNAME _PDEF;					            \
			return s_instance;										        \
		}															        \
		static void destroyInstance()								        \
		{															        \
			delete(s_instance);								            \
			s_instance = NULL;										        \
		}															        \
		static _CLASSNAME& instance() { return (*s_instance); }	        \
	protected:														        \
		_CLASSNAME _PDECL;											        \
		virtual ~_CLASSNAME();												\
        _CLASSNAME (const _CLASSNAME&);	                                    \
        void operator=(const _CLASSNAME&);							        \
		static _CLASSNAME* s_instance;								        \
    public:                                                                 \
        template <typename T> friend void ex::_private::Delete( T* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line );       \
        template <typename T> friend void ex::_private::DeleteNomng( T* _ptr, Allocator* _pAllocator );                                                                 \
        template <typename T> friend void ex::_private::DeleteArray( T* _ptr, Allocator* _pAllocator, const char* _file_name, const char* _function_name, size_t _line );  \
        template <typename T> friend void ex::_private::DeleteArrayNomng( T* _ptr, Allocator* _pAllocator ); \
        typedef _CLASSNAME singleton_t; \
        /* ---------- back to private at the end ---------- */ \
    private:

// ------------------------------------------------------------------
// Desc: Used to declare a singleton without any class construction parameters
// ------------------------------------------------------------------

#define EX_DECL_SINGLETON_NOMANAGE(_CLASSNAME) \
    EX_DECL_SINGLETON_PARAMS_NOMANAGE(_CLASSNAME, (), )

#endif // END __NEVER_USE__
// } UNUSED end 

// #################################################################################
#endif // END SINGLETON_MACRO_H_1250526122
// #################################################################################
