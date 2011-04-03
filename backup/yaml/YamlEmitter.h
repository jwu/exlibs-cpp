// ======================================================================================
// File         : YamlEmitter.h
// Author       : Wu Jie 
// Last Change  : 10/09/2009 | 21:54:33 PM | Friday,October
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef YAMLEMITTER_H_1255096500
#define YAMLEMITTER_H_1255096500
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "YamlNode.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class CYamlEmitter 
// 
// Purpose: 
//
// NOTE: the yaml mapping emitter is order independence, this make it weak to be a serialize format.
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL CYamlEmitter
{
    typedef CYamlEmitter self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Array<CYamlNode::smart_ptr_t> yaml_nodes_t; 

    enum EEncoding
    {
        eEncoding_UTF8,
        eEncoding_UTF16LE,
        eEncoding_UTF16BE,
    }; // end enum EEncoding 

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    CYamlEmitter ();
    ~CYamlEmitter ();

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // 
    result_t SaveToFile ( const char* _fileName ) const;
    result_t SaveToFile ( IFile::smart_ptr_t _spFile ) const;

    //
    void AddChild ( const CYamlNode::smart_ptr_t& _spNode );
    void SetEncoding ( const CYamlEmitter::EEncoding& _encoding ) { m_Encoding = _encoding; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    static yaml_encoding_t GetEncoding ( const CYamlEmitter::EEncoding& _encoding );

    //
    result_t SaveStreamStart ( yaml_emitter_t& _emitter ) const;
    result_t SaveStreamEnd ( yaml_emitter_t& _emitter ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    EEncoding     m_Encoding;
    yaml_nodes_t  m_Children;

}; // end class CYamlEmitter

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END YAMLEMITTER_H_1255096500
// #################################################################################


