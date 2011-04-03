// ======================================================================================
// File         : XmlParser.cpp
// Author       : Wu Jie 
// Last Change  : 12/04/2009 | 18:45:28 PM | Friday,December
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "XmlParser.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// public static member functions
///////////////////////////////////////////////////////////////////////////////


// ------------------------------------------------------------------
// Desc: Return the version string
// ------------------------------------------------------------------

const tchar* XmlParser::GetExpatVersion ()
{
    return XML_ExpatVersion();
}

// ------------------------------------------------------------------
// Desc: Get the version information
// ------------------------------------------------------------------

void XmlParser::GetExpatVersion( int* _pMajor, int* _pMinor, int* _pMicro )
{
    XML_Expat_Version v = XML_ExpatVersionInfo();
    if (_pMajor)
        *_pMajor = v.major;
    if (_pMinor)
        *_pMinor = v.minor;
    if (_pMicro)
        *_pMicro = v.micro;
}

// ------------------------------------------------------------------
// Desc: Get last error string
// ------------------------------------------------------------------

const tchar* XmlParser::GetErrorString( enum XML_Error _error ) 
{
    return XML_ErrorString(_error);
}

// ------------------------------------------------------------------
// Desc: start element handler wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::StartElementHandler ( void* _pUserData, const tchar* _pName, const tchar** _ppAttrs )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnStartElement( _pName, _ppAttrs );
}

// ------------------------------------------------------------------
// Desc: end element handler wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::EndElementHandler ( void* _pUserData, const tchar* _pName )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnEndElement( _pName );
}

// ------------------------------------------------------------------
// Desc: Character data handler wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::CharacterDataHandler ( void*  _pUserData, const tchar* _pData, int _len )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnCharacterData( _pData, _len );
}

// ------------------------------------------------------------------
// Desc: Processing instruction handler wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::ProcessingInstructionHandler ( void* _pUserData, const tchar* _pTarget, const tchar* _pData )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnProcessingInstruction( _pTarget, _pData );
}

// ------------------------------------------------------------------
// Desc: Comment handler wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::CommentHandler ( void* _pUserData, const tchar* _pData )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnComment( _pData );
}

// ------------------------------------------------------------------
// Desc: start CDATA section wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::StartCdataSectionHandler ( void* _pUserData )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnStartCdataSection();
}

// ------------------------------------------------------------------
// Desc: end CDATA section wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::EndCdataSectionHandler ( void* _pUserData )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnEndCdataSection();
}

// ------------------------------------------------------------------
// Desc: Default wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::DefaultHandler ( void* _pUserData, const tchar* _pData, int _len )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnDefault( _pData, _len );
}

// ------------------------------------------------------------------
// Desc: start namespace decl wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::StartNamespaceDeclHandler ( void* _pUserData, const tchar* _pPrefix, const tchar* _pURI )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnStartNamespaceDecl( _pPrefix, _pURI );
}

// ------------------------------------------------------------------
// Desc: end namespace decl wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::EndNamespaceDeclHandler ( void* _pUserData, const tchar* _pPrefix )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnEndNamespaceDecl(_pPrefix);
}

// ------------------------------------------------------------------
// Desc: XML declaration wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::XmlDeclHandler ( void* _pUserData, const tchar* _pVersion, const tchar* _pEncoding, int _isStandalone )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnXmlDecl( _pVersion, _pEncoding, _isStandalone );
}

// ------------------------------------------------------------------
// Desc: start Doctype declaration wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::StartDoctypeDeclHandler ( void* _pUserData, const tchar* _pDoctypeName, const tchar* _pSysID, const tchar* _pPubID, int hasInternalSubset )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnStartDoctypeDecl( _pDoctypeName, _pSysID, _pPubID, hasInternalSubset );
}

// ------------------------------------------------------------------
// Desc: end Doctype declaration wrapper
// ------------------------------------------------------------------

CDECL void XmlParser::EndDoctypeDeclHandler ( void* _pUserData )
{
    XmlParser* pThis = static_cast<XmlParser*>( _pUserData );
    pThis->OnEndDoctypeDecl();
}

///////////////////////////////////////////////////////////////////////////////
// public member functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlParser::XmlParser()
    : m_pParser (NULL)
    , m_Root( XmlNode::smart_ptr_t(NULL) )
{
    create();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlParser::~XmlParser()
{
    destroy();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::smart_ptr_t XmlParser::Parse( const tchar* _pBuffer, int _len, bool _isFinal )
{
    if ( InternalParse( _pBuffer, _len, _isFinal ) )
        return m_Root;
    return XmlNode::smart_ptr_t(NULL);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::smart_ptr_t XmlParser::ParseFile( const char* _filename )
{
    if ( InternalParseFile(_filename) )
        return m_Root;
    return XmlNode::smart_ptr_t(NULL);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::smart_ptr_t XmlParser::ParseBuffer( int _len, bool _isFinal )
{
    if ( InternalParseBuffer( _len, _isFinal ) )
        return m_Root;
    return XmlNode::smart_ptr_t(NULL);
}

// ------------------------------------------------------------------
// Desc: Get last error
// ------------------------------------------------------------------

XML_Error XmlParser::GetErrorCode() 
{
    ex_assert( m_pParser, "m_pParser is not create" );
    return XML_GetErrorCode(m_pParser);
}

// ------------------------------------------------------------------
// Desc: Get the current byte index
// ------------------------------------------------------------------

int64 XmlParser::GetCurrentByteIndex() 
{
    ex_assert( m_pParser, "m_pParser is not create" );
    return XML_GetCurrentByteIndex(m_pParser);
}

// ------------------------------------------------------------------
// Desc: Get the current line number
// ------------------------------------------------------------------

int XmlParser::GetCurrentLineNumber() 
{
    ex_assert( m_pParser, "m_pParser is not create" );
    return XML_GetCurrentLineNumber(m_pParser);
}

// ------------------------------------------------------------------
// Desc: Get the current column number
// ------------------------------------------------------------------

int XmlParser::GetCurrentColumnNumber() 
{
    ex_assert( m_pParser, "m_pParser is not create" );
    return XML_GetCurrentColumnNumber(m_pParser);
}

// ------------------------------------------------------------------
// Desc: Get the current byte count
// ------------------------------------------------------------------

int XmlParser::GetCurrentByteCount () 
{
    ex_assert( m_pParser, "m_pParser is not create" );
    return XML_GetCurrentByteCount(m_pParser);
}

// ------------------------------------------------------------------
// Desc: Get the input context
// ------------------------------------------------------------------

const char* XmlParser::GetInputContext ( int* _offset, int* _pSize )
{
    ex_assert( m_pParser, "m_pParser is not create" );
    return XML_GetInputContext( m_pParser, _offset, _pSize );
}

// ------------------------------------------------------------------
// Desc: Get last error string
// ------------------------------------------------------------------

const tchar* XmlParser::GetErrorString() 
{
    return XML_ErrorString( GetErrorCode() );
}

///////////////////////////////////////////////////////////////////////////////
// protected member functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: create a parser
// ------------------------------------------------------------------

bool XmlParser::create( const tchar* _encoding, const tchar* _sep )
{
    // destroy the old parser
    destroy ();

    // If the encoding or seperator are empty, then NULL
    if ( _encoding != NULL && _encoding [0] == 0 )
        _encoding = NULL;
    if (_sep != NULL && _sep [0] == 0)
        _sep = NULL;

    // create the new one
    m_pParser = XML_ParserCreate_MM( _encoding, NULL, _sep );
    if (m_pParser == NULL)
        return false;

    // Invoke the post create routine
    OnPostCreate();

    // Set the user data used in callbacks
    XML_SetUserData( m_pParser, (void*)this );
    return true;
}

// ------------------------------------------------------------------
// Desc: destroy the parser
// ------------------------------------------------------------------

void XmlParser::destroy()
{
    if ( m_pParser != NULL )
        XML_ParserFree(m_pParser);
    m_pParser = NULL;
}

// ------------------------------------------------------------------
// Desc: Parse a block of data
// ------------------------------------------------------------------

bool XmlParser::InternalParse( const tchar* _pBuffer, int _len, bool _isFinal )
{
    // Validate
    ex_assert( m_pParser, "m_pParser is not create" );

    // Get the length if not specified
    if ( _len < 0 )
    {
        _len = str::len(_pBuffer);
        if( typeop::IsSameType<tchar,wchar>::Result ) // if it is wchar, len * 2
            _len *= 2;
    }

    // Invoke the parser
    if ( XML_Parse( m_pParser, _pBuffer, _len, _isFinal ) == XML_STATUS_ERROR )
    {
        this->OnParseError();
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
// Desc: Parse file directly 
// ------------------------------------------------------------------

bool XmlParser::InternalParseFile( const char* _filename )
{
    // load file to buffer
    // check if file exists
    ex_assert_return( futil::file::exists(path_t(_filename)), false, "%s not Existss.", _filename );

    IFile::smart_ptr_t spFile = futil::file::open<PhysicalFile>(_filename);
    if ( spFile )
    {
        uint32 filesize = uint32(spFile->size());
        int bufferSize =  sizeof(tchar) * filesize ;
        // get internal buffer
        void* pBuffer = GetBuffer(bufferSize);
        // read file to buffer
        spFile->read( pBuffer, filesize );
        // close file immediately
        spFile->close();

        // record file name help handle error 
        m_ParsingFileName = _filename;
        // parse file
        bool bResult = InternalParseBuffer(bufferSize);
        m_ParsingFileName = NULL;

        // return result
        return bResult;
    }
    return false;
}

// ------------------------------------------------------------------
// Desc: Parse internal buffer
// ------------------------------------------------------------------

bool XmlParser::InternalParseBuffer( int _len, bool _isFinal )
{
    ex_assert( m_pParser, "m_pParser is not create" );
    if ( XML_ParseBuffer( m_pParser, _len, _isFinal ) == XML_STATUS_ERROR )
    {
        this->OnParseError();
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
// Desc: Get the internal buffer
// ------------------------------------------------------------------

void* XmlParser::GetBuffer( int _len )
{
    ex_assert( m_pParser, "m_pParser is not create" );
    return XML_GetBuffer( m_pParser, _len );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnPostCreate()
{
    // Enable all the event routines we want
    EnableStartElementHandler();
    EnableEndElementHandler();
    EnableCharacterDataHandler();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnStartElement ( const tchar* _pName, const char** _ppAttrs )
{
    //
    XmlNode::smart_ptr_t   parent;
    XmlNode::smart_ptr_t   node;

    //
    node = XmlNode::smart_ptr_t( ex_new XmlNode(_pName) );

    //
    if ( !m_NodeStack.empty() )
    {
        parent = m_NodeStack.top();
    }
    else
    {
        m_Root = node;
    }
    m_NodeStack.push(node);

    //
    if ( parent )
    {
        parent->addChild(node);
    }

    // 
#ifdef EX_DEBUG 
    node->setLine( XML_GetCurrentLineNumber(m_pParser) );
#endif

    // get num of attributes
    int idx = 0;
    while ( _ppAttrs[idx] != NULL )
        idx += 2;

    node->ReserveAttr(idx/2);

    //
    idx = 0;
    while ( _ppAttrs[idx] != NULL )
    {
        node->setAttr( _ppAttrs[idx], _ppAttrs[idx+1] );
        idx += 2;
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnEndElement ( const tchar* _pName )
{
    ex_assert( !m_NodeStack.empty(), "Invalid called for OnEndElement" );
    if ( !m_NodeStack.empty() )
    {
        m_NodeStack.pop();
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnCharacterData ( const tchar* _pData, int _len )
{
    // get white space
    const tchar* white_space_list;
    uint list_count = 0;
    ex::str::getWSList( white_space_list, list_count );

    // skip empty content
    bool validContent = false;
    for ( int i = 0; i < _len; ++i )
    {
        if ( !str::isInTheList( _pData[i], white_space_list, list_count ) )
        {
            validContent = true;
            break;
        }
    }

    // retrun if invalid content ( empty content )
    if ( !validContent )
        return;

    // TODO: implement temp string allocator
    // 
    char* pMallocBuffer = NULL;
    char* pStrBuffer = NULL;
    char str[EX_INT16_MAX+1];

    if ( _len < EX_INT16_MAX+1 )
    {
        pStrBuffer = str;
    }
    else
    {
        pStrBuffer = pMallocBuffer = (char*)ex_malloc( _len + 1 );
    }
    memcpy( pStrBuffer, _pData, _len );
    pStrBuffer[_len] = 0;

    // set contents
    ex_assert( !m_NodeStack.empty(), "Invalid Node Stack" );
    if ( !m_NodeStack.empty() )
    {
        m_NodeStack.top()->SetContent( pStrBuffer );
    }
    ex_free(pMallocBuffer);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnProcessingInstruction ( const tchar* _pTarget, const tchar* _pData )
{
    printf("OnProcessingInstruction\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnComment ( const tchar* _Data )
{
    printf("OnComment\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnStartCdataSection ()
{
    printf("OnStartCdataSection\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnEndCdataSection ()
{
    printf("OnEndCdataSection\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnDefault ( const tchar* _Data, int _len )
{
    printf("OnDefault\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool XmlParser::OnExternalEntityRef ( const tchar* _pContext, const tchar* _pBase, const tchar* _pSystemID, const tchar* _pPublicID )
{
    printf("OnExternalEntityRef\n");
    return true;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool XmlParser::OnUnknownEncoding ( const tchar* _pName, XML_Encoding* _pInfo )
{
    printf("OnUnknownEncoding\n");
    return true;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnStartNamespaceDecl ( const tchar* _pPrefix, const tchar* _pURI )
{
    printf("OnStartNamespaceDecl\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnEndNamespaceDecl ( const tchar* _pPrefix )
{
    printf("OnEndNamespaceDecl\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnXmlDecl ( const tchar* _pVersion, const tchar* _pEncoding, int _isStandalone )
{
    printf("OnXmlDecl\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnStartDoctypeDecl ( const tchar* _pDoctypeName, const tchar* _pSysID, const tchar* _pPubID, int _hasInternalSubset )
{
    printf("OnStartDoctypeDecl\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnEndDoctypeDecl ()
{
    printf("OnEndDoctypeDecl\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlParser::OnParseError ()
{
    ex::fprintf( stderr, "%s Parse error at line %d: %s\n", m_ParsingFileName, GetCurrentLineNumber(), GetErrorString() );
    ex_error( "%s Parse error at line %d: %s\n", m_ParsingFileName, GetCurrentLineNumber(), GetErrorString() );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define IMPLEMENT_COMMON_ENABLE_FUNCTION( _name ) \
    void XmlParser::Enable##_name( bool _isEnable ) \
{ \
    ex_assert( m_pParser, "m_pParser is not create" ); \
    XML_Set##_name( m_pParser, _isEnable ? _name : NULL ); \
}

IMPLEMENT_COMMON_ENABLE_FUNCTION( StartElementHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( EndElementHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( CharacterDataHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( ProcessingInstructionHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( CommentHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( StartCdataSectionHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( EndCdataSectionHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( StartNamespaceDeclHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( EndNamespaceDeclHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( XmlDeclHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( StartDoctypeDeclHandler );
IMPLEMENT_COMMON_ENABLE_FUNCTION( EndDoctypeDeclHandler );

#undef IMPLEMENT_COMMON_ENABLE_FUNCTION

// ------------------------------------------------------------------
// Desc: Enable/Disable the element handlers
// ------------------------------------------------------------------

void XmlParser::EnableElementHandler( bool _isEnable )
{
    ex_assert( m_pParser, "m_pParser is not create" );
    EnableStartElementHandler(_isEnable);
    EnableEndElementHandler(_isEnable);
}

// ------------------------------------------------------------------
// Desc: Enable/Disable the CDATA section handlers
// ------------------------------------------------------------------

void XmlParser::EnableCdataSectionHandler ( bool _isEnable )
{
    ex_assert( m_pParser, "m_pParser is not create" );
    EnableStartCdataSectionHandler (_isEnable);
    EnableEndCdataSectionHandler (_isEnable);
}

// ------------------------------------------------------------------
// Desc: Enable/Disable default handler
// ------------------------------------------------------------------

void XmlParser::EnableDefaultHandler ( bool _isEnable, bool _isExpand )
{
    ex_assert( m_pParser, "m_pParser is not create" );
    if ( _isExpand )
        XML_SetDefaultHandlerExpand( m_pParser, _isEnable ? DefaultHandler : NULL );
    else
        XML_SetDefaultHandler( m_pParser, _isEnable ? DefaultHandler : NULL );
}

// ------------------------------------------------------------------
// Desc: Enable/Disable namespace handlers
// ------------------------------------------------------------------

void XmlParser::EnableNamespaceDeclHandler ( bool _isEnable )
{
    EnableStartNamespaceDeclHandler (_isEnable);
    EnableEndNamespaceDeclHandler (_isEnable);
}

// ------------------------------------------------------------------
// Desc: Enable/Disable the DOCTYPE declaration handler
// ------------------------------------------------------------------

void XmlParser::EnableDoctypeDeclHandler ( bool _isEnable )
{
    ex_assert( m_pParser, "m_pParser is not create" );
    EnableStartDoctypeDeclHandler (_isEnable);
    EnableEndDoctypeDeclHandler (_isEnable);
}



// #########################
} // end namespace ex 
// #########################


