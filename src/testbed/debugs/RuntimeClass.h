// ======================================================================================
// File         : RuntimeClass.h
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:18 AM | Saturday,September
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DYNAMICTYPETEST_H_1250526596
#define DYNAMICTYPETEST_H_1250526596
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class CClassA
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class CClassA : public RuntimeClass
{
#if 1
	EX_DEF_RUNTIME_CLASS( CClassA, RuntimeClass );
#else
    #define _selfType CClassA
    #define _baseType RuntimeClass

    /* ---------- typedefs ---------- */ 
public: 
    typedef _selfType self_t; 
    typedef _baseType base_t; 
    typedef TypeList< self_t, _baseType::typelist_t > typelist_t; 
    /* ---------- static member data ---------- */ 
protected: 
    static const ex::uint32 s_HierarchyLevel = _baseType::s_HierarchyLevel + 1; 
    /* ---------- static member functions ---------- */ 
public: 
    static const string_id_t& classID () 
    { 
        static const string_id_t classID(_selfType::className()); 
        return classID; 
    } 
    static const char* className () 
    { 
        return "_selfType"; 
    } 
    static ex::uint32 Level () { return _selfType::s_HierarchyLevel; } 
    static const string_id_t* Hierarchy () 
    { 
        static string_id_t hierarchyTable[_selfType::s_HierarchyLevel]; 
        const string_id_t* parentHierarchyTable = _baseType::Hierarchy(); 
        for ( ex::uint32 i = 0; i < _selfType::s_HierarchyLevel-1; ++i ) 
        { 
            hierarchyTable[i] = parentHierarchyTable[i]; 
        } 
        hierarchyTable[_selfType::s_HierarchyLevel-1] = _selfType::classID(); 
        return hierarchyTable; 
    } 
    static bool IsChild ( const RuntimeClass& _other ) 
    { 
        if ( _other.IsBase( _selfType::s_HierarchyLevel, _selfType::classID() ) ) { return true; } 
        return false; 
    } 
    static bool IsSameOrChild ( const RuntimeClass& _other ) 
    { 
        if ( _other.IsSameOrBase( _selfType::s_HierarchyLevel, _selfType::classID() ) ) { return true; } 
        return false; 
    } 
    static _selfType* DynamicCast ( RuntimeClass* _pOther ) 
    { 
        if ( _pOther != NULL && _pOther->IsSameOrBase( _selfType::s_HierarchyLevel, _selfType::classID() ) ) 
        { 
            return static_cast< _selfType* >( _pOther ); 
        } 
        return NULL; 
    } 
    static const _selfType* DynamicConstCast ( const RuntimeClass* _pOther ) 
    { 
        if ( _pOther != NULL && _pOther->IsSameOrBase( _selfType::s_HierarchyLevel, _selfType::classID() ) ) 
        { 
            return static_cast< const _selfType* >( _pOther ); 
        } 
        return NULL; 
    } 
    /* ---------- public member functions ---------- */ 
public: 
    virtual ex::uint32 GetHierarchyLevel () const { return _selfType::s_HierarchyLevel; } 
    virtual const string_id_t& GetClassID () const { return _selfType::classID(); } 
    virtual const char* getClassName () const { return _selfType::className(); } 
    virtual const string_id_t* GetHierarchy () const 
    { 
        static const string_id_t* pHierarchyTable = _selfType::Hierarchy(); 
        return pHierarchyTable; 
    } 
    virtual bool IsA ( const string_id_t& _classID ) const 
    { 
        if ( _selfType::classID() == _classID ) { return true; } 
        return _baseType::IsA(_classID); 
    } 
    virtual bool IsBase ( const RuntimeClass& _other ) const { return _selfType::IsBase( _other.GetHierarchyLevel(), _other.GetClassID() ); } 
    virtual bool IsBase ( ex::uint32 _level, const string_id_t& _classID ) const 
    { 
        static const string_id_t* pHierarchyTable = _selfType::Hierarchy(); 
        return ( _level < _selfType::s_HierarchyLevel ) && ( pHierarchyTable[_level-1] == _classID ); 
    } 
    virtual bool IsSameOrBase ( const RuntimeClass& _other ) const { return _selfType::IsSameOrBase( _other.GetHierarchyLevel(), _other.GetClassID() ); } 
    virtual bool IsSameOrBase ( ex::uint32 _level, const string_id_t& _classID ) const 
    { 
        static const string_id_t* pHierarchyTable = _selfType::Hierarchy(); 
        return ( _level <= _selfType::s_HierarchyLevel ) && ( pHierarchyTable[_level-1] == _classID ); 
    }
#endif
}; // end class CClassA

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END DYNAMICTYPETEST_H_1250526596
// #################################################################################

