// ======================================================================================
// File         : XmlSerializeNode.cpp
// Author       : Wu Jie 
// Last Change  : 12/20/2008 | 23:30:33 PM | Saturday,December
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "XmlSerializeNode.h"

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

XmlSerializeNode::XmlSerializeNode ( const XmlNode::smart_ptr_t& _spNode, bool _isSaving )
    : ISerializeNode ()
{
    //
    if ( _isSaving )
        setSaving ();
    else
        setLoading ();

    //
    if (_spNode)
    {
        this->init (_spNode);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

XmlSerializeNode::~XmlSerializeNode ()
{
    for ( serialize_nodes_t::iterator iter = m_Children.begin(); iter != m_Children.end(); ++iter )
    {
        ex_delete ( (*iter) );
    }
    for ( serialize_nodes_t::iterator iter = m_LoadedChildren.begin(); iter != m_LoadedChildren.end(); ++iter )
    {
        ex_delete ( (*iter) );
    }
    m_Children.clear();
    m_LoadedChildren.clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::init ( const XmlNode::smart_ptr_t& _spNode )
{
    m_spXmlNode = _spNode; 
    m_Tag = _spNode->tag();

    // create children
    for ( XmlNode::iterator iter = m_spXmlNode->begin(m_spXmlNode); iter != m_spXmlNode->end(m_spXmlNode); ++iter )
    {
        XmlSerializeNode* pNode = ex_new XmlSerializeNode( (*iter), this->isSaving() );
        m_Children.push_back (pNode);
    }
    m_LoadedChildren.clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::addChild( const char* _tagName, ISerializeNode* _pNode )
{
    ex_assert ( m_spXmlNode, "xml node haven't created. pls create it by init or in contructor" );

    XmlSerializeNode* pNode = static_cast<XmlSerializeNode*>(_pNode);
    m_spXmlNode->addChild ( _tagName, pNode->m_spXmlNode );
    m_Children.push_back (pNode);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ISerializeNode* XmlSerializeNode::newChild( const char* _tagName )
{
    ex_assert ( m_spXmlNode, "xml node haven't created. pls create it by init or in contructor" );

    XmlSerializeNode* pNode = ex_new XmlSerializeNode( m_spXmlNode->newChild (_tagName), this->isSaving() );
    m_Children.push_back (pNode);
    return pNode; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool XmlSerializeNode::removeChild( ISerializeNode* _pNode )
{
    ex_assert ( m_spXmlNode, "xml node haven't created. pls create it by init or in contructor" );

    //
    XmlSerializeNode* pNode = static_cast<XmlSerializeNode*>(_pNode);
    bool bResult_Xml = m_spXmlNode->removeChild( pNode->m_spXmlNode );

    //
    bool bResult = false;
    serialize_nodes_t::iterator iter = m_Children.find(pNode);
    if ( iter != m_Children.end() )
    {
        ex_delete( (*iter) );
        m_Children.erase(iter);
        bResult = true;
    }

    //
    ex_assert ( bResult == bResult_Xml, "XmlSerializeNode and XmlNode don't have the same result." );

    return bResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint XmlSerializeNode::firstChild( const char* _tagName ) const
{
    return m_spXmlNode->firstChild ( _tagName );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ISerializeNode* XmlSerializeNode::nextChild( const char* _tagName )
{
    serialize_nodes_t::iterator iter = m_Children.begin();
    for ( ; iter != m_Children.end(); ++iter )
    {
        if ( (*iter)->isTag(_tagName) )
        {
            break;
        }
    }

    //
    if ( iter != m_Children.end() )
    {
        XmlSerializeNode* pNode = *iter;
        m_Children.erase(iter);
        m_LoadedChildren.push_back(pNode);
        return pNode;
    }

    return NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ISerializeNode* XmlSerializeNode::child( uint _idx ) const
{
    return m_Children[_idx];
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint XmlSerializeNode::childCount() const
{
    return m_spXmlNode->childCount();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint XmlSerializeNode::childCount( const char* _tagName ) const
{
    return m_spXmlNode->childCount( _tagName );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char* XmlSerializeNode::tag() const
{
    return m_Tag.c_str();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool XmlSerializeNode::isTag( const char* _tagName ) const
{
    return (m_Tag == _tagName);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint XmlSerializeNode::attrCount() const
{
    return m_spXmlNode->attrCount();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool XmlSerializeNode::hasAttr( const char* _key ) const
{
    return m_spXmlNode->hasAttr ( _key ) != uint(ex::IndexNone);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool XmlSerializeNode::removeAttr( const char* _key )
{
    return m_spXmlNode->removeAttr ( _key );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::saveToFile ( const char* _fileName ) const
{
    ex_assert_return ( isSaving(), EResult::write_failed, "The node is used for loading!" );
    ex_assert_return ( m_spXmlNode, EResult::write_failed, "xml node haven't created. pls create it by init or in contructor" );

    m_spXmlNode->saveToFile ( _fileName );
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::loadFromFile ( const char* _fileName )
{
    result_t eResult = EResult::ok;

    if ( futil::file::exists(path_t(_fileName)) == false )
    {
        return EResult::not_found;
    }

    //
    ex::XmlParser parser;
    XmlNode::smart_ptr_t spRoot = parser.ParseFile(_fileName);

    //
    if ( spRoot )
    {
        setLoading ();
        this->init ( spRoot );
    }
    else
    {
        eResult = EResult::not_found;
    }

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::saveToFile ( IFile::smart_ptr_t _spFile, futil::sz_t* _pBytesSaved ) const
{
    ex_assert_return ( isSaving(), EResult::write_failed, "The node is used for loading!" );

    //
    futil::offset_t posBeforeSave = _spFile->tell();
    ex_check_return ( m_spXmlNode->saveToFile ( _spFile, 0 ), 
                      EResult::failed,
                      "failed to save XmlSerializeNode to file: %s", 
                      _spFile->path().c_str() );
    if ( _pBytesSaved )
    {
        *_pBytesSaved = uint(_spFile->tell() - posBeforeSave);
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::loadFromFile ( IFile::smart_ptr_t _spFile, futil::sz_t _bytesToLoad )
{
    result_t eResult = EResult::ok;

    //
    uint restBytes = uint( _spFile->sizeToEnd() );
    ex_assert_return ( _bytesToLoad <= restBytes, EResult::read_failed, "the rest bytes of the file is less than the bytes you try to read." );

    DataHolder dataHolder;
    dataHolder.alloc ( size_t(_bytesToLoad) );
    _spFile->read ( dataHolder.data(), _bytesToLoad );
    ex::XmlParser parser;
    XmlNode::smart_ptr_t spRoot = parser.Parse( static_cast<tchar*>(dataHolder.data()) );

    //
    if ( spRoot ) {
        setLoading ();
        this->init ( spRoot );
    }
    else {
        eResult = EResult::not_found;
    }
    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::loadFromBuffer ( void* _pData, uint _bufferSize )
{
    result_t eResult = EResult::ok;

    DataHolder dataHolder;
    dataHolder.alloc ( _pData, size_t(_bufferSize) );
    ex::XmlParser parser;
    XmlNode::smart_ptr_t spRoot = parser.Parse( static_cast<tchar*>(dataHolder.data()) );

    //
    if ( spRoot ) {
        setLoading ();
        this->init ( spRoot );
    }
    else {
        eResult = EResult::not_found;
    }
    return eResult;
}

///////////////////////////////////////////////////////////////////////////////
// Set/Get Attribute functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, bool _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, bool* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, int8 _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, int8* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, uint8 _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, uint8* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, int16 _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, int16* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, uint16 _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, uint16* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, int32 _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, int32* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, uint32 _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, uint32* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, int64 _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, int64* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, uint64 _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, uint64* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// DISABLE { 
// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// void XmlSerializeNode::setAttr ( const char* _key, int _value )
// {
//     m_spXmlNode->setAttr ( _key, _value );
// }

// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// result_t XmlSerializeNode::getAttr ( const char* _key, int* _pValue ) const
// {
//     return m_spXmlNode->getAttr ( _key, _pValue );
// }

// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// void XmlSerializeNode::setAttr ( const char* _key, uint _value )
// {
//     m_spXmlNode->setAttr ( _key, _value );
// }

// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// result_t XmlSerializeNode::getAttr ( const char* _key, uint* _pValue ) const
// {
//     return m_spXmlNode->getAttr ( _key, _pValue );
// }
// } DISABLE end 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, float _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, float* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, double _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, double* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, char _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, char* _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, const char* _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, const char** _pValue ) const
{
    result_t eResult = m_spXmlNode->getAttr ( _key, _pValue );

    // TEMP HACK { 
    // NOTE: this process will make the string go to the string id table, so that 
    //       it will not be delete after the xml serialize. 
    string_id_t sid(*_pValue); 
    *_pValue = sid.c_str();
    return eResult;
    // } TEMP HACK end 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, const wchar* _value )
{
    m_spXmlNode->setAttr ( _key, _value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, const wchar** _pValue ) const
{
    return m_spXmlNode->getAttr ( _key, _pValue );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlSerializeNode::setAttr ( const char* _key, const void* _value, uint _bytes )
{
    ex_warning ( "not support" );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlSerializeNode::getAttr ( const char* _key, void** _pValue, uint _bytes ) const
{
    ex_warning ( "not support" );
    return EResult::failed;
}

// ######################### 
} // end namespace ex 
// ######################### 

