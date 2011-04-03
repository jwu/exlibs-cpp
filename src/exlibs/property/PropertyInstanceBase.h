// ======================================================================================
// File         : PropertyInstanceBase.h
// Author       : Wu Jie 
// Last Change  : 01/25/2010 | 09:46:59 AM | Monday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROPERTYINSTANCEBASE_H_1264385622
#define PROPERTYINSTANCEBASE_H_1264385622
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fwd-decls
///////////////////////////////////////////////////////////////////////////////

class PropertyBase;

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstanceBase  
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL PropertyInstanceBase
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef SmartPtr<PropertyInstanceBase> smart_ptr_t;

    typedef PropertyInstanceBase self_t;
    typedef Array<PropertyInstanceBase::smart_ptr_t> sub_properties_t;
    typedef List<Pair<int,const char*> > enum_infos_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    PropertyInstanceBase ( PropertyBase* _pProperty, void* _pObject );
    virtual ~PropertyInstanceBase ();

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    void set ( void* _pValue );
    void get ( void* _pValue );
    void notifyChanged ();

    // Property Info
    const char* typeName () const;
    const string_id_t& typeNameID () const;
    const char* propName () const;
    bool readonly () const;
    bool visible () const;

    // origianl value op
    bool isModified ();
    void reset ();
    void replace ();

    // type op
    size_t typeSize () const;
    bool isEnum () const;
    bool isAtomic () const;
    bool isClass () const;
    bool isStandaloneClass () const;
    bool isPropertyClass () const;

    enum_infos_t enumInfos () const; // valid when isEnum is true

    //
    INLINE sub_properties_t& subProperties () { return m_subProps; } 
    INLINE const sub_properties_t& subProperties () const { return m_subProps; } 
    INLINE void setBase ( PropertyInstanceBase* _pBase ) { m_pBasePropertyInstance = _pBase; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    PropertyBase*           m_pProperty;
    void*                   m_pObject;
    sub_properties_t        m_subProps;
    PropertyInstanceBase*   m_pBasePropertyInstance;

    void*                   m_originalValue;

}; // end class PropertyInstanceBase

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END PROPERTYINSTANCEBASE_H_1264385622
// #################################################################################


