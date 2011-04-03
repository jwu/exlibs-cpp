// ======================================================================================
// File         : TextFile.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:38:29 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TEXTFILE_H_1250523513
#define TEXTFILE_H_1250523513
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// include
///////////////////////////////////////////////////////////////////////////////

#include "PhysicalFile.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class TextFile
// 
// Purpose: 
// TODO: right now only support ASCII text file 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL TextFile : public PhysicalFile
{

    ///////////////////////////////////////////////////////////////////////////////
    // protected internal struct 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    ///////////////////////////////////////////////////////////////////////////////
    // class Buffer 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class Buffer
    {
    public:
        //
        Buffer( uint _bytes = 4096 )
        {
            resize( _bytes );
        }
        ~Buffer()
        {
            ex_free(m_pRawBuffer);
            m_pRawBuffer = NULL;
        }

        //
        void resize ( uint _bytes )
        {
            uint size = _bytes * sizeof(uint8);
            m_pRawBuffer = (uint8*)ex_realloc( m_pRawBuffer, size );
            ex::mem::zero( m_pRawBuffer, size );
            m_SizeInBytes = 0;
            m_Capacity = _bytes;
            m_Index = 0;
        }

        //
        void SetSize ( uint _bytes ) { m_SizeInBytes = _bytes; }

        //
        uint8 pop()
        {
            ex_assert( m_Index < m_SizeInBytes, "out of range!" );
            ex_assert( m_SizeInBytes <= m_Capacity, "out of capacity!" );
            uint8 result = m_pRawBuffer[m_Index++];
            return result;
        }

        //
        void push( uint8 _data )
        {
            ex_assert( m_Index < m_SizeInBytes, "out of range!" );
            ex_assert( m_SizeInBytes <= m_Capacity, "out of capacity!" );
            m_pRawBuffer[m_Index++] = _data;
            ++m_SizeInBytes;
        }

        //
        void reset() 
        {
            ex::mem::zero( m_pRawBuffer, m_Capacity * sizeof(uint8) );
            m_Index = 0;
            m_SizeInBytes = 0;
        }

        // 
        uint size () const { return m_SizeInBytes; }
        uint capacity () const { return m_Capacity; }
        uint8* ptr() const { return (m_pRawBuffer + m_Index); }
        bool empty() const { return m_Index == m_SizeInBytes; }
        bool Full() const { return m_SizeInBytes == m_Capacity; }

    protected:

        uint8*  m_pRawBuffer;
        uint    m_SizeInBytes; // in bytes
        uint    m_Capacity;
        uint    m_Index;
    }; // end struct Buffer

    ///////////////////////////////////////////////////////////////////////////////
    // public typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    enum EBufType
    {
        eBufType_reading = 0,
        eBufType_writing,
        eBufType_count
    }; // end EBufType

    //
    enum { DEFAULT_BUFFER_SIZE = 4096 };
    
    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    TextFile( const path_t& _name = path_t() );
    TextFile( const wpath_t& _name );
    virtual ~TextFile();
    void resizeBuffer ( TextFile::EBufType _eBufferType, uint _bytes = TextFile::DEFAULT_BUFFER_SIZE );

    //
    void writeline( const string_t& _line );
    result_t readline( string_t* _pLine );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    Buffer* m_buffers[eBufType_count];

}; // end class TextFile

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END TEXTFILE_H_1250523513
// #################################################################################
