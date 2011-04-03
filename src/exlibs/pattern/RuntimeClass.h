// ======================================================================================
// File         : RuntimeClass.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:11:10 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef RUNTIMECLASS_H_1250525473
#define RUNTIMECLASS_H_1250525473
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// disable macro
// NOTE: because getClassName is defined in WinUser.h 
///////////////////////////////////////////////////////////////////////////////

#if (EX_PLATFORM == EX_WIN32) 
    #ifdef getClassName
        #undef getClassName
    #endif
#endif

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class RuntimeClass 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class RuntimeClass
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef RuntimeClass self_t; 
    typedef TypeList< self_t, NullType > typelist_t; 

    ///////////////////////////////////////////////////////////////////////////////
    // protected static member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    static const uint32 s_hierarchyLevel = 0;

    ///////////////////////////////////////////////////////////////////////////////
    // public static member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    static const string_id_t& classID () 
    { 
        static const string_id_t classID(RuntimeClass::className()); 
        return classID; 
    } 
    static const char* className () { return "RuntimeClass"; } 
    static uint32 level () { return 0; }
    static const string_id_t* hierarchy () { return NULL; }
    static RuntimeClass* dynamicCast ( RuntimeClass* _pOther ) { return _pOther; }
    static const RuntimeClass* dynamicConstCast ( const RuntimeClass* _pOther ) { return _pOther; }
    template < typename T > static bool isA () { return false; }

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    virtual ~RuntimeClass() {}

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    virtual const string_id_t& getClassID () const = 0;
    virtual const char* getClassName () const = 0;

    //
    virtual const string_id_t* getHierarchy () const { return NULL; }
    virtual uint32 getHierarchyLevel () const { return 0; }

    //
    virtual bool isA ( const string_id_t& _classID ) const 
    {
        if ( self_t::classID() == _classID ) { return true; }
        return false;
    }

    //
    virtual bool isChildOf ( const RuntimeClass& _other ) const { return false; }
    virtual bool isChildOf ( uint32 _level, const string_id_t& _classID ) const { return false; }
    virtual bool isSameOrChildOf ( const RuntimeClass& _other ) const { return false; } 
    virtual bool isSameOrChildOf ( uint32 _level, const string_id_t& _classID ) const { return false; }

}; // end class RuntimeClass

// #########################
} // end namespace ex 
// #########################


///////////////////////////////////////////////////////////////////////////////
// macros 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: EX_DEF_RUNTIME_CLASS_NO_VIRTUAL
// ------------------------------------------------------------------ 

#define EX_DEF_RUNTIME_CLASS_NO_VIRTUAL(_selfType,_baseType) \
    __EX_DEF_RUNTIME_CLASS_STATIC(_selfType,_baseType);

// ------------------------------------------------------------------ 
// Desc: EX_DEF_RUNTIME_CLASS
// ------------------------------------------------------------------ 

#define EX_DEF_RUNTIME_CLASS(_selfType,_baseType) \
    __EX_DEF_RUNTIME_CLASS_STATIC(_selfType,_baseType); \
    __EX_DEF_RUNTIME_CLASS_VIRTUAL(_selfType,_baseType);

// ------------------------------------------------------------------ 
// Desc: __EX_DEF_RUNTIME_CLASS_STATIC
// ------------------------------------------------------------------ 

#define __EX_DEF_RUNTIME_CLASS_STATIC(_selfType,_baseType) \
        /* ---------- typedefs ---------- */ \
    public: \
        typedef _selfType self_t; \
        typedef _baseType base_t; \
        typedef ::ex::TypeList< self_t, _baseType::typelist_t > typelist_t; \
        /* ---------- static member data ---------- */ \
    protected: \
        static const ::ex::uint32 s_hierarchyLevel = _baseType::s_hierarchyLevel + 1; \
        /* ---------- static member functions ---------- */ \
    public: \
        static const ::ex::string_id_t& classID () \
        { \
            static const ::ex::string_id_t classID(_selfType::className()); \
            return classID; \
        } \
        static const char* className () \
        { \
            return #_selfType; \
        } \
        static ::ex::uint32 level () { return _selfType::s_hierarchyLevel; } \
        static const ::ex::string_id_t* hierarchy () \
        { \
            static ::ex::string_id_t hierarchyTable[_selfType::s_hierarchyLevel]; \
            const ::ex::string_id_t* parentHierarchyTable = _baseType::hierarchy(); \
            for ( ::ex::uint32 i = 0; i < _selfType::s_hierarchyLevel-1; ++i ) \
            { \
                hierarchyTable[i] = parentHierarchyTable[i]; \
            } \
            hierarchyTable[_selfType::s_hierarchyLevel-1] = _selfType::classID(); \
            return hierarchyTable; \
        } \
        static bool IsParentOf ( const RuntimeClass& _other ) \
        { \
            if ( _other.isChildOf( _selfType::s_hierarchyLevel, _selfType::classID() ) ) { return true; } \
            return false; \
        } \
        static bool IsSameOrParentOf ( const RuntimeClass& _other ) \
        { \
            if ( _other.isSameOrChildOf( _selfType::s_hierarchyLevel, _selfType::classID() ) ) { return true; } \
            return false; \
        } \
        static _selfType* dynamicCast ( RuntimeClass* _pOther ) \
        { \
            if ( _pOther != NULL && _pOther->isSameOrChildOf( _selfType::s_hierarchyLevel, _selfType::classID() ) ) \
            { \
                return static_cast< _selfType* >( _pOther ); \
            } \
            return NULL; \
        } \
        static const _selfType* dynamicConstCast ( const RuntimeClass* _pOther ) \
        { \
            if ( _pOther != NULL && _pOther->isSameOrChildOf( _selfType::s_hierarchyLevel, _selfType::classID() ) ) \
            { \
                return static_cast< const _selfType* >( _pOther ); \
            } \
            return NULL; \
        } \
        template < typename T > static bool isA () { return ::ex::typelist::IndexOf<_selfType::typelist_t,T>::value != -1; } \
        /* ---------- back to private at the end ---------- */ \
    private:

// ------------------------------------------------------------------ 
// Desc: __EX_DEF_RUNTIME_CLASS_VIRTUAL
// ------------------------------------------------------------------ 

#define __EX_DEF_RUNTIME_CLASS_VIRTUAL(_selfType,_baseType) \
        /* ---------- public member functions ---------- */ \
    public: \
        virtual ::ex::uint32 getHierarchyLevel () const { return _selfType::s_hierarchyLevel; } \
        virtual const ::ex::string_id_t& getClassID () const { return _selfType::classID(); } \
        virtual const char* getClassName () const { return _selfType::className(); } \
        virtual const ::ex::string_id_t* getHierarchy () const \
        { \
            static const ::ex::string_id_t* pHierarchyTable = _selfType::hierarchy(); \
            return pHierarchyTable; \
        } \
        virtual bool isA ( const ::ex::string_id_t& _classID ) const \
        { \
            if ( _selfType::classID() == _classID ) { return true; } \
            return _baseType::isA(_classID); \
        } \
        virtual bool isChildOf ( const RuntimeClass& _other ) const { return _selfType::isChildOf( _other.getHierarchyLevel(), _other.getClassID() ); } \
        virtual bool isChildOf ( ::ex::uint32 _level, const ::ex::string_id_t& _classID ) const \
        { \
            static const ::ex::string_id_t* pHierarchyTable = _selfType::hierarchy(); \
            return ( _level < _selfType::s_hierarchyLevel ) && ( pHierarchyTable[_level-1] == _classID ); \
        } \
        virtual bool isSameOrChildOf ( const RuntimeClass& _other ) const { return _selfType::isSameOrChildOf( _other.getHierarchyLevel(), _other.getClassID() ); } \
        virtual bool isSameOrChildOf ( ::ex::uint32 _level, const ::ex::string_id_t& _classID ) const \
        { \
            static const ::ex::string_id_t* pHierarchyTable = _selfType::hierarchy(); \
            return ( _level <= _selfType::s_hierarchyLevel ) && ( pHierarchyTable[_level-1] == _classID ); \
        } \
        /* ---------- back to private at the end ---------- */ \
    private:

// #################################################################################
#endif // END RUNTIMECLASS_H_1250525473
// #################################################################################
