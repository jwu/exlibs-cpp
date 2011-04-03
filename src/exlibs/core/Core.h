// ======================================================================================
// File         : Core.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:39:44 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef CORE_H_1250523591
#define CORE_H_1250523591
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// fwd-decls
///////////////////////////////////////////////////////////////////////////////

class ConfigParser;

///////////////////////////////////////////////////////////////////////////////
// typedefs
///////////////////////////////////////////////////////////////////////////////

typedef class Core core_t;

///////////////////////////////////////////////////////////////////////////////
// class Core 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Core
{
    ///////////////////////////////////////////////////////////////////////////////
    // types 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef void (*callback_pfn_t) ();

    enum EInit
    {
        eInit_None          = 0,

        eInit_Allocator     = 1<<0,
        eInit_SDL           = 1<<1,
        eInit_StringID      = 1<<2,
        eInit_Config        = 1<<3,
        eInit_LogFile       = 1<<4,
        eInit_ResourceMng   = 1<<5,
        eInit_MemMng        = 1<<6,
        eInit_TimerMng      = 1<<7,
        eInit_fsys          = 1<<8,
        eInit_lua           = 1<<9,

        eInit_All = -1,
    }; // end enum EInit

    ///////////////////////////////////////////////////////////////////////////////
    // public functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    static result_t startup( uint32 _flags = eInit_All );
    static result_t teardown();
    static bool initialized () { return core_t::s_initialized; }

    //
    static ConfigParser* config () { return core_t::s_pConfigParser; }
    static const char* configfile () { return s_configFilename; }

    //
    static result_t registerEnterCallback( callback_pfn_t _pfn );
    static result_t registerExitCallback( callback_pfn_t _pfn );

    ///////////////////////////////////////////////////////////////////////////////
    // private functions 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    static result_t init(); 
    static result_t deinit(); 
    static uint32 genInitFlags ( uint32 _flags );

    //
    static result_t onEnter();
    static result_t onExit();

    //
    static result_t loadConfig( const char* _fileName );

    ///////////////////////////////////////////////////////////////////////////////
    // private data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    typedef Deque< callback_pfn_t, NoManaged<NullType>::TAllocator > callback_deque_t;
    static callback_deque_t s_enterCallbackDeque;    
    static callback_deque_t s_exitCallbackDeque;    

    //
    enum EState
    {
        eState_NotBegin     = 0x00,
        eState_Processing   = 0x01,
        eState_Finish       = 0x02
    };

    static const char* s_configFilename;

    //
    static EState s_enterState;
    static EState s_exitState;

    //
    static ConfigParser* s_pConfigParser; 

    //
    static uint32 s_initFlags;
    static bool s_initialized;
        
}; // end class Core

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END CORE_H_1250523591
// #################################################################################
