// ======================================================================================
// File         : lua_global.cpp
// Author       : Wu Jie 
// Last Change  : 08/29/2010 | 17:11:50 PM | Sunday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "lua_inc.h"

#if EX_USE_LUA

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace lua { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// static defines
///////////////////////////////////////////////////////////////////////////////

static lua_State* s_L = NULL;
static wchar s_basePath[MAX_PATH];

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void check ( lua_State* _l, int status ) {
    if (status != 0) {
        lua_getglobal(_l, "_ALERT");
        if (lua_isfunction(_l, -1)) {
            lua_insert(_l, -2);
            lua_call(_l, 1, 0);
        }
        else {  /* no _ALERT function; print it on stderr */
            ex_error( "%s\n", lua_tostring(_l, -2) );
            lua_pop(_l, 2);  /* remove error message and _ALERT */
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// enhance 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int global_module ( lua_State* _l, const char* _key )
{
    lua_getglobal(_l, _key);

    if( !lua_istable(_l, -1) ) {
        lua_pop(_l, 1); // Pop the non-table.
        lua_newtable(_l);
        // cause lua_setglobal below will pop the top of the stack, 
        // and we will loose the table after the funciton call.
        // To prevent this, we duplicate the value at the top of the stack.
        lua_pushvalue(_l, -1);
        lua_setglobal(_l, _key);
    }

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int module ( lua_State* _l, int _idx, const char* _key )
{
    lua_getfield(_l, _idx, _key);

    // Create if necessary.
    if( !lua_istable(_l, -1) ) {
        lua_pop(_l, 1); // Pop the non-table.
        lua_newtable(_l);
        lua_pushvalue(_l, -1); // Duplicate the table to leave on top.
        lua_setfield(_l, -3, _key); // _key[_idx] = table
    }

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int get_module ( lua_State* _l, const char* _moduleName );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int parse ( lua_State* _l, int status )
{
    if (status == 0) {  /* parse OK? */
        status = lua_pcall(_l, 0, LUA_MULTRET, 0);  /* call main */
    }
    lua::check(_l, status);
    return status;
}

///////////////////////////////////////////////////////////////////////////////
// engine level
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void init ()
{
    ex::str::ncpy<wchar,MAX_PATH> (s_basePath, W("."), MAX_PATH);
    s_L = lua_open();
    luaL_openlibs(s_L);

    // we create global ex table if it not exists.
    lua::global_module ( lua::state(), "ex" );

    // init exlibs wraps
    lua::luaopen_core (lua::state());
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void deinit ()
{
    lua_close(s_L);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

lua_State* state () { return s_L; }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void set_base_path ( const wchar* _path ) {
    ex::str::ncpy<wchar,MAX_PATH> (s_basePath, _path, MAX_PATH);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

wchar* base_path () { return s_basePath; }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int load_module_byfile ( lua_State* _l, const wchar* _fullpath )
{
    wstring_t rel_wpath ( _fullpath );
    rel_wpath -= lua::base_path();

    char rel_path[1024];
    char* p = rel_path;
    ex::mem::zero( rel_path, 1024 );
    wchar_to_char<1024> ( rel_wpath.c_str(), rel_path );
    if ( rel_path[0] == '/' ) {
        p++;
    }
    char* dot = strrchr( p, '.' );
    int count = ex::str::len(p);
    if ( dot != NULL ) {
        count = dot - p;
    }
    char str[1024]; 
    ex::str::ncpy( str, 1024, p, count );
    str[count] = '\0';

    Array<string_t> str_list;
    ex::str::splitIntoArray ( "/", str, &str_list ); 

    string_t module_name;
    if ( str_list.size() > 1 ) {
        for ( Array<string_t>::iterator iter = str_list.begin(); iter != str_list.end()-1; ++iter ) {
            module_name = module_name + *iter + '.';
        }
        module_name = module_name + *(str_list.end()-1);
    }
    else {
        module_name = *(str_list.begin());
    }

    // now do the load
    if ( lua::load_module( _l, module_name.c_str() ) != 0 ) {
        ex_log ( "script module: %s loaded.\n", module_name.c_str() );
        return 1;
    }
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int load_module ( lua_State* _l, const char* _module )
{
    Array<string_t> str_list;
    ex::str::splitIntoArray ( ".", _module, &str_list ); 
    
    string_t rel_path;
    if ( str_list.size() > 1 ) {
        for ( Array<string_t>::iterator iter = str_list.begin(); iter != str_list.end()-1; ++iter ) {
            rel_path = rel_path + *iter + '/';
        }
    }
    rel_path = rel_path + *(str_list.end()-1) + ".lua";
    const char* rel_path_cstr = rel_path.c_str(); 
    wchar rel_wpath[1024];
    ex::mem::zero( rel_wpath, 1024 );
    char_to_wchar<1024> ( rel_path_cstr, rel_wpath );

    wpath_t full_path ( lua::base_path() );
    full_path += rel_wpath;

    // now load the buffer
    IFile::smart_ptr_t spFile = futil::file::readonly<PhysicalFile>(full_path);
    if ( spFile == NULL ) {
        ex_error ( "can't find the module %s by file", _module );
        return 0;
    }

    // now load the file to lua for execute
    DataHolder dataHolder;
    dataHolder.alloc ( size_t(spFile->size()) );
    spFile->read( dataHolder.data(), spFile->size() );

    //
    lua::global_module( _l, (*str_list.begin()).c_str() );
    for ( Array<string_t>::iterator iter = str_list.begin()+1; iter != str_list.end(); ++iter ) {
        lua::module( _l, -1, (*iter).c_str() );
    }

    // lua: setmetatable(M, {__index = _G}) { 
    // luaL_newmetatable ( _l, (*str_list.end()).c_str() );
    lua_newtable (_l);
    lua_getglobal ( _l, "_G" );
    lua_setfield ( _l, -2, "__index" );
    lua_setmetatable ( _l, -2 );
    // } lua end 

    // now load the buffer, this will create a function and put it at the top of the stack.
    int status = luaL_loadbuffer( _l,
                                  (const char*)(dataHolder.data()), 
                                  dataHolder.size(), 
                                  _module );
    lua::check(_l, status);

    // lua: setfenv(1,M) { 
    lua_pushvalue( _l, -2 ); // push the last table as the environment table.
    lua_setfenv( _l, -2 ); // pop the last value on the stack, and set it as the function environment.
    // } lua end 

    status = lua_pcall(_l, 0, LUA_MULTRET, 0);  /* call main */
    lua::check(_l, status);

    // after this, we will create a global link for faster access
    lua_setglobal( _l, _module );

    // now we can clear stack
    lua_settop( _l, 0 );

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int get_module ( lua_State* _l, const char* _moduleName )
{
    lua_getglobal( ex::lua::state(), _moduleName );
    if( !lua_istable(_l, -1) ) {
        lua_pop(_l, 1); // Pop the non-table.
        return 0;
    }
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int get_function ( lua_State* _l, const char* _moduleName, const char* _funcName )
{
    lua_getglobal( _l, _moduleName );
    lua_getfield( _l, -1, _funcName );
    if ( lua_isnil( _l, -1 ) ) {
        lua_pop(_l, 1); // remove nil
        ex_error ( "can't find function %s in module %s", _funcName, _moduleName );
        return 0;
    }
    lua_remove(_l, -2); // remove mod
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int w__gc ( lua_State* _l ) {
    Proxy* p = (Proxy*)lua_touserdata(_l, 1);
    Object* obj = (Object*)p->user_data;
    if ( p->own_by_gc )
        obj->release();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// DEBUG
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void dump_stack (lua_State * _l) {
    int i;
    int top = lua_gettop(_l);
    ex_log("-- stack: top --\n");
    for ( i = top; i >= 0; --i ) { /* repeat for each level */
        int t = lua_type(_l, i);
        switch (t) {
        case LUA_TSTRING: 
            { /* strings */
                ex_log("|- '%s'\n", lua_tostring(_l, i));
                break;
            }
        case LUA_TBOOLEAN: 
            { /* booleans */
                ex_log(lua_toboolean(_l, i) ? "|- true\n" : "|- false\n");
                break;
            }
        case LUA_TNUMBER: 
            { /* numbers */
                ex_log("|- %g\n", lua_tonumber(_l, i));
                break;
            }
        default: 
            { /* other values */
                ex_log("|- %s\n", lua_typename(_l, t));
                break;
            }
        }
    }
    ex_log("-- stack: bottom -- \n");
}

// ######################### 
} // end namespace lua 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 

#endif


