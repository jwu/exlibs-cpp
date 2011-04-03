// ======================================================================================
// File         : BinarySerializeNode.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:25:14 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef BINARYSERIALIZENODE_H_1250526317
#define BINARYSERIALIZENODE_H_1250526317
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SerializeNode.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fwd-decls
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class BinarySerializeNode 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL BinarySerializeNode : public ISerializeNode
{
    EX_DEF_RUNTIME_CLASS ( BinarySerializeNode, ISerializeNode );

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef ISerializeNode          base_t;
    typedef BinarySerializeNode    self_t;
    typedef BinarySerializeNode*   ptr_t;

    typedef base_t::iterator iterator;
    typedef base_t::iterator c_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    BinarySerializeNode ( uint _bytesToReserve = 0, bool _isSaving = true );
    virtual ~BinarySerializeNode ();

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
    virtual result_t getAttr ( const char* _key, void** _ppValue, uint _bytes ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    void setLoading () { base_t::setLoading(); m_CurPos = 0; }
    void setSaving () { base_t::setSaving(); m_CurPos = 0; }

    void* data () const { return m_pData; }
    uint GetCapacity () const { return m_Capacity; }
    uint size () const 
    {
        if ( isLoading() ) return m_Capacity;
        if ( isSaving() ) return m_CurPos;
        return 0;
    }
    uint GetCurPos () const { return m_CurPos; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    result_t WriteToBuffer ( const void* _pData, uint _size );
    result_t ReadFromBuffer ( void* _pData, uint _size ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    mutable void*   m_pData;
    mutable uint    m_Capacity;
    mutable uint    m_CurPos;

    // DISABLE { 
    // // NOTE: the m_Strings is for loading string data ( const char*/wchar* ), when
    // //       loading this data, the serialize node will allocate a memory buffer to store
    // //       the character come from binary data, then give the address back for user.
    // //       This data will be free when the serialize node destroied.
    // // NOTE: using list because Array will change the address when push_back.
    // typedef List<string_t> strings_t;
    // typedef List<wstring_t> wstrings_t;
    // mutable strings_t    m_Strings;
    // mutable wstrings_t   m_WStrings;
    // } DISABLE end 

}; // end class BinarySerializeNode

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END BINARYSERIALIZENODE_H_1250526317
// #################################################################################

