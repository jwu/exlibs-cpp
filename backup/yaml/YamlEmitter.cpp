// ======================================================================================
// File         : YamlEmitter.cpp
// Author       : Wu Jie 
// Last Change  : 10/09/2009 | 22:26:22 PM | Friday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "YamlEmitter.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

static int yaml_write_handler ( void* _pData, unsigned char* _pBuffer, size_t _size )
{
    IFile::smart_ptr_t spFile = *(static_cast<IFile::smart_ptr_t*>(_pData));
    uint written = spFile->write ( _pBuffer, uint(_size) );

    ex_assert ( written == _size, "failed to write file" );
    if ( written != _size )
        return 0;
    return 1;
}

// ######################### 
} // end namespace _private 
// ######################### 


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlEmitter::CYamlEmitter ()
    : m_Encoding ( eEncoding_UTF8 )
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CYamlEmitter::~CYamlEmitter ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void CYamlEmitter::AddChild ( const CYamlNode::smart_ptr_t& _spNode )
{
    m_Children.PushBack (_spNode);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlEmitter::SaveToFile ( const char* _fileName ) const
{
    result_t result_t = eResult_OK;

    IFile::smart_ptr_t spFile = futil::file::replace<CPhysicalFile>(_fileName);
    if ( spFile )
    {
        eResult = this->SaveToFile ( spFile );
    }
    else
    {
        eResult = eResult_CreateFailed;
    }
    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlEmitter::SaveToFile ( IFile::smart_ptr_t _spFile ) const
{
    result_t result_t = eResult_OK;
    yaml_emitter_t emitter;

    //
    int result = yaml_emitter_initialize(&emitter); 
    ex_assert( result, "failed to initialize yaml emitter." );

    //
    // TODO { 
    bool useCanonical = 0;
    bool useUnicode = 0;
    if ( useCanonical ) 
    {
        yaml_emitter_set_canonical ( &emitter, 1 );
    }
    if ( useUnicode ) 
    {
        yaml_emitter_set_unicode ( &emitter, 1 );
    }
    // } TODO end 

    // DELME { 
    // static const uint BUFFER_SIZE = 65536; 
    // size_t written = 0;
    // uint8 buffer[BUFFER_SIZE];
    // memset(buffer, 0, BUFFER_SIZE);
    // yaml_emitter_set_output_string ( &emitter, buffer, BUFFER_SIZE, &written );
    // } DELME end 

    yaml_emitter_set_output ( &emitter, _private::yaml_write_handler, &(_spFile) );

    // save stream start event
    ex_check_return ( SaveStreamStart ( emitter ), "save stream start failed." );

    //
    for ( yaml_nodes_t::ConstIterator iter = m_Children.Begin(); iter != m_Children.End(); ++iter )
    {
        eResult = (*iter)->SaveToFile ( &emitter ); 
        if ( eResult != eResult_OK )
            break;
    }

    // save stream end event
    ex_check_return ( SaveStreamEnd ( emitter ), "save stream end failed." );

    //
    yaml_emitter_delete(&emitter);

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlEmitter::SaveStreamStart ( yaml_emitter_t& _emitter ) const
{
    result_t result_t = eResult_OK;

    yaml_event_t event;
    yaml_stream_start_event_initialize ( &event, GetEncoding(m_Encoding) );
    yaml_emitter_emit ( &_emitter, &event ) || yaml_emitter_flush ( &_emitter );

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CYamlEmitter::SaveStreamEnd ( yaml_emitter_t& _emitter ) const
{
    result_t result_t = eResult_OK;

    yaml_event_t event;
    yaml_stream_end_event_initialize ( &event );
    yaml_emitter_emit ( &_emitter, &event ) || yaml_emitter_flush ( &_emitter );

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

yaml_encoding_t CYamlEmitter::GetEncoding ( const CYamlEmitter::EEncoding& _encoding )
{
    switch ( _encoding )
    {
    case eEncoding_UTF8:
        return YAML_UTF8_ENCODING;

    case eEncoding_UTF16LE:
        return YAML_UTF16LE_ENCODING;

    case eEncoding_UTF16BE:
        return YAML_UTF16BE_ENCODING;

    default:
        return YAML_UTF8_ENCODING; 
    }
}

// ######################### 
} // end namespace ex 
// ######################### 


