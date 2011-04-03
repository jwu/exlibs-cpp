// ======================================================================================
// File         : sdl_input.cpp
// Author       : Wu Jie 
// Last Change  : 10/28/2009 | 18:39:02 PM | Wednesday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"
#include <SDL/include/SDL.h>
#include <SDL/include/SDL_gfxPrimitives.h>

#if (EX_COMPILER == EX_MSVC)
    #ifdef EX_DEBUG
        #pragma comment( lib, "../../ext/SDL/lib/Debug/SDL.lib" )
        #pragma comment( lib, "../../ext/SDL/lib/Debug/SDLmain.lib" )
        #pragma comment( lib, "../../ext/SDL/lib/Debug/SDL_gfx.lib" )
    #else
        #pragma comment( lib, "../../ext/SDL/lib/Release/SDL.lib" )
        #pragma comment( lib, "../../ext/SDL/lib/Release/SDLmain.lib" )
        #pragma comment( lib, "../../ext/SDL/lib/Release/SDL_gfx.lib" )
    #endif
#endif

///////////////////////////////////////////////////////////////////////////////
// enums
///////////////////////////////////////////////////////////////////////////////


// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

const char* SDLKeyToString( SDLKey _enum )
{
#define EX_ENUM_TO_STRING_CASE(_x) case _x: return (#_x)
    switch( _enum )
    {
        EX_ENUM_TO_STRING_CASE(SDLK_UNKNOWN);
        EX_ENUM_TO_STRING_CASE(SDLK_BACKSPACE);
        EX_ENUM_TO_STRING_CASE(SDLK_TAB);
        EX_ENUM_TO_STRING_CASE(SDLK_CLEAR);
        EX_ENUM_TO_STRING_CASE(SDLK_RETURN);
        EX_ENUM_TO_STRING_CASE(SDLK_PAUSE);
        EX_ENUM_TO_STRING_CASE(SDLK_ESCAPE);
        EX_ENUM_TO_STRING_CASE(SDLK_SPACE);
        EX_ENUM_TO_STRING_CASE(SDLK_EXCLAIM);
        EX_ENUM_TO_STRING_CASE(SDLK_QUOTEDBL);
        EX_ENUM_TO_STRING_CASE(SDLK_HASH);
        EX_ENUM_TO_STRING_CASE(SDLK_DOLLAR);
        EX_ENUM_TO_STRING_CASE(SDLK_AMPERSAND);
        EX_ENUM_TO_STRING_CASE(SDLK_QUOTE);
        EX_ENUM_TO_STRING_CASE(SDLK_LEFTPAREN);
        EX_ENUM_TO_STRING_CASE(SDLK_RIGHTPAREN);
        EX_ENUM_TO_STRING_CASE(SDLK_ASTERISK);
        EX_ENUM_TO_STRING_CASE(SDLK_PLUS);
        EX_ENUM_TO_STRING_CASE(SDLK_COMMA);
        EX_ENUM_TO_STRING_CASE(SDLK_MINUS);
        EX_ENUM_TO_STRING_CASE(SDLK_PERIOD);
        EX_ENUM_TO_STRING_CASE(SDLK_SLASH);
        EX_ENUM_TO_STRING_CASE(SDLK_0);
        EX_ENUM_TO_STRING_CASE(SDLK_1);
        EX_ENUM_TO_STRING_CASE(SDLK_2);
        EX_ENUM_TO_STRING_CASE(SDLK_3);
        EX_ENUM_TO_STRING_CASE(SDLK_4);
        EX_ENUM_TO_STRING_CASE(SDLK_5);
        EX_ENUM_TO_STRING_CASE(SDLK_6);
        EX_ENUM_TO_STRING_CASE(SDLK_7);
        EX_ENUM_TO_STRING_CASE(SDLK_8);
        EX_ENUM_TO_STRING_CASE(SDLK_9);
        EX_ENUM_TO_STRING_CASE(SDLK_COLON);
        EX_ENUM_TO_STRING_CASE(SDLK_SEMICOLON);
        EX_ENUM_TO_STRING_CASE(SDLK_LESS);
        EX_ENUM_TO_STRING_CASE(SDLK_EQUALS);
        EX_ENUM_TO_STRING_CASE(SDLK_GREATER);
        EX_ENUM_TO_STRING_CASE(SDLK_QUESTION);
        EX_ENUM_TO_STRING_CASE(SDLK_AT);
        EX_ENUM_TO_STRING_CASE(SDLK_LEFTBRACKET);
        EX_ENUM_TO_STRING_CASE(SDLK_BACKSLASH);
        EX_ENUM_TO_STRING_CASE(SDLK_RIGHTBRACKET);
        EX_ENUM_TO_STRING_CASE(SDLK_CARET);
        EX_ENUM_TO_STRING_CASE(SDLK_UNDERSCORE);
        EX_ENUM_TO_STRING_CASE(SDLK_BACKQUOTE);
        EX_ENUM_TO_STRING_CASE(SDLK_a);
        EX_ENUM_TO_STRING_CASE(SDLK_b);
        EX_ENUM_TO_STRING_CASE(SDLK_c);
        EX_ENUM_TO_STRING_CASE(SDLK_d);
        EX_ENUM_TO_STRING_CASE(SDLK_e);
        EX_ENUM_TO_STRING_CASE(SDLK_f);
        EX_ENUM_TO_STRING_CASE(SDLK_g);
        EX_ENUM_TO_STRING_CASE(SDLK_h);
        EX_ENUM_TO_STRING_CASE(SDLK_i);
        EX_ENUM_TO_STRING_CASE(SDLK_j);
        EX_ENUM_TO_STRING_CASE(SDLK_k);
        EX_ENUM_TO_STRING_CASE(SDLK_l);
        EX_ENUM_TO_STRING_CASE(SDLK_m);
        EX_ENUM_TO_STRING_CASE(SDLK_n);
        EX_ENUM_TO_STRING_CASE(SDLK_o);
        EX_ENUM_TO_STRING_CASE(SDLK_p);
        EX_ENUM_TO_STRING_CASE(SDLK_q);
        EX_ENUM_TO_STRING_CASE(SDLK_r);
        EX_ENUM_TO_STRING_CASE(SDLK_s);
        EX_ENUM_TO_STRING_CASE(SDLK_t);
        EX_ENUM_TO_STRING_CASE(SDLK_u);
        EX_ENUM_TO_STRING_CASE(SDLK_v);
        EX_ENUM_TO_STRING_CASE(SDLK_w);
        EX_ENUM_TO_STRING_CASE(SDLK_x);
        EX_ENUM_TO_STRING_CASE(SDLK_y);
        EX_ENUM_TO_STRING_CASE(SDLK_z);
        EX_ENUM_TO_STRING_CASE(SDLK_DELETE);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_0);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_1);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_2);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_3);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_4);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_5);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_6);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_7);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_8);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_9);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_10);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_11);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_12);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_13);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_14);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_15);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_16);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_17);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_18);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_19);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_20);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_21);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_22);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_23);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_24);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_25);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_26);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_27);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_28);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_29);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_30);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_31);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_32);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_33);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_34);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_35);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_36);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_37);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_38);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_39);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_40);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_41);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_42);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_43);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_44);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_45);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_46);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_47);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_48);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_49);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_50);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_51);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_52);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_53);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_54);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_55);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_56);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_57);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_58);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_59);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_60);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_61);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_62);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_63);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_64);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_65);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_66);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_67);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_68);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_69);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_70);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_71);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_72);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_73);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_74);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_75);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_76);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_77);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_78);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_79);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_80);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_81);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_82);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_83);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_84);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_85);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_86);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_87);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_88);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_89);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_90);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_91);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_92);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_93);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_94);
        EX_ENUM_TO_STRING_CASE(SDLK_WORLD_95);
        EX_ENUM_TO_STRING_CASE(SDLK_KP0);
        EX_ENUM_TO_STRING_CASE(SDLK_KP1);
        EX_ENUM_TO_STRING_CASE(SDLK_KP2);
        EX_ENUM_TO_STRING_CASE(SDLK_KP3);
        EX_ENUM_TO_STRING_CASE(SDLK_KP4);
        EX_ENUM_TO_STRING_CASE(SDLK_KP5);
        EX_ENUM_TO_STRING_CASE(SDLK_KP6);
        EX_ENUM_TO_STRING_CASE(SDLK_KP7);
        EX_ENUM_TO_STRING_CASE(SDLK_KP8);
        EX_ENUM_TO_STRING_CASE(SDLK_KP9);
        EX_ENUM_TO_STRING_CASE(SDLK_KP_PERIOD);
        EX_ENUM_TO_STRING_CASE(SDLK_KP_DIVIDE);
        EX_ENUM_TO_STRING_CASE(SDLK_KP_MULTIPLY);
        EX_ENUM_TO_STRING_CASE(SDLK_KP_MINUS);
        EX_ENUM_TO_STRING_CASE(SDLK_KP_PLUS);
        EX_ENUM_TO_STRING_CASE(SDLK_KP_ENTER);
        EX_ENUM_TO_STRING_CASE(SDLK_KP_EQUALS);
        EX_ENUM_TO_STRING_CASE(SDLK_UP);
        EX_ENUM_TO_STRING_CASE(SDLK_DOWN);
        EX_ENUM_TO_STRING_CASE(SDLK_RIGHT);
        EX_ENUM_TO_STRING_CASE(SDLK_LEFT);
        EX_ENUM_TO_STRING_CASE(SDLK_INSERT);
        EX_ENUM_TO_STRING_CASE(SDLK_HOME);
        EX_ENUM_TO_STRING_CASE(SDLK_END);
        EX_ENUM_TO_STRING_CASE(SDLK_PAGEUP);
        EX_ENUM_TO_STRING_CASE(SDLK_PAGEDOWN);
        EX_ENUM_TO_STRING_CASE(SDLK_F1);
        EX_ENUM_TO_STRING_CASE(SDLK_F2);
        EX_ENUM_TO_STRING_CASE(SDLK_F3);
        EX_ENUM_TO_STRING_CASE(SDLK_F4);
        EX_ENUM_TO_STRING_CASE(SDLK_F5);
        EX_ENUM_TO_STRING_CASE(SDLK_F6);
        EX_ENUM_TO_STRING_CASE(SDLK_F7);
        EX_ENUM_TO_STRING_CASE(SDLK_F8);
        EX_ENUM_TO_STRING_CASE(SDLK_F9);
        EX_ENUM_TO_STRING_CASE(SDLK_F10);
        EX_ENUM_TO_STRING_CASE(SDLK_F11);
        EX_ENUM_TO_STRING_CASE(SDLK_F12);
        EX_ENUM_TO_STRING_CASE(SDLK_F13);
        EX_ENUM_TO_STRING_CASE(SDLK_F14);
        EX_ENUM_TO_STRING_CASE(SDLK_F15);
        EX_ENUM_TO_STRING_CASE(SDLK_NUMLOCK);
        EX_ENUM_TO_STRING_CASE(SDLK_CAPSLOCK);
        EX_ENUM_TO_STRING_CASE(SDLK_SCROLLOCK);
        EX_ENUM_TO_STRING_CASE(SDLK_RSHIFT);
        EX_ENUM_TO_STRING_CASE(SDLK_LSHIFT);
        EX_ENUM_TO_STRING_CASE(SDLK_RCTRL);
        EX_ENUM_TO_STRING_CASE(SDLK_LCTRL);
        EX_ENUM_TO_STRING_CASE(SDLK_RALT);
        EX_ENUM_TO_STRING_CASE(SDLK_LALT);
        EX_ENUM_TO_STRING_CASE(SDLK_RMETA);
        EX_ENUM_TO_STRING_CASE(SDLK_LMETA);
        EX_ENUM_TO_STRING_CASE(SDLK_LSUPER);
        EX_ENUM_TO_STRING_CASE(SDLK_RSUPER);
        EX_ENUM_TO_STRING_CASE(SDLK_MODE);
        EX_ENUM_TO_STRING_CASE(SDLK_COMPOSE);
        EX_ENUM_TO_STRING_CASE(SDLK_HELP);
        EX_ENUM_TO_STRING_CASE(SDLK_PRINT);
        EX_ENUM_TO_STRING_CASE(SDLK_SYSREQ);
        EX_ENUM_TO_STRING_CASE(SDLK_BREAK);
        EX_ENUM_TO_STRING_CASE(SDLK_MENU);
        EX_ENUM_TO_STRING_CASE(SDLK_POWER);
        EX_ENUM_TO_STRING_CASE(SDLK_EURO);
        EX_ENUM_TO_STRING_CASE(SDLK_UNDO);
    default: return "Unknown Enum";
    }
#undef EX_ENUM_TO_STRING_CASE
}

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST ( sdl_input, keyboard, off )
{
    // init and setup a video window
    if ( SDL_WasInit(SDL_INIT_VIDEO) == 0 )
    {
        SDL_InitSubSystem( SDL_INIT_VIDEO );
    }
    if ( !SDL_SetVideoMode( 640, 480, 0, 0 ) )
    {
        fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
        SDL_Quit();
        exit( -1 );
    }

    stringRGBA ( SDL_GetVideoSurface(), 10, 10, "Test Keyboard", 255, 255, 255, 255 );

    //The SDL event that we will poll to get events.
    SDL_Event event;

    //Poll our SDL key event for any keystrokes.
    int quit = 0;
    while ( !quit )
    {
        while ( SDL_PollEvent(&event) )
        {
            switch ( event.type ) 
            {
            case SDL_KEYDOWN:
                printf ( "key: %s down\n", SDLKeyToString( event.key.keysym.sym ) );
                break;

            case SDL_KEYUP:
                printf ( "key: %s up\n", SDLKeyToString( event.key.keysym.sym ) );
                break;

            case SDL_QUIT:
                quit = 1; 
                break;

            default:
                break;
            }
        }

        SDL_Flip ( SDL_GetVideoSurface() );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST ( sdl_input, mouse, off )
{
    // init and setup a video window
    if ( SDL_WasInit(SDL_INIT_VIDEO) == 0 )
    {
        SDL_InitSubSystem( SDL_INIT_VIDEO );
    }
    if ( !SDL_SetVideoMode( 640, 480, 0, 0 ) )
    {
        fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
        SDL_Quit();
        exit( -1 );
    }

    //The SDL event that we will poll to get events.
    SDL_Event event;

    //Poll our SDL key event for any keystrokes.
    int quit = 0;
    while ( !quit )
    {
        static int mouse_x = 0;
        static int mouse_y = 0;

        static int mouse_button_x = 0;
        static int mouse_button_y = 0;
        static int mouse_button_pressed = 0;

        // clear screen
        ex::uint32 gray = SDL_MapRGB( SDL_GetVideoSurface()->format, 50, 50, 50 );
		SDL_FillRect( SDL_GetVideoSurface(), NULL, gray );

        // test mouse
        int screen_x = 10;
        int screen_y = 10;
        stringRGBA ( SDL_GetVideoSurface(), screen_x, screen_y, "Test mouse", 255, 255, 255, 255 );

        // show current mouse coordinate
        screen_y += 10;
        ex::string_t str = ex::string_t().printf ( "(%d,%d)", mouse_x, mouse_y );
        stringRGBA ( SDL_GetVideoSurface(), screen_x, screen_y, str.c_str(), 255, 255, 255, 255 );

        // show current mouse press up/down coordinate
        screen_y += 10;
        str = ex::string_t().printf ( "%s at: (%d,%d)", mouse_button_pressed ? "pressed" : "released", mouse_button_x, mouse_button_y );
        stringRGBA ( SDL_GetVideoSurface(), screen_x, screen_y, str.c_str(), 255, 255, 255, 255 );

        // process event
        while ( SDL_PollEvent(&event) )
        {
            switch ( event.type ) 
            {
            case SDL_MOUSEMOTION:
                {
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                {
                    mouse_button_x = event.button.x;
                    mouse_button_y = event.button.y;
                    mouse_button_pressed = (event.button.state == SDL_PRESSED);
                }
                break;

            case SDL_QUIT:
                quit = 1; 
                break;

            default:
                break;
            }
        }

        SDL_Flip ( SDL_GetVideoSurface() );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST ( sdl_input, joystick, off )
{
    // init and setup a video window
    if ( SDL_WasInit(SDL_INIT_VIDEO) == 0 )
    {
        SDL_InitSubSystem( SDL_INIT_VIDEO );
    }
    if ( !SDL_SetVideoMode( 640, 480, 0, 0 ) )
    {
        fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
        SDL_Quit();
        exit( -1 );
    }

    // enable joystick event 
    SDL_Joystick* pJoystick;
    SDL_JoystickEventState(SDL_ENABLE);
    pJoystick = SDL_JoystickOpen(0); // NOTE: here we only detect num-0 joystick

    //The SDL event that we will poll to get events.
    SDL_Event event;

    //Poll our SDL key event for any keystrokes.
    int quit = 0;
    while ( !quit )
    {
        static int num_joysticks = SDL_NumJoysticks();
        static int num_axes = SDL_JoystickNumAxes(pJoystick);
        static int num_balls = SDL_JoystickNumBalls(pJoystick);
        static int num_hats = SDL_JoystickNumHats(pJoystick);
        static int num_buttons = SDL_JoystickNumButtons(pJoystick);

        // clear screen
        ex::uint32 gray = SDL_MapRGB( SDL_GetVideoSurface()->format, 128, 128, 128 );
		SDL_FillRect( SDL_GetVideoSurface(), NULL, gray );

        // test joystick
        int screen_x = 10;
        int screen_y = 10;
        stringRGBA ( SDL_GetVideoSurface(), screen_x, screen_y, "Test joystick", 255, 255, 255, 255 );

        // show number of joysticks
        screen_y += 10;
        ex::string_t str = ex::string_t().printf ( "%i joysticks were found.", num_joysticks );
        stringRGBA ( SDL_GetVideoSurface(), screen_x, screen_y, str.c_str(), 255, 255, 255, 255 );

        // show joystick names
        screen_y += 10;
        str = ex::string_t().printf ( "The names of the joysticks are:" );
        stringRGBA ( SDL_GetVideoSurface(), screen_x, screen_y, str.c_str(), 255, 255, 255, 255 );
        for( int i = 0; i < num_joysticks; ++i ) 
        {
            screen_y += 10;
            str = ex::string_t().printf ( "  |-%s", SDL_JoystickName(i) );
            stringRGBA ( SDL_GetVideoSurface(), screen_x, screen_y, str.c_str(), 255, 255, 255, 255 );
        }

#if 0
        // show joystick axes
        for ( int i = 0; i < num_axes; ++i )
        {
            screen_y += 10;
            str = ex::string_t().printf ( "axe_%d: %d", SDL_JoystickName(i) );
            stringRGBA ( SDL_GetVideoSurface(), screen_x, screen_y, str.c_str(), 255, 255, 255, 255 );
        }
#endif

        while ( SDL_PollEvent(&event) )
        {
            switch ( event.type ) 
            {
            case SDL_JOYAXISMOTION:
                {
                    // TODO:
                    printf ( "joy axis motion\n" );
                }
                break;

            case SDL_JOYBALLMOTION:
                {
                    // TODO:
                    printf ( "joy ball motion\n" );
                }
                break;

            case SDL_JOYHATMOTION:
                {
                    // TODO:
                    printf ( "joy hat motion\n" );
                }
                break;

            case SDL_JOYBUTTONDOWN:
                {
                    // TODO:
                    printf ( "joy button down\n" );
                }
                break;

            case SDL_JOYBUTTONUP:
                {
                    // TODO:
                    printf ( "joy button up\n" );
                }
                break;

            case SDL_QUIT:
                quit = 1; 
                break;

            default:
                break;
            }
        }

        SDL_Flip ( SDL_GetVideoSurface() );
    }

    SDL_JoystickClose(pJoystick);
}
