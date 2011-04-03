// ======================================================================================
// File         : XmlSerializeNode.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:25:45 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef XMLSERIALIZENODE_H_1250526348
#define XMLSERIALIZENODE_H_1250526348
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SerializeNode.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class XmlSerializeNode 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL XmlSerializeNode : public ISerializeNode
{
    EX_DEF_RUNTIME_CLASS ( XmlSerializeNode, ISerializeNode );

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef ISerializeNode      base_t;
    typedef XmlSerializeNode   self_t;
    typedef XmlSerializeNode*  ptr_t;

    typedef base_t::iterator iterator;
    typedef base_t::iterator c_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    XmlSerializeNode ( const XmlNode::smart_ptr_t& _spNode = XmlNode::smart_ptr_t(NULL), bool _isSaving = true );
    virtual ~XmlSerializeNode ();

    // ========================================================
    // child
    // ========================================================

    virtual void addChild( const char* _tagName, ISerializeNode* _pNode );
    virtual ISerializeNode* newChild( const char* _tagName );
    virtual bool removeChild( ISerializeNode* _pNode );

    virtual uint firstChild( const char* _tagName ) const;
    virtual ISerializeNode* nextChild( const char* _tagName );
    virtual ISerializeNode* child( uint _idx ) const;

    virtual uint childCount() const;
    virtual uint childCount( const char* _tagName ) const;

    // ========================================================
    // tag
    // ========================================================

    virtual const char* tag() const;
    virtual bool isTag( const char* _tagName ) const;

    // ========================================================
    // attribute 
    // ========================================================

    virtual uint attrCount() const;
    virtual bool hasAttr( const char* _key ) const;
    virtual bool removeAttr( const char* _key );

    // ======================================================== 
    // file 
    // ======================================================== 

    virtual result_t saveToFile ( const char* _fileName ) const;
    virtual result_t loadFromFile ( const char* _fileName );

    virtual result_t saveToFile ( IFile::smart_ptr_t _spFile, futil::sz_t* _pBytesSaved = NULL ) const;
    virtual result_t loadFromFile ( IFile::smart_ptr_t _spFile, futil::sz_t _bytesToLoad );

    virtual result_t loadFromBuffer ( void* _pData, uint _bufferSize );

    // ======================================================== 
    // Get/Set Attr 
    // ======================================================== 

    // bool
    virtual void setAttr ( const char* _key, bool _value );
    virtual result_t getAttr ( const char* _key, bool* _pValue ) const;

    // int8
    virtual void setAttr ( const char* _key, int8 _value );
    virtual result_t getAttr ( const char* _key, int8* _pValue ) const;

    // uint8
    virtual void setAttr ( const char* _key, uint8 _value );
    virtual result_t getAttr ( const char* _key, uint8* _pValue ) const;

    // int16
    virtual void setAttr ( const char* _key, int16 _value );
    virtual result_t getAttr ( const char* _key, int16* _pValue ) const;

    // uint16
    virtual void setAttr ( const char* _key, uint16 _value );
    virtual result_t getAttr ( const char* _key, uint16* _pValue ) const;

    // int32
    virtual void setAttr ( const char* _key, int32 _value );
    virtual result_t getAttr ( const char* _key, int32* _pValue ) const;

    // uint32
    virtual void setAttr ( const char* _key, uint32 _value );
    virtual result_t getAttr ( const char* _key, uint32* _pValue ) const;

    // int64
    virtual void setAttr ( const char* _key, int64 _value );
    virtual result_t getAttr ( const char* _key, int64* _pValue ) const;

    // uint64
    virtual void setAttr ( const char* _key, uint64 _value );
    virtual result_t getAttr ( const char* _key, uint64* _pValue ) const;

    // DISABLE { 
    // // int
    // virtual void setAttr ( const char* _key, int _value );
    // virtual result_t getAttr ( const char* _key, int* _pValue ) const;

    // // uint
    // virtual void setAttr ( const char* _key, uint _value );
    // virtual result_t getAttr ( const char* _key, uint* _pValue ) const;
    // } DISABLE end 

    // float
    virtual void setAttr ( const char* _key, float _value );
    virtual result_t getAttr ( const char* _key, float* _pValue ) const;

    // double
    virtual void setAttr ( const char* _key, double _value );
    virtual result_t getAttr ( const char* _key, double* _pValue ) const;

    // char
    virtual void setAttr ( const char* _key, char _value );
    virtual result_t getAttr ( const char* _key, char* _pValue ) const;

    // const char*
    virtual void setAttr ( const char* _key, const char* _value );
    virtual result_t getAttr ( const char* _key, const char** _pValue ) const;

    // const wchar*
    virtual void setAttr ( const char* _key, const wchar* _value );
    virtual result_t getAttr ( const char* _key, const wchar** _pValue ) const;

    // void*
    virtual void setAttr ( const char* _key, const void* _value, uint _bytes );
    virtual result_t getAttr ( const char* _key, void** _pValue, uint _bytes ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void init ( const XmlNode::smart_ptr_t& _spNode );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    XmlNode::smart_ptr_t   m_spXmlNode;
    string_t                m_Tag;

    //
    typedef Array<XmlSerializeNode*> serialize_nodes_t; 
    serialize_nodes_t  m_Children;
    serialize_nodes_t  m_LoadedChildren;

}; // end class XmlSerializeNode

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END XMLSERIALIZENODE_H_1250526348
// #################################################################################

