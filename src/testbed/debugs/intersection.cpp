// ======================================================================================
// File         : T_Intersection.cpp
// Author       : Wu Jie 
// Last Change  : 01/12/2010 | 13:34:03 PM | Tuesday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

// ======================================================== 
// for sdl 
// ======================================================== 

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
// test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST ( T_Intersection, RectRect, off )
{
    // init and setup a video window
    if ( SDL_WasInit(SDL_INIT_VIDEO) == 0 )
    {
        SDL_InitSubSystem( SDL_INIT_VIDEO );
    }
    if ( !SDL_SetVideoMode( 1024, 1024, 0, 0 ) )
    {
        fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
        SDL_Quit();
        exit( -1 );
    }

    //
    static int mouse_x = 0;
    static int mouse_y = 0;
    static bool drawing_select = false;
    static bool drawing_create = false;

    // insert nodes to the tree
    typedef ex::Array<ex::recti_t> rects_t; 
    rects_t rect_list; 
    rects_t selected_rects; 

    ex::recti_t mouse_rect;

    // main loop
    SDL_Event event;
    int quit = 0;
    while ( !quit )
    {
        // ======================================================== 
        // clear the buffer
        // ======================================================== 

        ex::uint32 color = SDL_MapRGB( SDL_GetVideoSurface()->format, 20, 20, 20 );
        SDL_FillRect( SDL_GetVideoSurface(), NULL, color );

        // ======================================================== 
        // process event
        // ======================================================== 

        while ( SDL_PollEvent(&event) )
        {

            switch ( event.type ) 
            {
                // process mouse
            case SDL_MOUSEMOTION:
                {
                    if ( drawing_create || drawing_select )
                    {
                        mouse_rect.setInScreen ( mouse_x, mouse_y, event.button.x, event.button.y );
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;
                    mouse_rect.setInScreen ( mouse_x, mouse_y, event.button.x, event.button.y );

                    if ( event.button.button == SDL_BUTTON_RIGHT )
                    {
                        drawing_create = true;
                    }
                    else if ( event.button.button == SDL_BUTTON_LEFT )
                    {
                        drawing_select = true;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                {
                    mouse_rect.setInScreen ( mouse_x, mouse_y, event.button.x, event.button.y );

                    if ( event.button.button == SDL_BUTTON_RIGHT )
                    {
                        rect_list.push_back(mouse_rect);
                        drawing_create = false;
                    }
                    else if ( event.button.button == SDL_BUTTON_LEFT )
                    {
                        selected_rects.clear();
                        for ( rects_t::iterator iter = rect_list.begin(); iter != rect_list.end(); ++iter )
                        {
                            if ( mouse_rect.contains(*iter) || ex::intersect::rect_rect( mouse_rect, *iter ) )
                            {
                                selected_rects.push_back(*iter);
                            }
                        }
                        drawing_select = false;
                    }
                }
                break;

            case SDL_QUIT:
                quit = 1; 
                break;

            default:
                break;
            }
        }

        // ======================================================== 
        // rendering
        // ======================================================== 

        // draw rects
        for ( rects_t::iterator iter = rect_list.begin(); iter != rect_list.end(); ++iter )
        {
            rectangleRGBA ( SDL_GetVideoSurface(), (*iter).left(), (*iter).top(), (*iter).right(), (*iter).bot(), 255, 255, 255, 255 );
        }

        // draw selected rects
        for ( rects_t::iterator iter = selected_rects.begin(); iter != selected_rects.end(); ++iter )
        {
            rectangleRGBA ( SDL_GetVideoSurface(), (*iter).left(), (*iter).top(), (*iter).right(), (*iter).bot(), 255, 0, 0, 255 );
        }

        // daw creating & selecting rect
        if ( drawing_create )
        {
            rectangleRGBA ( SDL_GetVideoSurface(), mouse_rect.left(), mouse_rect.top(), mouse_rect.right(), mouse_rect.bot(), 0, 255, 255, 255 );
        }
        if ( drawing_select )
        {
            boxRGBA ( SDL_GetVideoSurface(), mouse_rect.left(), mouse_rect.top(), mouse_rect.right(), mouse_rect.bot(), 0, 128, 255, 128 );
            rectangleRGBA ( SDL_GetVideoSurface(), mouse_rect.left(), mouse_rect.top(), mouse_rect.right(), mouse_rect.bot(), 0, 150, 255, 255 );
        }

        //
        stringRGBA ( SDL_GetVideoSurface(), 10, 10, "Test Intersection RectRect", 255, 255, 255, 255 );

        //
        SDL_Flip ( SDL_GetVideoSurface() );
    }
}
