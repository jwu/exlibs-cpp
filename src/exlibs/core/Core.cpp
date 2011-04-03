// ======================================================================================
// File         : Core.cpp
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 15:19:27 PM | Sunday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "memory/MemMng.h"

#if EX_USE_LUA
    #include "lua/lua_inc.h"
#endif

// #########################
namespace ex { 
// #########################

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: DestroyStringIDTable 
// ------------------------------------------------------------------ 

void DestroyStringIDTable ()
{
    ex_log("destroy StringID Table\n" );
    ex_check( string_id_t::destroy() == EResult::ok, "failed to destroy StringID table." );
    // DISABLE: ex_check( wstring_id_t::destroy() == EResult::ok, "failed to destroy StringID table." );
}

// ######################### 
} // end namespace _private 
// ######################### 


///////////////////////////////////////////////////////////////////////////////
// private data defines
///////////////////////////////////////////////////////////////////////////////

//
core_t::callback_deque_t core_t::s_enterCallbackDeque;    
core_t::callback_deque_t core_t::s_exitCallbackDeque;    

//
const char* core_t::s_configFilename = "ex-config.xml";

//
core_t::EState core_t::s_enterState = eState_NotBegin;
core_t::EState core_t::s_exitState = eState_NotBegin;

//
ConfigParser* core_t::s_pConfigParser = NULL;
uint32 core_t::s_initFlags = core_t::eInit_None;
bool core_t::s_initialized = false;

///////////////////////////////////////////////////////////////////////////////
// private defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: at the very beginning of core_t::startup 
// ------------------------------------------------------------------

result_t Core::onEnter()
{
    s_enterState = eState_Processing;

    //
    while ( !s_enterCallbackDeque.empty() )
    {
        callback_deque_t::ref_t pfn = s_enterCallbackDeque.front();
        pfn();
        s_enterCallbackDeque.pop_front();
    }

    //
    s_enterState = eState_Finish;

    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: at the very ending of Core::teardown
// ------------------------------------------------------------------

result_t Core::onExit()
{
    s_exitState = eState_Processing;

    //
    while ( !s_exitCallbackDeque.empty() )
    {
        callback_deque_t::ref_t pfn = s_exitCallbackDeque.back();
        pfn();
        s_exitCallbackDeque.pop_back();
    }

    //
    s_exitState = eState_Finish;

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc:  
// ------------------------------------------------------------------ 

uint32 Core::genInitFlags( uint32 _flags )
{
    uint32 result_falgs = _flags;

    // check and re-generate init flags by dependencies.

    //
    if ( flags_has( _flags, eInit_Config ) ) 
    {
        flags_add ( result_falgs, eInit_StringID );
    }

    //
    if ( flags_has( _flags, eInit_MemMng ) ) 
    {
        flags_add ( result_falgs, eInit_Allocator );
    }

    return result_falgs;
}

// ------------------------------------------------------------------
// Desc: after Core::onEnter 
// ------------------------------------------------------------------

result_t Core::init()
{
    // don't init twice.
    if ( s_initialized )
        return EResult::ok;

    // init log 
    if ( EX_GP (Log) == NULL ) return EResult::create_failed;
    EX_GP(Log)->hookMethod("printf", new LogPrintf );
    if ( flags_has( s_initFlags, eInit_LogFile ) )
    {
        EX_GP(Log)->hookMethod("logfile", new LogFile("./Log.txt") );
    }

    // init cpu-info // TODO: now is in CpuClock, but should be move to somewhere.
    ex_log("init cpu-info...\n" );
    ex_check_return ( cpu_clock_t::init () == EResult::ok, EResult::failed, "failed to init" );

    // init allocators
    if ( flags_has( s_initFlags, eInit_Allocator ) )
    {
        ex_log("init Allocators...\n" );
        if ( EX_GP(Allocator_sys) == NULL ) return EResult::create_failed;
        if ( EX_GP(Allocator_dl283) == NULL ) return EResult::create_failed;
    }

    // init SDL 
#if EX_USE_SDL
    if ( flags_has( s_initFlags, eInit_SDL ) )
    {
        ex_log("init SDL Joystick,Audio\n" );
        if ( SDL_Init( SDL_INIT_JOYSTICK | SDL_INIT_AUDIO ) )
        {
            ex_warning ( "Could not initialize SDL: %s", SDL_GetError() );
            return EResult::init_failed;
        }
    }
#endif

    // timer manager
    if ( flags_has( s_initFlags, eInit_TimerMng ) )
    {
        ex_log("create Timer Manager\n" );
        if ( EX_GP(TimerMng) == NULL ) return EResult::create_failed;
    }

    // resource manager
    if ( flags_has( s_initFlags, eInit_ResourceMng ) )
    {
        ex_log("create Resource Manager\n" );
        if ( EX_GP(ResourceMng) == NULL ) return EResult::create_failed;
    }

    // init MemMng
    if ( flags_has( s_initFlags, eInit_MemMng ) )
    {
        ex_log("init Memory Manager\n" );
        if ( EX_GP(MemMng) == NULL ) return EResult::create_failed;
        EX_GP(MemMng)->init();
    }

    // ======================================================== 
    // init item depend on MemMng 
    // ======================================================== 

    // init string id table
    if ( flags_has( s_initFlags, eInit_StringID ) )
    {
        ex_log("create StringID Table\n" );
        ex_check_return ( string_id_t::init( EX_UINT16_MAX + 1 ) == EResult::ok, EResult::failed, "failed to init StringID table." );
        // DISABLE ex_check_return ( wstring_id_t::init( EX_UINT16_MAX + 1 ) == EResult::ok, EResult::failed, "failed to init StringID table." );

        // This will register the string_id_t::destroy() function call right after MemMng destructor.
        registerExitCallback ( _private::DestroyStringIDTable );
    }

    // load config file 
    if ( flags_has( s_initFlags, eInit_Config ) )
    {
        // NOTE: the ConfigParser use string_id_t, so load config after string_id_t table init
        ex_check_return ( loadConfig( core_t::configfile() ) == EResult::ok, EResult::failed, "Failed to load config file" );
    }

    // init fsys
    if ( flags_has( s_initFlags, eInit_fsys ) ) {
        fsys::init ();
    }
    
#if EX_USE_LUA
    // init lua
    if ( flags_has( s_initFlags, eInit_lua ) ) {
        lua::init ();
    }
#endif

    // now register all internal classes
    ex::register_classes();
    ex::register_enums();

    s_initialized = true;

    //
    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: before Core::onExit
// ------------------------------------------------------------------

result_t Core::deinit()
{
    if ( s_initialized )
    {
#if EX_USE_LUA
        // de-init lua
        if ( flags_has( s_initFlags, eInit_lua ) ) {
            lua::deinit ();
        }
#endif

        // de-init fsys
        if ( flags_has( s_initFlags, eInit_fsys ) )
        {
            fsys::deinit ();
        }

        // de-init config parser
        if ( flags_has( s_initFlags, eInit_Config ) )
        {
            core_t::config()->save( core_t::configfile() );

            ex_log("Release Config Settings\n" );
            ex_delete ( core_t::s_pConfigParser );
        }

        // close SDL
#if EX_USE_SDL
        if ( flags_has( s_initFlags, eInit_SDL ) )
        {
            ex_log("Quit SDL\n" );
            SDL_Quit ();
        }
#endif

        s_initialized = false;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t Core::loadConfig( const char* _fileName )
{
    ex_log("Load config file %s\n", _fileName );
    result_t eResult = EResult::ok;

    const static float exlibs_ver = 2.1f;
    core_t::s_pConfigParser = ex_new ConfigParser();

    // ======================================================== 
    // autogen config
    // ======================================================== 

    // get working path
    char path[ex::MaxPath];
    ex::getcwd( path, int(ex::MaxPath) );
    path_t workingPath ( path );
    core_t::config()->set ("cwd", "string", workingPath.c_str(), true );

    // TEMP: set default value since we don't use config file in this version { 
    core_t::config()->set ("exlibs_ver", "float", to_str<dec>(exlibs_ver).c_str() );
    core_t::config()->set ("memleak_log", "string", "$(cwd)/memleak.err" );
    // } TEMP end 

    // check if builtin-resource exists
    if ( futil::dir::exists( workingPath + path_t("res/raw") )  ) {
        core_t::config()->set ("builtin_repo", "string", "$(cwd)/res", true );
    }
    else {
        // TEMP-DISABLE: ex_error ("builtin resource path not found!");
    }

    // TEMP DISABLE { 
    // // ======================================================== 
    // // parse config file
    // // ======================================================== 

    // eResult = core_t::config()->parse(_fileName);
    // if ( eResult != EResult::ok ||
    //      core_t::config()->has("exlibs_ver") == false || 
    //      core_t::config()->get<float>("exlibs_ver") != exlibs_ver )
    // {
    //     // ======================================================== 
    //     // default custom value
    //     // ======================================================== 

    //     core_t::config()->set ("exlibs_ver", "float", to_str<dec>(exlibs_ver).c_str() );
    //     core_t::config()->set ("memleak_log", "string", "$(cwd)/memleak.err" );

    //     //
    //     eResult = core_t::config()->save(_fileName);
    // }
    // } TEMP DISABLE end 

    return eResult;
}

///////////////////////////////////////////////////////////////////////////////
// public defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t Core::startup( uint32 _flags )
{
    // on enter
    if ( core_t::onEnter() != EResult::ok )
    {
        // TODO: report de-init failed;
    }

    s_initFlags = genInitFlags(_flags);

    // init core
    if ( core_t::init() != EResult::ok )
    {
        // TODO: report init failed;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t Core::teardown()
{
    if ( core_t::deinit() != EResult::ok )
    {
        ex_warning ("failed to deinit core");
    }

    // on exit
    // this will release all singleton
    if ( core_t::onExit() != EResult::ok )
    {
        ex_warning ("failed to release singleton in core");
    }

    //
#if ( EX_USE_SYSTEM_MEMORY || (EX_USE_MEMORY_MANAGER && EX_DBG_WITH_CRT) ) && defined (EX_DEBUG)
    // NOTE: use _CrtDumpMemoryLeaks will lead to un-expated memory leak, cause static memory havn't released yet. 
    // _CrtDumpMemoryLeaks(); 

    // This statement automatically calls _CrtDumpMemoryLeaks when your program exits.
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    s_initFlags = core_t::eInit_None;
    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t Core::registerEnterCallback( callback_pfn_t _pfn )
{
    //
    ex_assert( s_enterState != eState_Finish, "Invalid register, core_t::onEnter already been processed" );

    //
    switch( s_enterState )
    {
    case eState_NotBegin:
        {
            s_enterCallbackDeque.push_back(_pfn);
            break;
        }

    case eState_Processing:
        {
            s_enterCallbackDeque.push_front(_pfn);
            break;
        }

    default:
        break;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t Core::registerExitCallback( callback_pfn_t _pfn )
{
    //
    ex_assert( s_exitState != eState_Finish, "Invalid register, core_t::onExit already been processed" );

    //
    switch( s_exitState )
    {
    case eState_NotBegin:
        {
            s_exitCallbackDeque.push_back(_pfn);
            break;
        }

    case eState_Processing:
        {
            s_exitCallbackDeque.push_front(_pfn);
            break;
        }

    default:
        break;
    }

    return EResult::ok;
}

// #########################
} // end namespace ex 
// #########################

