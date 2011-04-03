// ======================================================================================
// File         : XmlParser.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:27:54 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef XMLPARSER_H_1250526478
#define XMLPARSER_H_1250526478
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#ifndef XML_STATIC
#define XML_STATIC
#endif

#include <expat/include/expat.h>
#include "XmlNode.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class XmlParser 
// 
// Purpose: 
//              <example value = 1>"this is a example"</example>    
//                  |          |                |           |
// CXmlElement -  CXmlTag  XmlAttribute    CXmlText    CXmlTagEnd        
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL XmlParser
{

    ///////////////////////////////////////////////////////////////////////////////
    // public typedef 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef XmlParser self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    XmlParser();
    ~XmlParser();

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    XmlNode::smart_ptr_t Parse( const tchar* _pBuffer, int _len = -1, bool _isFinal = true );
    XmlNode::smart_ptr_t ParseFile( const char* _filename );
    XmlNode::smart_ptr_t ParseBuffer( int _len, bool _isFinal = true );

    //
	enum XML_Error GetErrorCode (); 
	int64 GetCurrentByteIndex (); 
	int GetCurrentLineNumber ();
	int GetCurrentColumnNumber (); 
	int GetCurrentByteCount (); 
	const char* GetInputContext ( int* _offset, int* _pSize );
	const tchar* GetErrorString (); 

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
	bool create ( const tchar* _encoding = NULL, const tchar* _sep = NULL );
	void destroy ();
	bool InternalParse ( const tchar* _pBuffer, int _len = -1, bool _isFinal = true );
    bool InternalParseFile ( const char* _filename );
	bool InternalParseBuffer( int _len, bool _isFinal = true );
	void* GetBuffer( int _len );

    //
	void OnPostCreate ();
	void OnStartElement ( const tchar* _pName, const char** _ppAttrs );
	void OnEndElement ( const tchar* _pName );
	void OnCharacterData ( const tchar* _pData, int _len );
	void OnProcessingInstruction ( const tchar* _pTarget, const tchar* _pData );
	void OnComment ( const tchar* _Data );
	void OnStartCdataSection ();
	void OnEndCdataSection ();
	void OnDefault ( const tchar* _Data, int _len );
	bool OnExternalEntityRef ( const tchar* _pContext, const tchar* _pBase, const tchar* _pSystemID, const tchar* _pPublicID );
	bool OnUnknownEncoding ( const tchar* _pName, XML_Encoding* _pInfo );
	void OnStartNamespaceDecl ( const tchar* _pPrefix, const tchar* _pURI );
	void OnEndNamespaceDecl ( const tchar* _pPrefix );
	void OnXmlDecl ( const tchar* _pVersion, const tchar* _pEncoding, int _isStandalone );
	void OnStartDoctypeDecl ( const tchar* _pDoctypeName, const tchar* _pSysID, const tchar* _pPubID, int _hasInternalSubset );
	void OnEndDoctypeDecl ();
    void OnParseError ();

    // Enable Functions
    void EnableStartElementHandler ( bool _isEnable = true );       
    void EnableEndElementHandler ( bool _isEnable = true );         
    void EnableCharacterDataHandler ( bool _isEnable = true );      
    void EnableProcessingInstructionHandler ( bool _isEnable = true ); 
    void EnableCommentHandler ( bool _isEnable = true );            
    void EnableStartCdataSectionHandler ( bool _isEnable = true );  
    void EnableEndCdataSectionHandler ( bool _isEnable = true );    
    void EnableStartNamespaceDeclHandler ( bool _isEnable = true ); 
    void EnableEndNamespaceDeclHandler ( bool _isEnable = true );   
    void EnableXmlDeclHandler ( bool _isEnable = true );            
    void EnableStartDoctypeDeclHandler ( bool _isEnable = true );   
    void EnableEndDoctypeDeclHandler ( bool _isEnable = true );     
	void EnableElementHandler( bool _isEnable = true );
	void EnableCdataSectionHandler ( bool _isEnable = true );
	void EnableDefaultHandler ( bool _isEnable = true, bool _isExpand = true );
	void EnableNamespaceDeclHandler ( bool _isEnable = true );
	void EnableDoctypeDeclHandler ( bool _isEnable = true );

    ///////////////////////////////////////////////////////////////////////////////
    // public static functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
	static const tchar* GetExpatVersion ();
	static void GetExpatVersion( int* _pMajor, int* _pMinor, int* _pMicro );
	static const tchar* GetErrorString( enum XML_Error _error );

    //
	static CDECL void StartElementHandler ( void* _pUserData, const tchar* _pName, const tchar** _ppAttrs );
	static CDECL void EndElementHandler ( void* _pUserData, const tchar* _pName );
	static CDECL void CharacterDataHandler ( void*  _pUserData, const tchar* _pData, int _len );
	static CDECL void ProcessingInstructionHandler ( void* _pUserData, const tchar* _pTarget, const tchar* _pData );
	static CDECL void CommentHandler ( void* _pUserData, const tchar* _pData );
	static CDECL void StartCdataSectionHandler ( void* _pUserData );
	static CDECL void EndCdataSectionHandler ( void* _pUserData );
	static CDECL void DefaultHandler ( void* _pUserData, const tchar* _pData, int _len );
	static CDECL void StartNamespaceDeclHandler ( void* _pUserData, const tchar* _pPrefix, const tchar* _pURI );
	static CDECL void EndNamespaceDeclHandler ( void* _pUserData, const tchar* _pPrefix );
	static CDECL void XmlDeclHandler ( void* _pUserData, const tchar* _pVersion, const tchar* _pEncoding, int _isStandalone );
	static CDECL void StartDoctypeDeclHandler ( void* _pUserData, const tchar* _pDoctypeName, const tchar* _pSysID, const tchar* _pPubID, int hasInternalSubset );
	static CDECL void EndDoctypeDeclHandler ( void* _pUserData );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

	XML_Parser		m_pParser;
    const char*     m_ParsingFileName;

    typedef Stack<XmlNode::smart_ptr_t> node_stack_t;
    node_stack_t                m_NodeStack;
    XmlNode::smart_ptr_t       m_Root;

}; // end class XmlParser

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END XMLPARSER_H_1250526478
// #################################################################################
