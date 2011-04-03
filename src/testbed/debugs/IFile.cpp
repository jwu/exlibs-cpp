// ======================================================================================
// File         : IFile.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:21 AM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( IFile, fileid, off )
{
    ex::uint64 fileID = -1;
    ex::IFile::smart_ptr_t spFile;
    ex::r_path_t xml_file( "res://xml/Array.xml" );
    if ( ex::futil::file::exists(xml_file.rawfile()) )
    {
        fileID = ex::futil::file::fileID (xml_file.rawfile());
        ex_log("first time get fileID = %d\n", fileID );

        fileID = ex::futil::file::fileID (xml_file.rawfile());
        ex_log("second time get fileID = %d\n", fileID );

        spFile = ex::futil::file::readonly<ex::PhysicalFile> (xml_file.rawfile());
        fileID = ex::futil::file::fileID (xml_file.rawfile());
        ex_log("after readonly get fileID = %d\n", fileID );

        spFile = ex::futil::file::open<ex::PhysicalFile> (xml_file.rawfile());
        fileID = ex::futil::file::fileID (xml_file.rawfile());
        ex_log("after open exists get fileID = %d\n", fileID );

        EX_HW_BREAK();
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( IFile, readline, off )
{
    ex::r_path_t txt_file( "res://txt/bible.txt" );
    ex::TextFile bible(txt_file.rawfile());
    // ex::TextFile bible("TestFile.txt");
    if ( bible.open(ex::futil::access::read) )
    {
        ex::string_t line;
        while ( bible.readline( &line ) != ex::EResult::end_of_file )
        {
            // printf ( "%s", line.c_str() );
            ex::Array<ex::string_t> arr;
            ex::str::splitIntoArray( " ", line.c_str(), &arr );

            for ( int i = 0; i < (int)arr.size(); ++i )
            {
                ex::string_id_t id( arr[i].c_str() );
            }
        }
        bible.close();

        ex::IFile::smart_ptr_t spFile = ex::futil::file::open<ex::PhysicalFile>("./result.txt");
        if ( spFile )
        {
            ex::string_t text( (ex::string_id_t::GetStringTable()).to_str<ex::dec>() );
            spFile->write( text.c_str(), (ex::uint32)text.size() );
            spFile->close();
        }
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( IFile, FileMng, off )
{
    ex::IFile::smart_ptr_t spFile = ex::futil::file::open<ex::PhysicalFile>("./result.txt");
    if ( spFile )
    {
        ex::string_t text("find it\n");
        spFile->write( text.c_str(), (ex::uint32)text.size() );
        spFile->close();
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( IFile, write, off )
{
    ex::PhysicalFile file("./TestFile.txt"); 
    if ( file.open() )
    {
        const int size = 256;
        char buffer[size] = "Hello Word!\n";
        file.write( (void*)buffer, size );
        file.close();
    }
}
