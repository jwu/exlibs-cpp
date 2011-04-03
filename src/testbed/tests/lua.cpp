// ======================================================================================
// File         : lua.cpp
// Author       : Wu Jie 
// Last Change  : 08/31/2010 | 15:27:07 PM | Tuesday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"
#include "exlibs/lua/lua_inc.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( lua, normal, off )
{
    // ex::wpath_t base_path = ex::wpath_t("e:/projects/Client/exlibs/src/testbed/res/lua/scripts/");

    ex::lua::set_base_path ( W("e:/projects/Client/exlibs/src/testbed/res/lua/scripts/") );
    ex::lua::load_module ( ex::lua::state(), "mod_1.foo.foobar" );
    ex::lua::load_module ( ex::lua::state(), "mod_1.bar.foobar" );
    ex::lua::load_module ( ex::lua::state(), "mod_2.foo.foobar" );
    ex::lua::load_module ( ex::lua::state(), "mod_2.bar.foobar" );

    int status = 0; 

    // test1 { 
    // lua_getglobal( ex::lua::state(), "mod_1" );
    // ex_assert ( lua_istable( ex::lua::state(), -1 ), "faield" );
    // lua_getfield( ex::lua::state(), -1, "foo" );
    // ex_assert ( lua_istable( ex::lua::state(), -1 ), "faield" );
    // lua_getfield( ex::lua::state(), -1, "foobar" );
    // ex_assert ( lua_istable( ex::lua::state(), -1 ), "faield" );
    // lua_getfield( ex::lua::state(), -1, "test" );
    // ex_assert ( lua_isfunction( ex::lua::state(), -1 ), "faield" );

    // status = lua_pcall( ex::lua::state(), 0, 0, 0 );
    // ex::lua::check( ex::lua::state(), status );
    // } test1 end 

    // test2 { 
    ex::lua::get_function( ex::lua::state(), "mod_1.bar.foobar", "test" );
    status = lua_pcall( ex::lua::state(), 0, 0, 0 );
    ex::lua::check( ex::lua::state(), status );
    // } test2 end 

    // test3 { 
    ex::lua::get_function( ex::lua::state(), "mod_2.foo.foobar", "test" );
    status = lua_pcall( ex::lua::state(), 0, 0, 0 );
    ex::lua::check( ex::lua::state(), status );
    // } test3 end 

    EX_HW_BREAK();
}

