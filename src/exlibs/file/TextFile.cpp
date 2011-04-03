// ======================================================================================
// File         : TextFile.cpp
// Author       : Wu Jie 
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "TextFile.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// member function defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TextFile::TextFile( const path_t& _path )
    : PhysicalFile(_path)
{
    m_buffers[eBufType_reading] = NULL;
    m_buffers[eBufType_writing] = NULL;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TextFile::TextFile( const wpath_t& _path )
    : PhysicalFile(_path)
{
    m_buffers[eBufType_reading] = NULL;
    m_buffers[eBufType_writing] = NULL;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TextFile::~TextFile()
{
    for ( uint i = 0; i < uint(eBufType_count); ++i )
    {
        if ( m_buffers[i] != NULL )
        {
            ex_delete(m_buffers[i]);
            m_buffers[i] = NULL;
        }
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TextFile::resizeBuffer ( TextFile::EBufType _eBufferType, uint _bytes )
{
    TextFile::Buffer* pBuffer = m_buffers[_eBufferType]; 

    if ( pBuffer == NULL )
    {
        pBuffer = ex_new Buffer(_bytes); 
		m_buffers[_eBufferType] = pBuffer;
    }
    else
    {
        pBuffer->resize(_bytes);
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TextFile::writeline( const string_t& _line )
{
    string_t line( _line + '\n' );
    PhysicalFile::write( static_cast<const void*>( line.c_str() ), uint(line.size()) );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t TextFile::readline( string_t* _pLine )
{
    // if buffer is not created, use default size create one
    if ( m_buffers[eBufType_reading] == NULL )
        this->resizeBuffer(eBufType_reading);

    TextFile::Buffer* pBuffer = m_buffers[eBufType_reading]; 

    // If we still have data in buffer, read it first
    bool finish = false;
    uint8* pStart = NULL;
    uint8* pEnd = NULL;

    // ensure that result line is empty
    _pLine->clear();

    //
    while ( !finish )
    {
        // get current buffer pointer position as start point
        pStart = pBuffer->ptr();

        // if buffer not empty, read it until empty or until we meet the end line character
        while ( !pBuffer->empty() )
        {
            char data = pBuffer->pop();
            if ( data == '\n' )
            {
                finish = true;
                break;
            }
        }

        // after reading get current buffer pointer position as start point
        pEnd = pBuffer->ptr();

        // read the buffer data to pData we allocate
        if ( pStart != pEnd )
        {
            _pLine->append( (char*)pStart, (char*)pEnd );
        }

        // if we meet end line character, end up the process and return the data we got.
        if ( finish )
        {
            break;
        }
        else // else we reset the buffer and read data from disk file
        {
            pBuffer->reset();
            futil::sz_t bytesRead = this->read( pBuffer->ptr(), pBuffer->capacity() );
            pBuffer->SetSize(uint(bytesRead));

            // if we read all things, directly return false, to tell that we are finished
            if ( bytesRead == 0 && (futil::sz_t)this->tell() == this->size() )
                return EResult::end_of_file;
        }
    }

    return EResult::ok;
}

// #########################
} // end namespace ex 
// #########################

