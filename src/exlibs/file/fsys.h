// ======================================================================================
// File         : fsys.h
// Author       : Wu Jie 
// Last Change  : 04/13/2010 | 09:18:35 AM | Tuesday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FSYS_H_1271121519
#define FSYS_H_1271121519
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "futil.h"
#include "../String/ResPath.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace fsys { 
// ######################### 

// NOTE: the limitation of the system is you can't have folder hello.src_ext and file hello.src_ext under
// the same path.

// seek
namespace mode {
    enum Enum
    {
        unknown = -1,
        exrepo,
        local,
        remote,
    }; // end enum Enum
}

//
struct _fnode;
typedef _fnode fnode_t;
typedef HashMap<string_id_t,fnode_t*> name_to_node_t;

// struct _fnode
struct _fnode
{
    string_id_t name;           // the fnode_t name. (with src_ext)
    string_id_t type;           // the type registered in ResourceMng
    futil::sz_t size;           // file size.
    futil::offset_t entry;      // the start address
    fnode_t* parent;            // parent node
    name_to_node_t children;    // children
}; // end struct _fnode

// NOTE: a local/remote repository will have 3 sub-directory (src,bin,raw) 
// struct _repository
struct _repository;
typedef _repository repository_t;
struct _repository
{
    mode::Enum mode;
    path_t path;         // can be local/remote path
    string_id_t name;    // the name of the exrepo, in local/remote mode it is the name you want to create.
    fnode_t* root;       // this is the entry point of the exact node.
    repository_t* prev;
    repository_t* next;
}; // end struct _repository

///////////////////////////////////////////////////////////////////////////////
// general
///////////////////////////////////////////////////////////////////////////////

// basic
EX_LIBS_DLL result_t init ();
EX_LIBS_DLL result_t deinit ();
EX_LIBS_DLL bool initialized ();
EX_LIBS_DLL result_t register_ftype ( const string_id_t& _srcExt, const string_id_t& _resType, bool _override = false );
EX_LIBS_DLL result_t unregister_ftype ( const string_id_t& _srcExt );
EX_LIBS_DLL void reset ();

// repository
EX_LIBS_DLL repository_t* mount ( const path_t& _path, const string_id_t& _name );
EX_LIBS_DLL result_t mount ( const string_id_t& _before, const string_id_t& _after );
EX_LIBS_DLL result_t unmount ( const string_id_t& _name );
EX_LIBS_DLL void unmountAll ();
EX_LIBS_DLL const repository_t* repo ( const path_t& _path );
EX_LIBS_DLL const repository_t* repo ( const string_id_t& _name );
EX_LIBS_DLL void repo_names ( Array<string_t>* _result );
EX_LIBS_DLL void clear ( repository_t* _repo );
EX_LIBS_DLL uint explore ( const path_t& _path, const path_t& _name );

// fnode
EX_LIBS_DLL r_path_t rpath ( fnode_t* _node );

// src ext to bin ext, res-type
EX_LIBS_DLL string_id_t src_to_rtype ( const string_id_t& _srcExt );

// DEBUG: used for console debug { 
EX_LIBS_DLL void debug_show ();
// } DEBUG end 

//
EX_LIBS_DLL bool isdir ( const r_path_t& _path );
EX_LIBS_DLL bool isfile ( const r_path_t& _path );
EX_LIBS_DLL result_t glob ( const r_path_t& _path, Array<r_path_t>* _pResult );
EX_LIBS_DLL result_t globFiles ( const r_path_t& _path, Array<r_path_t>* _pResult );
EX_LIBS_DLL result_t globDirs ( const r_path_t& _path, Array<r_path_t>* _pResult );

///////////////////////////////////////////////////////////////////////////////
// fsys::file
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace file { 
// ######################### 

    // NOTE: rawfile will reserve the original ext.
    EX_LIBS_DLL path_t rawpath ( const r_path_t& _path );
    EX_LIBS_DLL path_t srcpath ( const r_path_t& _path );
    // NOTE: binfile will change src ext to bin ext.
    EX_LIBS_DLL path_t binpath ( const r_path_t& _path );

    //
    EX_LIBS_DLL bool exists ( const r_path_t& _path );
    EX_LIBS_DLL fnode_t* add_exists ( const r_path_t& _path );
    EX_LIBS_DLL bool remove ( const r_path_t& _path );

// ######################### 
} // end namespace file 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fsys::dir
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace dir { 
// ######################### 

    // NOTE path convert in dir:: is similar with file::, but never try to change the ext.
    EX_LIBS_DLL path_t rawpath ( const r_path_t& _path );
    EX_LIBS_DLL path_t srcpath ( const r_path_t& _path );
    EX_LIBS_DLL path_t binpath ( const r_path_t& _path );

    //
    EX_LIBS_DLL bool exists ( const r_path_t& _path );
    EX_LIBS_DLL fnode_t* add_exists ( const r_path_t& _path );
    EX_LIBS_DLL bool remove ( const r_path_t& _path );

// ######################### 
} // end namespace dir 
// ######################### 

// ######################### 
} // end namespace fsys 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END FSYS_H_1271121519
// #################################################################################
