// ======================================================================================
// File         : PropertyObject.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:23:21 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROPERTYOBJECT_H_1250526205
#define PROPERTYOBJECT_H_1250526205
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "PropertiesDescriptor.h"
#include "PropertyInstance.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// classes define
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class PropertyObject 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL PropertyObject : public RuntimeClass
{
    EX_DEF_RUNTIME_CLASS ( PropertyObject, RuntimeClass );

    ///////////////////////////////////////////////////////////////////////////////
    // static public functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // NOTE: this is the end of property register, the register recurcive will stop here
    static void staticRegisterProperties () 
    {
        if (s_initialized)                                    
            return;                                             

        s_descriptor.setClassName ( PropertyObject::className() );  
        s_initialized = true;
        s_descriptor.setParentDescriptor(NULL);
    }
    static const PropertiesDescriptor* staticGetDescriptor () 
    {
        ex_assert ( s_initialized, "object should be inited" );
        return &(self_t::s_descriptor); 
    }

    // 
    static const string_id_t& type_name () 
    { 
        static const string_id_t strID ("PropertyObject"); 
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    PropertyObject ();
    virtual ~PropertyObject ();

    ///////////////////////////////////////////////////////////////////////////////
    // public virtual member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // NOTE: when rewrite, remember call base_t::serialize(_pNode) to help serialize base classes.
    virtual void serialize ( ISerializeNode* _pNode );

    // NOTE: auto declare in EX_DECL_PROPERTY_OBJECT when inherit
    // NOTE: manually define by write EX_DEF_PROPERTIES_BEGIN in cpp when inherit 
    virtual void registerProperties () const { self_t::staticRegisterProperties(); }

    // NOTE: auto declare & define in EX_DECL_PROPERTY_OBJECT when inherit
    virtual PropertiesDescriptor* getDescriptor () { return const_cast<PropertiesDescriptor*>(self_t::staticGetDescriptor()); }
    virtual const PropertiesDescriptor* getDescriptor () const { return self_t::staticGetDescriptor(); }

    ///////////////////////////////////////////////////////////////////////////////
    // protected static member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // NOTE: auto declare in EX_DECL_PROPERTY_OBJECT when inherit
    // NOTE: auto define in EX_DEF_PROPERTIES_BEGIN when inherit
    static bool s_initialized;

    // NOTE: auto declare in EX_DECL_PROPERTY_OBJECT when inherit
    // NOTE: auto define in EX_DEF_PROPERTIES_BEGIN when inherit
    static PropertiesDescriptor s_descriptor;

}; // end class PropertyObject 

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < PropertyObject > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
class PropertyInstance < PropertyObject > : public PropertyInstanceBase
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef PropertyObject            class_t;
    typedef PropertyInstanceBase      base_t;
    typedef PropertyInstance<class_t> self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    // 
    PropertyInstance ( PropertyBase* _pProperty, void* _pObject )
        : base_t ( _pProperty, _pObject )
    {
        class_t* pClass = reinterpret_cast<class_t*>(_pProperty->getValuePtr(_pObject));
        const PropertiesDescriptor* pPropDesc = pClass->getDescriptor();

        HashSet<string_id_t> prop_names;

        const PropertiesDescriptor::properties_t& props = pPropDesc->properties (); 
        for ( PropertiesDescriptor::properties_t::c_iterator iter = props.begin(); iter != props.end(); ++iter )
        {
            // NOTE: if we met the same name of a property, use the first one.
            if ( prop_names.find( string_id_t( (*iter)->propName().c_str() ) ) != prop_names.end() )
                continue;

            // TODO: must prevent a PropertyObject recursively save it self!
            PropertyInstanceBase::smart_ptr_t pPropInstance = (*iter)->createPropertyInstance_sp (pClass);
            pPropInstance->setBase(this);
            m_subProps.push_back ( pPropInstance );
            prop_names.insert( string_id_t((*iter)->propName().c_str()) );
        }

        // DISABLE: we add parent property in exEditor.qt. { 
        // // recursively add parent property
        // while ( pPropDesc )
        // {
        //     const PropertiesDescriptor::properties_t& props = pPropDesc->properties (); 
        //     for ( PropertiesDescriptor::properties_t::c_iterator iter = props.begin(); iter != props.end(); ++iter )
        //     {
        //         // NOTE: if we met the same name of a property, use the first one.
        //         if ( prop_names.find( string_id_t( (*iter)->propName().c_str() ) ) != prop_names.end() )
        //             continue;

        //         // TODO: must prevent a PropertyObject recursively save it self!
        //         PropertyInstanceBase::smart_ptr_t pPropInstance = (*iter)->createPropertyInstance_sp (pClass);
        //         pPropInstance->setBase(this);
        //         m_subProps.push_back ( pPropInstance );
        //         prop_names.insert( string_id_t((*iter)->propName().c_str()) );
        //     }

        //     // get parent
        //     pPropDesc = pPropDesc->parentDescriptor();
        // }
        // } DISABLE end 
    }

}; // end class PropertyInstance < PropertyObject > 

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END PROPERTYOBJECT_H_1250526205
// #################################################################################

