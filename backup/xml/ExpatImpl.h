// ======================================================================================
// File         : ExpatImpl.h
// Author       : Wu Jie 
// Last Change  : 12/04/2009 | 18:05:06 PM | Friday,December
// Description  : this class is based on article in 
//                  http://www.codeproject.com/KB/XML/expatimpl.aspx 
// NOTE: This file will not be used anymore. We write the implementation directly in XmlParser.cpp
// ======================================================================================

// #################################################################################
#ifndef EXPATIMPL_H_1250526445
#define EXPATIMPL_H_1250526445
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#ifndef XML_STATIC
#define XML_STATIC
#endif

#include <expat/include/expat.h>

// #########################
namespace ex { 
// #########################

// #########################
namespace _private { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class TExpatImpl 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <class T>
class TExpatImpl
{

    ///////////////////////////////////////////////////////////////////////////////
    // Constructors and destructors
    ///////////////////////////////////////////////////////////////////////////////

public:
	
    // ------------------------------------------------------------------
    // Desc: General constructor
    // ------------------------------------------------------------------

	TExpatImpl()
	{
		m_pParser = NULL;
	}

    // ------------------------------------------------------------------
    // Desc: Destructor
    // ------------------------------------------------------------------

	~TExpatImpl()
	{
		destroy();
	}

    ///////////////////////////////////////////////////////////////////////////////
    // Parser creation and deletion methods
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------
    // Desc: create a parser
    // ------------------------------------------------------------------

	bool create( const tchar* _encoding = NULL, const tchar* _sep = NULL )
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
		T* pThis = static_cast<T*>(this);
		pThis->OnPostCreate();

		// Set the user data used in callbacks
		XML_SetUserData( m_pParser, (void*)this );
		return true;
	}

    // ------------------------------------------------------------------
    // Desc: destroy the parser
    // ------------------------------------------------------------------

	void destroy()
	{
		if ( m_pParser != NULL )
			XML_ParserFree(m_pParser);
		m_pParser = NULL;
	}

    ///////////////////////////////////////////////////////////////////////////////
    // Parser parse methods
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------
    // Desc: Parse a block of data
    // ------------------------------------------------------------------

	bool Parse( const tchar* _pBuffer, int _len = -1, bool _isFinal = true )
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

    bool ParseFile( const char* _filename )
    {
        // load file to buffer. check if file exists
        if ( futil::file::exists(path_t(_filename)) )
        {
            ex_warning ( "%s not Existss.", _filename );
            return false;
        }

        IFile::smart_ptr_t spFile = futil::file::open<CPhysicalFile>(_filename);
        if ( spFile )
        {
            uint32 filesize = uint32(spFile->Size());
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
            bool bResult = ParseBuffer(bufferSize);
            m_ParsingFileName = NULL;

            // return result
            return bResult;
        }
        return false;
    }

    // ------------------------------------------------------------------
    // Desc: Parse internal buffer
    // ------------------------------------------------------------------

	bool ParseBuffer( int _len, bool _isFinal = true )
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

	void* GetBuffer( int _len )
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		return XML_GetBuffer( m_pParser, _len );
	}

    ///////////////////////////////////////////////////////////////////////////////
    // Parser callback enable/disable methods
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
#define IMPLEMENT_COMMON_ENABLE_FUNCTION( _name ) \
    void Enable##_name( bool _isEnable = true ) \
    { \
        ex_assert( m_pParser, "m_pParser is not create" ); \
        XML_Set##_name( m_pParser, _isEnable ? _name : NULL ); \
    }

    //
    IMPLEMENT_COMMON_ENABLE_FUNCTION( StartElementHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( EndElementHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( CharacterDataHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( ProcessingInstructionHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( CommentHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( StartCdataSectionHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( EndCdataSectionHandler );
    // IMPLEMENT_COMMON_ENABLE_FUNCTION( ExternalEntityRefHandler );
    // IMPLEMENT_COMMON_ENABLE_FUNCTION( UnknownEncodingHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( StartNamespaceDeclHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( EndNamespaceDeclHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( XmlDeclHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( StartDoctypeDeclHandler );
    IMPLEMENT_COMMON_ENABLE_FUNCTION( EndDoctypeDeclHandler );

    // ------------------------------------------------------------------
    // Desc: Enable/Disable the element handlers
    // ------------------------------------------------------------------

	void EnableElementHandler( bool _isEnable = true )
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		EnableStartElementHandler(_isEnable);
		EnableEndElementHandler(_isEnable);
	}

    // ------------------------------------------------------------------
    // Desc: Enable/Disable the CDATA section handlers
    // ------------------------------------------------------------------

	void EnableCdataSectionHandler ( bool _isEnable = true )
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		EnableStartCdataSectionHandler (_isEnable);
		EnableEndCdataSectionHandler (_isEnable);
	}

    // ------------------------------------------------------------------
    // Desc: Enable/Disable default handler
    // ------------------------------------------------------------------
	
	void EnableDefaultHandler ( bool _isEnable = true, bool _isExpand = true )
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

	void EnableNamespaceDeclHandler ( bool _isEnable = true )
	{
		EnableStartNamespaceDeclHandler (_isEnable);
		EnableEndNamespaceDeclHandler (_isEnable);
	}

    // ------------------------------------------------------------------
    // Desc: Enable/Disable the DOCTYPE declaration handler
    // ------------------------------------------------------------------

	void EnableDoctypeDeclHandler ( bool _isEnable = true )
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		EnableStartDoctypeDeclHandler (_isEnable);
		EnableEndDoctypeDeclHandler (_isEnable);
	}

#undef IMPLEMENT_COMMON_ENABLE_FUNCTION

    ///////////////////////////////////////////////////////////////////////////////
    // Parser error reporting methods
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------
    // Desc: Get last error
    // ------------------------------------------------------------------

	enum XML_Error GetErrorCode() 
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		return XML_GetErrorCode(m_pParser);
	}

    // ------------------------------------------------------------------
    // Desc: Get the current byte index
    // ------------------------------------------------------------------

	int64 GetCurrentByteIndex() 
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		return XML_GetCurrentByteIndex(m_pParser);
	}

    // ------------------------------------------------------------------
    // Desc: Get the current line number
    // ------------------------------------------------------------------

	int GetCurrentLineNumber() 
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		return XML_GetCurrentLineNumber(m_pParser);
	}

    // ------------------------------------------------------------------
    // Desc: Get the current column number
    // ------------------------------------------------------------------

	int GetCurrentColumnNumber() 
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		return XML_GetCurrentColumnNumber(m_pParser);
	}

    // ------------------------------------------------------------------
    // Desc: Get the current byte count
    // ------------------------------------------------------------------

	int GetCurrentByteCount () 
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		return XML_GetCurrentByteCount(m_pParser);
	}

    // ------------------------------------------------------------------
    // Desc: Get the input context
    // ------------------------------------------------------------------

	const char* GetInputContext ( int* _offset, int* _pSize )
	{
        ex_assert( m_pParser, "m_pParser is not create" );
		return XML_GetInputContext( m_pParser, _offset, _pSize );
	}

    // ------------------------------------------------------------------
    // Desc: Get last error string
    // ------------------------------------------------------------------

	const tchar* GetErrorString() 
	{
		return XML_ErrorString( GetErrorCode() );
	}

    ///////////////////////////////////////////////////////////////////////////////
    // Parser other methods
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------
    // Desc: Return the version string
    // ------------------------------------------------------------------

	static const tchar* GetExpatVersion ()
	{
		return XML_ExpatVersion();
	}

    // ------------------------------------------------------------------
    // Desc: Get the version information
    // ------------------------------------------------------------------

	static void GetExpatVersion( int* _pMajor, int* _pMinor, int* _pMicro )
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

	static const tchar* GetErrorString( enum XML_Error _error ) 
	{
		return XML_ErrorString(_error);
	}

    ///////////////////////////////////////////////////////////////////////////////
    // Public handler methods
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------
    // Desc: Start element handler
    // ------------------------------------------------------------------

	void OnStartElement ( const tchar* _pName, const char** _ppAttrs ) { return; }

    // ------------------------------------------------------------------
    // Desc: End element handler
    // ------------------------------------------------------------------

	void OnEndElement ( const tchar* _pName ) { return; }

    // ------------------------------------------------------------------
    // Desc: Character data handler
    // ------------------------------------------------------------------

	void OnCharacterData ( const tchar* _pData, int _len ) { return; }

    // ------------------------------------------------------------------
    // Desc: Processing instruction handler
    // ------------------------------------------------------------------

	void OnProcessingInstruction ( const tchar* _pTarget, const tchar* _pData ) { return; }

    // ------------------------------------------------------------------
    // Desc: Comment handler
    // ------------------------------------------------------------------

	void OnComment ( const tchar* _Data ) { return; }

    // ------------------------------------------------------------------
    // Desc: Start CDATA section handler
    // ------------------------------------------------------------------

	void OnStartCdataSection () { return; }

    // ------------------------------------------------------------------
    // Desc: End CDATA section handler
    // ------------------------------------------------------------------

	void OnEndCdataSection () { return; }

    // ------------------------------------------------------------------
    // Desc: Default handler
    // ------------------------------------------------------------------
	
	void OnDefault ( const tchar* _Data, int _len ) { return; }
	
    // ------------------------------------------------------------------
    // Desc: ext entity ref handler
    // ------------------------------------------------------------------
	
	bool OnExternalEntityRef ( const tchar* _pContext, const tchar* _pBase, const tchar* _pSystemID, const tchar* _pPublicID ) { return false; }
	
    // ------------------------------------------------------------------
    // Desc: Unknown encoding handler
    // ------------------------------------------------------------------
	
	bool OnUnknownEncoding ( const tchar* _pName, XML_Encoding* _pInfo ) { return false; }
	
    // ------------------------------------------------------------------
    // Desc: Start namespace declaration handler
    // ------------------------------------------------------------------
	
	void OnStartNamespaceDecl ( const tchar* _pPrefix, const tchar* _pURI ) { return; }
	
    // ------------------------------------------------------------------
    // Desc: End namespace declaration handler
    // ------------------------------------------------------------------
	
	void OnEndNamespaceDecl ( const tchar* _pPrefix ) { return; }
	
    // ------------------------------------------------------------------
    // Desc: XML declaration handler
    // ------------------------------------------------------------------

	void OnXmlDecl ( const tchar* _pVersion, const tchar* _pEncoding, bool _isStandalone ) { return; }

    // ------------------------------------------------------------------
    // Desc: Start DOCTYPE declaration handler
    // ------------------------------------------------------------------

	void OnStartDoctypeDecl ( const tchar* _pDoctypeName, const tchar* _pSysID, const tchar* _pPubID, bool _hasInternalSubset ) { return; }

    // ------------------------------------------------------------------
    // Desc: End DOCTYPE declaration handler
    // ------------------------------------------------------------------

	void OnEndDoctypeDecl () { return; }

    // ------------------------------------------------------------------
    // Desc: 
    // ------------------------------------------------------------------

    void OnParseError ()
    {
        fprintf( stderr, "%s Parse error at line %d: %s\n", m_ParsingFileName, GetCurrentLineNumber(), GetErrorString() );
        ex_error( "%s Parse error at line %d: %s\n", m_ParsingFileName, GetCurrentLineNumber(), GetErrorString() );
    }


    ///////////////////////////////////////////////////////////////////////////////
    // Protected methods
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // ------------------------------------------------------------------
    // Desc: Handle any post creation
    // ------------------------------------------------------------------

	void OnPostCreate () {} 

    ///////////////////////////////////////////////////////////////////////////////
    // Protected static methods
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // ------------------------------------------------------------------
    // Desc: Start element handler wrapper
    // ------------------------------------------------------------------

	static CDECL void StartElementHandler ( void* _pUserData, const tchar* _pName, const tchar** _ppAttrs )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnStartElement( _pName, _ppAttrs );
	}

    // ------------------------------------------------------------------
    // Desc: End element handler wrapper
    // ------------------------------------------------------------------

	static CDECL void EndElementHandler ( void* _pUserData, const tchar* _pName )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnEndElement( _pName );
	}

    // ------------------------------------------------------------------
    // Desc: Character data handler wrapper
    // ------------------------------------------------------------------

	static CDECL void CharacterDataHandler ( void*  _pUserData, const tchar* _pData, int _len )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnCharacterData( _pData, _len );
	}

    // ------------------------------------------------------------------
    // Desc: Processing instruction handler wrapper
    // ------------------------------------------------------------------

	static CDECL void ProcessingInstructionHandler ( void* _pUserData, const tchar* _pTarget, const tchar* _pData )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnProcessingInstruction( _pTarget, _pData );
	}

    // ------------------------------------------------------------------
    // Desc: Comment handler wrapper
    // ------------------------------------------------------------------

	static CDECL void CommentHandler ( void* _pUserData, const tchar* _pData )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnComment( _pData );
	}

    // ------------------------------------------------------------------
    // Desc: Start CDATA section wrapper
    // ------------------------------------------------------------------

	static CDECL void StartCdataSectionHandler ( void* _pUserData )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnStartCdataSection();
	}

    // ------------------------------------------------------------------
    // Desc: End CDATA section wrapper
    // ------------------------------------------------------------------

	static CDECL void EndCdataSectionHandler ( void* _pUserData )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnEndCdataSection();
	}

    // ------------------------------------------------------------------
    // Desc: Default wrapper
    // ------------------------------------------------------------------
	
	static CDECL void DefaultHandler ( void* _pUserData, const tchar* _pData, int _len )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnDefault( _pData, _len );
	}
	
    // XXX: disable this, different with others
    // ------------------------------------------------------------------
    // Desc: ext entity ref wrapper
    // ------------------------------------------------------------------
	
	// static CDECL int ExternalEntityRefHandler ( XML_Parser _parser, const tchar* _pContext, const tchar* _pBase, const tchar* _pSystemID, const tchar* _pPublicID ) 
    // {
	// 	T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
	// 	return pThis->OnExternalEntityRef( _pContext, _pBase, _pSystemID, _pPublicID ) ? 1 : 0;
	// }
	
    // XXX: disable this, different with others
    // ------------------------------------------------------------------
    // Desc: Unknown encoding wrapper
    // ------------------------------------------------------------------
	
	// static CDECL int UnknownEncodingHandler ( void* _pUserData, const tchar* _pName, XML_Encoding* _pInfo )
	// {
	// 	T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
	// 	return pThis->OnUnknownEncoding( _pName, _pInfo ) ? 1 : 0;
	// }
	
    // ------------------------------------------------------------------
    // Desc: Start namespace decl wrapper
    // ------------------------------------------------------------------

	static CDECL void StartNamespaceDeclHandler ( void* _pUserData, const tchar* _pPrefix, const tchar* _pURI )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnStartNamespaceDecl( _pPrefix, _pURI );
	}
	
    // ------------------------------------------------------------------
    // Desc: End namespace decl wrapper
    // ------------------------------------------------------------------
	
	static CDECL void EndNamespaceDeclHandler ( void* _pUserData, const tchar* _pPrefix )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnEndNamespaceDecl(_pPrefix);
	}
	
    // ------------------------------------------------------------------
    // Desc: XML declaration wrapper
    // ------------------------------------------------------------------

	static CDECL void XmlDeclHandler ( void* _pUserData, const tchar* _pVersion, const tchar* _pEncoding, bool _isStandalone )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnXmlDecl( _pVersion, _pEncoding, _isStandalone );
	}

    // ------------------------------------------------------------------
    // Desc: Start Doctype declaration wrapper
    // ------------------------------------------------------------------

	static CDECL void StartDoctypeDeclHandler ( void* _pUserData, const tchar* _pDoctypeName, const tchar* _pSysID, const tchar* _pPubID, bool hasInternalSubset )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnStartDoctypeDecl( _pDoctypeName, _pSysID, _pPubID, hasInternalSubset );
	}

    // ------------------------------------------------------------------
    // Desc: End Doctype declaration wrapper
    // ------------------------------------------------------------------

	static CDECL void EndDoctypeDeclHandler ( void* _pUserData )
	{
		T* pThis = static_cast<T*>( (TExpatImpl<T>*)_pUserData );
		pThis->OnEndDoctypeDecl();
	}

    ///////////////////////////////////////////////////////////////////////////////
    // Protected members
    ///////////////////////////////////////////////////////////////////////////////

protected:

	XML_Parser		m_pParser;
    const char*     m_ParsingFileName;
}; // end class TExpatImpl


// #########################
} // end namespace _private 
// #########################


// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END EXPATIMPL_H_1250526445
// #################################################################################
