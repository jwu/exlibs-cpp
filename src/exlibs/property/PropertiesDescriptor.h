// ======================================================================================
// File         : PropertiesDescriptor.h
// Author       : Wu Jie 
// Last Change  : 07/28/2009 | 10:36:17 AM | Tuesday,July
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROPERTIESDESCRIPTOR_H_1250526156
#define PROPERTIESDESCRIPTOR_H_1250526156
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fwd-decl
///////////////////////////////////////////////////////////////////////////////

class PropertyBase;

///////////////////////////////////////////////////////////////////////////////
// class PropertiesDescriptor
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL PropertiesDescriptor
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Array<PropertyBase*,NoManaged<NullType>::TAllocator> properties_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    PropertiesDescriptor ();
    ~PropertiesDescriptor ();

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    static void addProperty ( properties_t* _pInProperties, PropertyBase* _pProperty );

    //
    void setClassName ( const char* _className ) { m_className = _className; }
    const char* className () const { return m_className; }

    //
    properties_t& properties () { return m_properties; }
    const properties_t& properties () const { return m_properties; }

    //
    result_t serializePropertyObject ( ISerializeNode* _pNode, void* _pObject ) const;

    //
    void setParentDescriptor ( PropertiesDescriptor* _pParentDesc ) { m_parentDesc = _pParentDesc; }
    const PropertiesDescriptor* parentDescriptor () const { return m_parentDesc; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    result_t serializeProperty ( PropertyBase* pProp, ISerializeNode* _pNode, void* _pObject ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    const char*             m_className;
    properties_t            m_properties;
    PropertiesDescriptor*   m_parentDesc;

}; // end class PropertiesDescriptor


// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END PROPERTIESDESCRIPTOR_H_1250526156
// #################################################################################

