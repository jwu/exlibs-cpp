// ======================================================================================
// File         : lua_global.h
// Author       : Wu Jie 
// Last Change  : 08/29/2010 | 17:10:27 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef LUA_GLOBAL_H_1283073042
#define LUA_GLOBAL_H_1283073042
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace lua { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// enhance 
///////////////////////////////////////////////////////////////////////////////


// global_module get the _key in global, check if it is a table, 
// if not, it pop-up the key and create a new table, set the global _key field 
// leave it at the top of the stack
EX_LIBS_DLL int global_module ( lua_State* _l, const char* _key );

// table actually do the same thing as global_module, instead it operate the table at _idx
EX_LIBS_DLL int module ( lua_State* _l, int _idx, const char* _key );

// usage: ex::lua::parse ( ex::lua::state(), luaL_loadfile(ex::lua::state(), filename) );
EX_LIBS_DLL int parse ( lua_State* _l, int status ); 
EX_LIBS_DLL void check ( lua_State* _l, int status );

///////////////////////////////////////////////////////////////////////////////
// engine level
///////////////////////////////////////////////////////////////////////////////

EX_LIBS_DLL void init ();
EX_LIBS_DLL void deinit ();
EX_LIBS_DLL lua_State* state ();

EX_LIBS_DLL void set_base_path ( const wchar* _path );
EX_LIBS_DLL wchar* base_path ();

// the load module will get base_path as the base directory for searching modules.
// if the base directory is NULL, it will to the current-working path for searching.
EX_LIBS_DLL int load_module_byfile ( lua_State* _l, const wchar* _fullpath );
EX_LIBS_DLL int load_module ( lua_State* _l, const char* _module );
EX_LIBS_DLL int get_module ( lua_State* _l, const char* _moduleName );
EX_LIBS_DLL int get_function ( lua_State* _l, const char* _moduleName, const char* _funcName );

// wrap helpers
EX_LIBS_DLL int w__gc ( lua_State* _l );

///////////////////////////////////////////////////////////////////////////////
// library wraps
///////////////////////////////////////////////////////////////////////////////

EX_LIBS_DLL int luaopen_core ( lua_State* _l );

///////////////////////////////////////////////////////////////////////////////
// DEBUG:
///////////////////////////////////////////////////////////////////////////////

EX_LIBS_DLL void dump_stack ( lua_State* _l );

// ######################### 
} // end namespace lua 
// ######################### 


// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END LUA_GLOBAL_H_1283073042
// #################################################################################


