// ======================================================================================
// File         : Resource.cpp
// Author       : Wu Jie 
// Last Change  : 04/11/2010 | 09:21:10 AM | Sunday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class CTestResource 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class CTestResource : public Resource
{
    EX_DECL_RESOURCE ( CTestResource, Resource, "test", 1 )

    //
public:
    CTestResource ( const string_id_t& _resID ) 
        : base_t (_resID)
        , m_title ("Hello World!")
        , m_author ("Wu Jie")
        , m_article ("")
    {
    }
    virtual ~CTestResource ()
    {
    }

    //
    void showArticle ()
    {
        ex_log("%s\n", m_article.c_str() );
    }

    //
protected:
    virtual result_t autogen ( const Resource::files_t& _rawFiles ) 
    { 
        for ( ex::uint i = 0; i < _rawFiles.size(); ++i )
        {
            m_rawFiles.insert ( string_id_t("chapter-"+ex::to_str<dec>(i)), _rawFiles[i] );
        }
        m_title = "my article";
        m_author = "johnny";

        return EResult::ok; 
    }
    virtual result_t compile ( ISerializeNode* _pNode )
    {
        string_t text;
        text = text + "title: " + m_title + "\n";
        text = text + "author: " + m_author + "\n";

        //
        for ( file_map_t::c_iterator iter = this->rawFiles().begin(); iter != this->rawFiles().end(); ++iter )
        {
            //
            ex::path_t fullPath = (*iter).rawfile();
            IFile::smart_ptr_t spFile = futil::file::readonly<PhysicalFile>(fullPath);
            if ( spFile )
            {
                DataHolder dataHolder;
                dataHolder.alloc ( size_t(spFile->size()) );
                spFile->read( dataHolder.data(), spFile->size() );
                text += string_t( (const char*)(dataHolder.data()), dataHolder.size() );
            }
            else
            {
                ex_warning ( "autogen resource failed: file %s not found.", fullPath.c_str() );
                return EResult::not_found;
            }
        }

        EX_SERIALIZE ( _pNode, "text", text );
        return EResult::ok;
    }
    virtual result_t processData ( ISerializeNode& _node )
    {
        string_t text;
        EX_SERIALIZE ( &_node, "text", text );
        m_article = text;
        return EResult::ok;
    }
    virtual result_t reload ( ISerializeNode& _node )
    {
        return EResult::ok;
    }
    virtual result_t unload ()
    {
        return EResult::ok;
    }

    //
protected:

    string_t m_title;
    string_t m_author;
    string_t m_article;

}; // end class CTestResource

EX_DEF_PROPERTIES_BEGIN (CTestResource)
    EX_REGISTER_PROPERTY ( "title", m_title )
    EX_REGISTER_PROPERTY ( "author", m_author )
EX_DEF_PROPERTIES_END()

// ######################### 
} // end namespace ex 
// ######################### 


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( Resource, compile, off )
{
     EX_GP(ex::ResourceMng)->registerRes<ex::CTestResource>(true);

    ex::Resource::files_t rawFiles;
    rawFiles.push_back ( ex::r_path_t("res://chapters/chapter.01.txt") );
    rawFiles.push_back ( ex::r_path_t("res://chapters/chapter.02.txt") );
    rawFiles.push_back ( ex::r_path_t("res://chapters/chapter.03.txt") );
    rawFiles.push_back ( ex::r_path_t("res://chapters/chapter.04.txt") );

    EX_GP(ex::ResourceMng)->autogen ( ex::r_path_t("res://tests/my_article_01.test"), rawFiles );
    EX_GP(ex::ResourceMng)->autogen ( ex::r_path_t("res://tests/my_article_02.test"), rawFiles );

    ex::CTestResource::smart_ptr_t spRes = EX_GP(ex::ResourceMng)->getRes<ex::CTestResource>( ex::string_id_t("res://tests/my_article_02.test") );
    if (spRes)
    {
        spRes->showArticle();
    }

    EX_HW_BREAK();
}

