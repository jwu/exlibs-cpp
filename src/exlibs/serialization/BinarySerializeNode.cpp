// ======================================================================================
// File         : BinarySerializeNode.cpp
// Author       : Wu Jie 
// Last Change  : 08/16/2009 | 16:43:38 PM | Sunday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "BinarySerializeNode.h"

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BinarySerializeNode::BinarySerializeNode ( uint _bytesToReserve, bool _isSaving )
    : ISerializeNode ()
    , m_pData (NULL)
    , m_Capacity (0)
    , m_CurPos (0)
{
    //
    if ( _isSaving )
        setSaving ();
    else
        setLoading ();

    //
    if ( _bytesToReserve >= 0 )
    {

        m_pData = ex_malloc ( _bytesToReserve );
        m_Capacity = _bytesToReserve;
        m_CurPos = 0;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BinarySerializeNode::~BinarySerializeNode ()
{
    ex_free(m_pData);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::addChild( const char* _tagName, ISerializeNode* _pNode )
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ISerializeNode* BinarySerializeNode::newChild( const char* _tagName )
{
    return this;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool BinarySerializeNode::removeChild( ISerializeNode* _pNode )
{
    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint BinarySerializeNode::firstChild( const char* _tagName ) const
{
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ISerializeNode* BinarySerializeNode::nextChild( const char* _tagName )
{
    return const_cast<ISerializeNode*>(static_cast<const ISerializeNode*>(this));
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ISerializeNode* BinarySerializeNode::child( uint _idx ) const
{
    return const_cast<ISerializeNode*>(static_cast<const ISerializeNode*>(this));
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint BinarySerializeNode::childCount() const
{
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint BinarySerializeNode::childCount( const char* _tagName ) const
{
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char* BinarySerializeNode::tag() const
{
    return "BinarySerializeNode";
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool BinarySerializeNode::isTag( const char* _tagName ) const
{
    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint BinarySerializeNode::attrCount() const
{
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool BinarySerializeNode::hasAttr( const char* _key ) const
{
    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool BinarySerializeNode::removeAttr( const char* _key )
{
    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::saveToFile ( const char* _fileName ) const
{
    ex_assert_return ( isSaving(), EResult::write_failed, "The node is used for loading!" );

    //
    IFile::smart_ptr_t spFile = futil::file::replace<PhysicalFile>(_fileName);
    if ( spFile && m_pData && m_CurPos > 0 )
    {
        // write header
        spFile->write ( m_pData, m_CurPos );
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::loadFromFile ( const char* _fileName )
{
    IFile::smart_ptr_t spFile = futil::file::readonly<PhysicalFile>(_fileName);
    if ( spFile )
    {
        // read raw data
        m_Capacity = uint(spFile->size());
        m_CurPos = 0;
        m_pData = ex_realloc ( m_pData, m_Capacity );

        //
        spFile->read ( m_pData, m_Capacity );

        //
        setLoading ();
    }
    else 
    {
        return EResult::not_found;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::saveToFile ( IFile::smart_ptr_t _spFile, futil::sz_t* _pBytesSaved ) const
{
    ex_assert_return ( isSaving(), EResult::write_failed, "The node is used for loading!" );

    //
    if ( _spFile && m_pData && m_CurPos > 0 )
    {
        // write header
        futil::sz_t bytesWritten = _spFile->write ( m_pData, m_CurPos );
        if ( _pBytesSaved )
            *_pBytesSaved = bytesWritten;
    }
    
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::loadFromFile ( IFile::smart_ptr_t _spFile, futil::sz_t _bytesToLoad )
{
    if ( _spFile )
    {
        //
        futil::sz_t restBytes = _spFile->sizeToEnd();
        ex_assert_return ( _bytesToLoad <= restBytes, EResult::read_failed, "the rest bytes of the file is less than the bytes you try to read." );

        // read raw data
        m_Capacity = uint(_bytesToLoad);
        m_CurPos = 0;

        if ( m_Capacity > 0 )
        {
            m_pData = ex_realloc ( m_pData, m_Capacity );
            _spFile->read ( m_pData, m_Capacity );
        }

        //
        setLoading ();
    }
    
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::loadFromBuffer ( void* _pData, uint _bufferSize )
{
    // read raw data
    m_Capacity = uint(_bufferSize);
    m_CurPos = 0;

    if ( m_Capacity > 0 )
    {
        m_pData = ex_malloc( m_Capacity ); 
        ex::mem::cpy( m_pData, _pData, m_Capacity );
    }

    //
    setLoading ();
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::WriteToBuffer ( const void* _pData, uint _size )
{
    //
    uint originalSize = m_Capacity;
    uint restSize = m_Capacity - m_CurPos;

    ex_assert_return ( originalSize > 0, EResult::write_failed, "The size of the node can't be zero for writing." );

    // if rest size less than the size we try to write, enlarge the size twice
    while ( restSize < _size )
    {
        m_Capacity *= 2;
        restSize = m_Capacity - m_CurPos;
    }

    // resize 
    if ( m_Capacity > originalSize )
    {
        m_pData = ex_realloc( m_pData, m_Capacity );
    }

    // copy the data to m_pData
    memcpy ( (void*)((int8*)m_pData + m_CurPos), _pData, _size );
    m_CurPos += _size;

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::ReadFromBuffer ( void* _pData, uint _size ) const
{
    // if rest size less than the size we try to write, the data reading process should be wrong
    ex_assert_return ( m_Capacity - m_CurPos >= _size, EResult::read_failed, "if rest size less than the size we try to write, the data reading process should be wrong" );

    // copy the data to m_pData
    memcpy ( _pData, (void*)((int8*)m_pData + m_CurPos), _size );
    m_CurPos += _size;

    return EResult::ok;
}

///////////////////////////////////////////////////////////////////////////////
// Set/Get Attribute functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, bool _value )
{
    WriteToBuffer ( &_value, sizeof(bool) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, bool* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(bool) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, int8 _value )
{
    WriteToBuffer ( &_value, sizeof(int8) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, int8* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(int8) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, uint8 _value )
{
    WriteToBuffer ( &_value, sizeof(uint8) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, uint8* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(uint8) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, int16 _value )
{
    WriteToBuffer ( &_value, sizeof(int16) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, int16* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(int16) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, uint16 _value )
{
    WriteToBuffer ( &_value, sizeof(uint16) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, uint16* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(uint16) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, int32 _value )
{
    WriteToBuffer ( &_value, sizeof(int32) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, int32* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(int32) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, uint32 _value )
{
    WriteToBuffer ( &_value, sizeof(uint32) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, uint32* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(uint32) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, int64 _value )
{
    WriteToBuffer ( &_value, sizeof(int64) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, int64* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(int64) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, uint64 _value )
{
    WriteToBuffer ( &_value, sizeof(uint64) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, uint64* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(uint64) );
}

// DISABLE { 
// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// void BinarySerializeNode::setAttr ( const char* _key, int _value )
// {
//     WriteToBuffer ( &_value, sizeof(int) );
// }

// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// result_t BinarySerializeNode::getAttr ( const char* _key, int* _pValue ) const
// {
//     return ReadFromBuffer ( (void*)_pValue, sizeof(int) );
// }

// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// void BinarySerializeNode::setAttr ( const char* _key, uint _value )
// {
//     WriteToBuffer ( &_value, sizeof(uint) );
// }

// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// result_t BinarySerializeNode::getAttr ( const char* _key, uint* _pValue ) const
// {
//     return ReadFromBuffer ( (void*)_pValue, sizeof(uint) );
// }
// } DISABLE end 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, float _value )
{
    WriteToBuffer ( &_value, sizeof(float) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, float* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(float) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, double _value )
{
    WriteToBuffer ( &_value, sizeof(double) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, double* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(double) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, char _value )
{
    WriteToBuffer ( &_value, sizeof(char) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, char* _pValue ) const
{
    return ReadFromBuffer ( (void*)_pValue, sizeof(char) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, const char* _value )
{
    uint strlen = str::len(_value);
    WriteToBuffer ( &strlen, sizeof(uint) );
    WriteToBuffer ( _value, strlen * sizeof(char) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, const char** _pValue ) const
{
    uint strlen = 0;
    ReadFromBuffer ( &strlen, sizeof(uint) );

    uint restSize = m_Capacity - m_CurPos;
    if (  restSize < strlen  )
    {
        return EResult::read_failed;
    }

    // DISABLE { 
    // m_Strings.push_back ( string_t( (char*)((int8*)m_pData + m_CurPos), strlen ) );
    // *_pValue = m_Strings.back().c_str(); 
    // } DISABLE end 

    // TEMP HACK { 
    // NOTE: this process will make the string go to the string id table, so that 
    //       it will not be delete after the xml serialize. 
    string_id_t sid( (char*)((int8*)m_pData + m_CurPos) ); 
    *_pValue = sid.c_str();
    // } TEMP HACK end 

    m_CurPos += strlen;
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, const wchar* _value )
{
    uint strlen = str::len(_value);
    WriteToBuffer ( &strlen, sizeof(uint) );
    WriteToBuffer ( _value, strlen * sizeof(wchar) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, const wchar** _pValue ) const
{
    ex_check_return( false, EResult::read_failed, "wchar not support yet!" );

    uint strlen = 0;
    ReadFromBuffer ( &strlen, sizeof(uint) );

    uint restSize = m_Capacity - m_CurPos;
    if (  restSize < strlen  )
    {
        return EResult::read_failed;
    }

    // DISABLE { 
    // m_WStrings.push_back ( wstring_t( (wchar*)((int8*)m_pData + m_CurPos), strlen ) );
    // *_pValue = m_WStrings.back().c_str(); 
    // } DISABLE end 

    // TODO { 
    // TEMP HACK { 
    // NOTE: this process will make the string go to the string id table, so that 
    //       it will not be delete after the xml serialize. 
    // char* utf8 = (char*)ex_stack_malloc( strlen * sizeof(wchar) );
    // utf16_to_utf8( (wchar*)((int8*)m_pData + m_CurPos), utf8 );
    // string_id_t sid(utf8); 
    // *_pValue = sid.c_str();
    // } TEMP HACK end 
    // } TODO end 

    m_CurPos += strlen * sizeof(wchar);

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void BinarySerializeNode::setAttr ( const char* _key, const void* _value, uint _bytes )
{
    WriteToBuffer ( _value, _bytes );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t BinarySerializeNode::getAttr ( const char* _key, void** _ppValue, uint _bytes ) const
{
    if ( _bytes == 0 )
        return EResult::ok;

    ex_assert_return ( *_ppValue != NULL, EResult::read_failed, "*_ppValue can't be NULL" );

    // 
    uint restSize = m_Capacity - m_CurPos;
    if (  restSize < _bytes  )
    {
        return EResult::read_failed;
    }

    //
    memcpy ( *_ppValue, (void*)((int8*)m_pData + m_CurPos), _bytes );
    m_CurPos += _bytes;
    
    return EResult::ok;
}

// ######################### 
} // end namespace ex 
// ######################### 


