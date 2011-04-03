// ======================================================================================
// File         : fsys.cpp
// Author       : Wu Jie 
// Last Change  : 04/13/2010 | 09:31:16 AM | Tuesday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "fsys.h"

///////////////////////////////////////////////////////////////////////////////
// macros
///////////////////////////////////////////////////////////////////////////////

#define foreach_child_begin( _it_node, _children ) \
    for ( fsys::name_to_node_t::iterator _it_node = (_children).begin(); _it_node != (_children).end(); ++_it_node )  \
    { \

#define foreach_child_end() \
    }

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace fsys { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// private 
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

    // variables 

    // general
    bool initialized = false;

    // repositories
    repository_t* repos = NULL;
    typedef HashMap<string_id_t,repository_t*> name_to_repo_t;
    name_to_repo_t* repo_table = NULL;

    // rtype-table
    typedef HashMap<string_id_t,string_id_t> src_to_rtype_t;
    src_to_rtype_t* src_to_rtype;

    // functions

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    path_t to_fullpath ( const path_t& _root_folder, const r_path_t& _path )
    {
        r_path_t::pair_t path_pair = _path.splitRepo ();
        const repository_t* repo = fsys::repo ( string_id_t( path_pair.first.c_str() ) );
        if ( repo )
        {
            return repo->path + _root_folder + path_pair.second;
        }
        return path_t("");
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    fnode_t* new_fnode ( fnode_t* _parent, const string_id_t& _name, const string_id_t& _type )
    {
        fnode_t* node = ex_new fnode_t();
        node->name = _name;
        node->type = _type;
        node->size = 0;
        node->entry = 0;
        node->parent = _parent;

        if ( _parent ) {
            _parent->children[_name] = node;
        }

        return node;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    result_t remove_from_parent ( const fnode_t* _node )
    {
        fsys::name_to_node_t::iterator it_node = _node->parent->children.find ( _node->name );
        if ( it_node != _node->parent->children.end() ) {
            _node->parent->children.erase (it_node);
            return EResult::ok;
        }
        return EResult::not_found;
    }

    // ------------------------------------------------------------------ 
    // Desc:
    // ------------------------------------------------------------------ 

    void delete_fnode ( fnode_t* _node, bool _notifyParent = true )
    {
        ex_assert_return ( _node, /*void*/, "_node is NULL, something must be wrong!" );

        // recursivelly delete childs.
        foreach_child_begin ( it_node, _node->children )
            delete_fnode (*it_node,false); // NOTE: when remove child, don't notify parent, which will lead to children table crush.
        foreach_child_end ()

        // root-node parent is NULL
        if ( _notifyParent ) {
            if ( _node->parent ) 
            {
                if ( _private::remove_from_parent(_node) != EResult::ok )
                {
                    ex_error ( "parent node don't have current node. something must be wrong!\n"
                               "something must be wrong! cur-node name: %s, type: %s", 
                               _node->name.c_str(), 
                               _node->type.c_str() );
                }
            }
            else 
            {
                ex_error ( "parent node is NULL. something must be wrong!\n"
                           "only root node's parent is NULL, and when it delete, it never notify parent.\n"
                           "something must be wrong! cur-node name: %s, type: %s", 
                           _node->name.c_str(), 
                           _node->type.c_str() );
            }
        }

        // now delete the node.
        ex_delete (_node);
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    fnode_t* add_fnode_in ( fnode_t* _node, const string_id_t& _name, bool _isFolder )
    {
        name_to_node_t::iterator it_node = _node->children.find(_name);
        if ( it_node != _node->children.end() )
        {
            return *it_node;
        }
        else
        {
            // get resource type by ext-name. 
            string_id_t resType = string_id_t::null;
            if ( _isFolder == false )
            {
                path_t ext_name = path_t(_name.c_str()).splitExt().second;
                string_id_t ext_name_id = string_id_t(ext_name.c_str());
                _private::src_to_rtype_t::iterator it_resType = _private::src_to_rtype->find(ext_name_id);
                if ( it_resType == _private::src_to_rtype->end() ) // if not in reigstered res-type, skip it.
                    return NULL;
                resType = *it_resType;
            }
            else
                resType = string_id_t::s_folder;

            fnode_t* node = _private::new_fnode( _node, _name, resType );
            return node;
        }
        return NULL;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    uint do_local_explore ( fnode_t* _parent, const path_t& _path, bool _recursively );
    // ------------------------------------------------------------------ 

    fnode_t* add_fnode ( const r_path_t& _path, bool _isFolder )
    {
        // split the path to repo and path-name
        r_path_t::pair_t path_pair = _path.splitRepo();

        // get repo
        const repository_t* cur_repo = fsys::repo( string_id_t(path_pair.first.c_str()) );
        if ( cur_repo == NULL )
            return NULL;

        //
        if ( cur_repo->mode != fsys::mode::local )
        {
            ex_warning ("add resource can only work under local-mode");
            return NULL;
        }

        //
        Array<string_t> arr;
        str::splitIntoArray ( "/", path_pair.second.c_str(), &arr ); 
        if ( arr.empty() )
            arr.push_back(path_pair.second.c_str());

        //
        fnode_t* node = cur_repo->root;
        for ( Array<string_t>::iterator iter = arr.begin(); iter != arr.end(); ++iter )
        {
            // if this is the last section, it is a file
            bool isFile = false;
            if ( _isFolder == false && iter == arr.end() - 1 )
                isFile = true;

            // always add as folder
            node = _private::add_fnode_in ( node, string_id_t((*iter).c_str()), !isFile );
            if ( node == NULL )
                return NULL;
        }

        // it the node we add is a folder. add the files under it as sub-node
        if ( node != NULL && _isFolder )
        {
            path_t src_path = fsys::dir::srcpath(_path);
            _private::do_local_explore ( node, src_path, false ); // only expand the first-level
        }

        // 
        return node;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    fnode_t* find_fnode_in ( fnode_t* _node, const string_id_t& _name )
    {
        name_to_node_t::iterator it_node = _node->children.find(_name);
        if ( it_node != _node->children.end() )
        {
            return *it_node;
        }
        return NULL;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    fnode_t* find_fnode ( const r_path_t& _resPath )
    {
        // split the path to repo and path-name
        r_path_t::pair_t path_pair = _resPath.splitRepo();

        //
        Array<string_t> arr;
        str::splitIntoArray ( "/", path_pair.second.c_str(), &arr ); 
        if ( arr.empty() )
            arr.push_back(path_pair.second.c_str());

        // get repo
        const repository_t* cur_repo = fsys::repo( string_id_t(path_pair.first.c_str()) );
        if ( cur_repo == NULL )
            return NULL;

        //
        fnode_t* node = cur_repo->root;
        for ( Array<string_t>::iterator iter = arr.begin(); iter != arr.end(); ++iter )
        {
            node = find_fnode_in ( node, string_id_t((*iter).c_str()) );
            if ( node == NULL )
                break;
        }
        // if found the node, return it!
        if ( node )
            return node;

        return NULL;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    fnode_t* check_fnode ( const r_path_t& _path, bool _isFolder, bool _syncWithLocal = true )
    {
        fnode_t* node = _private::find_fnode (_path);
        if ( node != NULL )
        {
            // check if it is a folder
            if ( _isFolder && node->type == string_id_t::s_folder )
                return node;
            // check if it is a file.
            if ( !_isFolder && node->type != string_id_t::s_folder )
                return node;
            // this is not the node we want.
            return NULL;
        }

        // get repo
        const repository_t* cur_repo = fsys::repo( string_id_t(_path.repoName().c_str()) );
        if ( cur_repo == NULL )
            return NULL;

        // if we are in local mode, check the node in physical disk
        if ( cur_repo->mode == fsys::mode::local && _syncWithLocal )
        {
            //
            bool exists = false; 
            if ( _isFolder )
                exists = futil::dir::exists( fsys::dir::srcpath(_path) );
            else
                exists = futil::file::exists( fsys::file::srcpath(_path) );

            //
            if ( exists == false && node != NULL ) // if the file is not exists in the disk, but have the node. delete the node...
            {
                _private::delete_fnode (node);
                return NULL;
            }
            else if ( exists == true && node == NULL ) // if the file exists but node not exits, add the node...
            {
                node = _private::add_fnode (_path,_isFolder);
            }
        }

        // TODO: update status???

        //
        return node;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    bool remove_fnode ( const r_path_t& _path, bool _isFolder )
    {
        // split the path to repo and path-name
        r_path_t::pair_t path_pair = _path.splitRepo();

        // get repo
        const repository_t* cur_repo = fsys::repo( string_id_t(path_pair.first.c_str()) );
        if ( cur_repo == NULL )
            return false;

        //
        if ( cur_repo->mode != fsys::mode::local )
        {
            ex_warning ("add resource can only work under local-mode");
            return false;
        }

        // get the fnode
        fnode_t* node = check_fnode ( _path, _isFolder, false ); // don't sync with local.
        if ( node != NULL ) {
            delete_fnode ( node );
            return true;
        }
        return false;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    repository_t* repo ( fnode_t* _node )
    {
        fnode_t* cur_root = _node;
        // get the root node
        while ( cur_root->name != string_id_t::s___root__ ) {
            cur_root = cur_root->parent;
        }
        // loop all repo to check the root
        repository_t* cur_repo = _private::repos;
        while ( cur_repo )
        {
            if ( cur_repo->root == cur_root )
                return cur_repo;
            cur_repo = cur_repo->next;
        }
        return NULL;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    uint do_local_explore ( fnode_t* _parent, const path_t& _path, bool _recursively = true )
    {
        uint count = 0;

        //
        Array<path_t> names;
        if ( futil::glob( _path, &names ) != EResult::ok  )
        {
            ex_warning ( "failed to glob path %s", _path.c_str() );
            return 0;
        }

        //
        for ( Array<path_t>::iterator iter = names.begin(); iter != names.end(); ++iter )
        {
            path_t full_path = _path + *iter;
            bool is_dir = futil::isdir( full_path );
            path_t base_name = (*iter);
            path_t ext_name = "";
            if ( is_dir == false ) {
                path_t::pair_t name_pair = (*iter).splitExt();
                base_name = name_pair.first;
                ext_name = name_pair.second;
            }

            // if the extname is NULL, and it is not a dir, skip it.
            if ( ext_name == "" && is_dir == false ) {
                continue;
            }

            // get resource type by ext-name. 
            string_id_t ext_name_id = string_id_t(ext_name.c_str());
            _private::src_to_rtype_t::iterator it_resType = _private::src_to_rtype->find(ext_name_id);
            if ( it_resType == _private::src_to_rtype->end() ) // if not in reigstered res-type, skip it.
                continue;

            // create new node.
            fnode_t* node = _private::new_fnode( _parent, string_id_t((*iter).c_str()), *it_resType );

            // if this is a dir, recursively explore it.
            uint file_count = 1; // if not dir, counted as one file
            if ( is_dir && _recursively) {
                file_count = _private::do_local_explore( node, full_path);
                // DISABLE: keep emtpy folder { 
                // if ( file_count == 0 ) // if this is a empty directory, remove the node.
                // {
                //     _private::delete_fnode ( node );
                // }
                // } DISABLE end 
            }

            //
            count += file_count;
        }

        return count;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    uint do_remote_explore ( fnode_t* _parent, const path_t& _path )
    {
        // TODO:
        return 0;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    uint do_exfile_explore ( fnode_t* _parent, const path_t& _path )
    {
        // TODO: use header to establish the whole file-tree
        // TODO:
        // _private::_parent->size = ???;
        // _private::_parent->entry = ???;
        return 0;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    void debug_show ( fnode_t* _node, uint _level )
    {
        string_t text = "";
        for ( uint i = 0; i < _level; ++i )
        {
            text += "| ";
        }
        ex_log("%s|-[%s] %s", text.c_str(), _node->type.c_str() ? _node->type.c_str() : "\n", _node->name.c_str() );

        // recursivelly delete childs.
        foreach_child_begin ( it_node, _node->children )
            _private::debug_show ( *it_node, _level + 1 );
        foreach_child_end ()
    }

// ######################### 
} // end namespace _private 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// general
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t init ()
{
    if ( _private::initialized == false )
    {
        // create repository table if we don't have.
        if ( _private::repo_table == NULL ) {
            _private::repo_table = ex_new _private::name_to_repo_t();
        }

        // create src to rtype table
        if ( _private::src_to_rtype == NULL ) {
            _private::src_to_rtype = ex_new _private::src_to_rtype_t();
        }

        // reset repo, src_to_rtype.
        fsys::reset();

        _private::initialized = true;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t deinit ()
{
    if ( _private::initialized )
    {
        unmountAll ();
        ex_safe_delete(_private::repo_table);
        ex_safe_delete(_private::src_to_rtype);

        _private::initialized = false;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool initialized ()
{
    return _private::initialized;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t register_ftype ( const string_id_t& _srcExt, const string_id_t& _resType, bool _override )
{
    string_id_t ext = _srcExt;
    ex_assert_return( _private::src_to_rtype, EResult::failed, "src_to_rtype is NULL, pls call fsys::init first" );

    _private::src_to_rtype_t::iterator iter = _private::src_to_rtype->find ( ext );
    if ( iter != _private::src_to_rtype->end() ) 
    {
        if ( _override == false )
            return EResult::already_existed;
        *iter = _resType; 
    }
    else
    {
        _private::src_to_rtype->insert ( ext, _resType );
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t unregister_ftype ( const string_id_t& _srcExt )
{
    result_t eResult = EResult::ok;

    // unregister src to rtype
    _private::src_to_rtype_t::iterator it_type = _private::src_to_rtype->find ( _srcExt );
    if ( it_type != _private::src_to_rtype->end() ) {
        _private::src_to_rtype->erase(it_type);
    }
    else {
        eResult = EResult::not_found;
    }

    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void reset ()
{
    ex_assert_return( _private::repo_table, /*void*/, "repo_table is NULL, pls call fsys::init first" );
    ex_assert_return( _private::src_to_rtype, /*void*/, "src_to_rtype is NULL, pls call fsys::init first" );

    //
    unmountAll();

    //
    _private::src_to_rtype->clear();
    fsys::register_ftype ( string_id_t::null, string_id_t::s_folder ); // folder type
    fsys::register_ftype ( string_id_t("xml"), string_id_t::s_config ); // TODO: this relate with core::config()
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void unmountAll ()
{
    repository_t* cur_repo = _private::repos;
    while ( cur_repo )
    {
        _private::delete_fnode ( cur_repo->root, false );
        // TODO: do we need close file-handle in exrepo mode ???
        ex_delete (cur_repo);
        cur_repo = cur_repo->next;
    }
    _private::repos = NULL;
    _private::repo_table->clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t unmount ( const string_id_t& _name )
{
    //
    _private::name_to_repo_t::iterator iter = _private::repo_table->find(_name);
    if ( iter == _private::repo_table->end() )
        return EResult::not_found;

    // unmount the repo from list
    // if this is the first repo, reset the repo-start-token
    if ( (*iter)->prev == NULL ) {
        _private::repos = (*iter)->next;
    }
    else {
        (*iter)->prev->next = (*iter)->next;
    }
    if ( (*iter)->next ) {
        (*iter)->next->prev = (*iter)->prev;
    }

    // erase the repo from the repo-table
    _private::repo_table->erase(iter);

    //
    _private::delete_fnode ( (*iter)->root, false );
    // TODO: do we need close file-handle in exrepo mode ???
    ex_delete ((*iter));

    ex_log("unmounted repo %s\n", _name.c_str());
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

repository_t* mount ( const path_t& _path, const string_id_t& _name )
{
    _private::name_to_repo_t::iterator iter = _private::repo_table->find(_name);
    if ( iter != _private::repo_table->end() )
        return *iter;

    fsys::mode::Enum repo_mode = fsys::mode::unknown;
    if ( futil::file::exists( path_t(_path + path_t(_name.c_str()) + ".exrepo") ) )
    {
        repo_mode = fsys::mode::exrepo;
    }
    else if ( futil::dir::exists(_path) )
    {
        repo_mode = fsys::mode::local;
    }
    // TODO: remote repo should use be impl { 
    // else if ( futil::remote::exists(_path) )
    // {
    //     repo_mode = fsys::mode::remote;
    // }
    // } TODO end 

    // if we don't found exists repo, return NULL
    if ( repo_mode == fsys::mode::unknown )
    {
        return NULL;
    }

    // if we don't found the repo, create and mount it at the end.
    repository_t* repo = ex_new repository_t; 
    repo->path = _path;
    repo->name = _name;
    repo->root = _private::new_fnode( NULL, string_id_t::s___root__, string_id_t::s_folder );
    repo->mode = repo_mode;

    // mount the repo at the end of the repo-list
    if ( _private::repos == NULL )
    {
        _private::repos = repo;
        repo->next = NULL;
        repo->prev = NULL;
    }
    else
    {
        // get repos end
        repository_t* last_repo = _private::repos;
        repository_t* cur_repo = _private::repos;
        while ( cur_repo )
        {
            last_repo = cur_repo;
            cur_repo = cur_repo->next;
        }
        last_repo->next = repo;
        repo->prev = last_repo;
        repo->next = NULL;
    }
    (*_private::repo_table)[_name] = repo;

    ex_log("mounted repo %s from %s\n", _name.c_str(), _path.c_str() );

    //
    return repo;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t mount ( const string_id_t& _before, const string_id_t& _after )
{
    repository_t* repo_before = const_cast<repository_t*>(repo(_before));
    repository_t* repo_after = const_cast<repository_t*>(repo(_after));
    if ( repo_before == NULL || repo_after == NULL )
        return EResult::not_found;

    // already in the position we need.
    if ( repo_before->next == repo_after )
        return EResult::ok;

    // unmount the repo-after
    if ( repo_after->prev == NULL ) {
        _private::repos = repo_after->next;
    }
    else {
        repo_after->prev->next = repo_after->next;
    }
    if ( repo_after->next ) {
        repo_after->next->prev = repo_after->prev;
    }

    // mount after to before
    if ( repo_before->next ) {
        repo_after->next = repo_before->next;
        repo_before->next->prev = repo_after;
    }
    else
    {
        repo_after->next = NULL;
    }

    repo_after->prev = repo_before;
    repo_before->next = repo_after;

    //
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const repository_t* repo ( const path_t& _path )
{
    repository_t* cur_repo = _private::repos;
    while ( cur_repo )
    {
        if ( cur_repo->path == _path )
            return cur_repo;
        cur_repo = cur_repo->next;
    }
    return NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const repository_t* repo ( const string_id_t& _name )
{
    _private::name_to_repo_t::iterator iter = _private::repo_table->find(_name);
    if ( iter == _private::repo_table->end() )
        return NULL;
    return *iter;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void repo_names ( Array<string_t>* _result )
{
    ex_assert_return ( _result, /*void*/, "result array is NULL" );
    repository_t* cur_repo = _private::repos;
    while ( cur_repo )
    {
        _result->push_back(cur_repo->name.c_str());
        cur_repo = cur_repo->next;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void clear ( repository_t* _repo )
{
    // keep root node and recursivelly delete childs.
    foreach_child_begin ( it_node, _repo->root->children )
        _private::delete_fnode (*it_node,false);
    foreach_child_end ()
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint explore ( const path_t& _path, const path_t& _name )
{
    ex_assert_return( _private::repo_table, EResult::failed, "repo_table is NULL, pls call fsys::init first" );
    ex_assert_return( _private::src_to_rtype, EResult::failed, "src_to_rtype is NULL, pls call fsys::init first" );

    repository_t* repo = mount( _path, string_id_t(_name.c_str()) );
    fsys::clear( repo );

    //
    uint count = 0;
    if ( repo->mode == fsys::mode::local )
    {
        count = _private::do_local_explore ( repo->root, _path + path_t("src") );
    }
    else if ( repo->mode == fsys::mode::remote )
    {
        count = _private::do_remote_explore ( repo->root, _path );
    }
    else if ( repo->mode == fsys::mode::exrepo )
    {
        count = _private::do_exfile_explore ( repo->root, _path + _name + ".exrepo" );
    }

    return count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

r_path_t rpath ( fnode_t* _node )
{
    ex_assert_return( _node, r_path_t("://"), "node is NULL, invalid input" );
    fnode_t* cur_node = _node;
    string_t path = "";
    while ( cur_node->name != string_id_t::s___root__ ) // while the current node is not root.
    {
        path = cur_node->name.c_str() + string_t("/") + path;
        cur_node = cur_node->parent;
    }
    path = path.empty() ? path : path.substr( 0, path.size()-1 ); // stripe last slash "/"
    return r_path_t( _private::repo( cur_node )->name.c_str() + string_t("://") + path );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

string_id_t src_to_rtype ( const string_id_t& _srcExt )
{
    _private::src_to_rtype_t::iterator iter = _private::src_to_rtype->find (_srcExt);
    if ( iter != _private::src_to_rtype->end() )
        return *iter; 
    return string_id_t("unknown");
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void debug_show ()
{
    uint level = 0;

    // debug_show each repo
    repository_t* cur_repo = _private::repos;
    ex_log("===================================================\n");
    while ( cur_repo )
    {
        ex_log("repository: %s - %s\n", cur_repo->path.c_str(), cur_repo->name.c_str() );
        foreach_child_begin ( it_node, cur_repo->root->children )
            _private::debug_show ( *it_node, level + 1 );
        foreach_child_end ()
        cur_repo = cur_repo->next;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool isdir ( const r_path_t& _path )
{
    return fsys::dir::exists(_path);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool isfile ( const r_path_t& _path )
{
    return fsys::file::exists(_path);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t glob ( const r_path_t& _path, Array<r_path_t>* _pResult )
{
    fnode_t* node = _private::check_fnode (_path,true);
    if ( node == NULL )
        return EResult::not_found;

    foreach_child_begin ( it_node, node->children )
        _pResult->push_back ( _path + path_t ( (*it_node)->name.c_str() ) );
    foreach_child_end ()
    return EResult::ok; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t globFiles ( const r_path_t& _path, Array<r_path_t>* _pResult )
{
    fnode_t* node = _private::check_fnode (_path,true);
    if ( node == NULL )
        return EResult::not_found;

    foreach_child_begin ( it_node, node->children )
        if ( (*it_node)->type != string_id_t::s_folder ) // it is a file
            _pResult->push_back ( _path + path_t ( (*it_node)->name.c_str() ) );
    foreach_child_end ()
    return EResult::ok; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t globDirs ( const r_path_t& _path, Array<r_path_t>* _pResult )
{
    fnode_t* node = _private::check_fnode (_path,true);
    if ( node == NULL )
        return EResult::not_found;

    foreach_child_begin ( it_node, node->children )
        if ( (*it_node)->type == string_id_t::s_folder ) // it is a folder
            _pResult->push_back ( _path + path_t ( (*it_node)->name.c_str() ) );
    foreach_child_end ()
    return EResult::ok; 
}

///////////////////////////////////////////////////////////////////////////////
// fsys::file
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace file { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

path_t rawpath ( const r_path_t& _path )
{
    return _private::to_fullpath ( path_t("raw"), _path );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

path_t srcpath ( const r_path_t& _path )
{
    return _private::to_fullpath ( path_t("src"), _path );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

path_t binpath ( const r_path_t& _path )
{
    path_t bin_filepath = _private::to_fullpath ( path_t("bin"), _path );
    path_t::pair_t path_pair = bin_filepath.splitExt();

    // if we don't have src_ext
    if ( path_pair.second.empty() )
        return path_pair.first;

    return bin_filepath + ".exbin";
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool exists ( const r_path_t& _path )
{
    fnode_t* node = _private::check_fnode (_path, false);
    return node != NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

fnode_t* add_exists ( const r_path_t& _path )
{
    fnode_t* node = _private::check_fnode (_path, false);
    return node;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool remove ( const r_path_t& _path )
{
    return _private::remove_fnode (_path,false);
}

// ######################### 
} // end namespace file 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fsys::dir
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace dir { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

path_t rawpath ( const r_path_t& _path )
{
    return _private::to_fullpath ( path_t("raw"), _path );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

path_t srcpath ( const r_path_t& _path )
{
    return _private::to_fullpath ( path_t("src"), _path );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

path_t binpath ( const r_path_t& _path )
{
    return _private::to_fullpath ( path_t("bin"), _path );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool exists ( const r_path_t& _path )
{
    fnode_t* node = _private::check_fnode (_path, true);
    return node != NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

fnode_t* add_exists ( const r_path_t& _path )
{
    fnode_t* node = _private::check_fnode (_path, true);
    return node;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool remove ( const r_path_t& _path )
{
    return _private::remove_fnode (_path,true);
}


// ######################### 
} // end namespace dir 
// ######################### 

// ######################### 
} // end namespace fsys 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 

#undef foreach_child_begin
#undef foreach_child_end
