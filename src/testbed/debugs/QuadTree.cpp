// ======================================================================================
// File         : TQuadTree.cpp
// Author       : Wu Jie 
// Last Change  : 12/29/2009 | 13:50:55 PM | Tuesday,December
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"
#include "exlibs/QuadTree/QuadTree_inc.h"

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
// class CTestObject
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class CTestObject
{
public:

    CTestObject ( int _id = -1, const ex::recti_t& _rect = ex::recti_t() )
        : m_ID (_id)
        , m_Rect (_rect)
    {
    }
    ~CTestObject () 
    {
    }

    int& id () { return m_ID; }
    const int& id () const { return m_ID; }

    ex::recti_t& rect () { return m_Rect; }
    const ex::recti_t& rect () const { return m_Rect; }

    bool operator == ( const CTestObject& _value ) const { return (id() == _value.id()); }

protected:

    int m_ID;
    ex::recti_t m_Rect;

}; // end class CTestObject

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
struct Hash<CTestObject> 
{
    INLINE ex::uint operator () ( const CTestObject& _value ) const { return _value.id(); }
}; // end struct Hash<const char*>

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <> TQuadTree<CTestObject>::node_list_t* TQuadTree<CTestObject>::s_pFreeNodes = NULL;

///////////////////////////////////////////////////////////////////////////////
// class TQuadTreeItem<CTestObject>
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
class TQuadTreeItem<CTestObject> : public TQuadTreeItemBase<CTestObject>
{
public:
    TQuadTreeItem ( const CTestObject& _value, const ex::TQuadTree<CTestObject>& _qtree )
        : ex::TQuadTreeItemBase<CTestObject> (_value, 
                                              _qtree.MapFromWorld( ex::rectf_t( float(_value.rect().left()),
                                                                                float(_value.rect().top()),
                                                                                float(_value.rect().right()),
                                                                                float(_value.rect().bot()) ) ))
    {
    }

}; // end class TQuadTreeItem

// ######################### 
} // end namespace ex 
// ######################### 

typedef ex::TQuadTree<CTestObject> qtree_t;

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// ======================================================== 
// DrawNode
// ======================================================== 

void DrawNode ( const qtree_t* _pTree, const qtree_t::node_t* _pNode )
{
    //
    if ( _pNode == NULL )
        return;

    //
    DrawNode( _pTree, _pNode->SubNode(ex::eQuadTree_TL) );
    DrawNode( _pTree, _pNode->SubNode(ex::eQuadTree_TR) );
    DrawNode( _pTree, _pNode->SubNode(ex::eQuadTree_BL) );
    DrawNode( _pTree, _pNode->SubNode(ex::eQuadTree_BR) );

    // draw transparent
    ex::rectf_t rect = _pTree->MapToWorld( _pNode->Rect() );
    boxRGBA ( SDL_GetVideoSurface(), int(rect.left()), int(rect.top()), int(rect.right()), int(rect.bot()), 0, 255, 255, 50 );

    //
    if ( _pNode->SubNode(ex::eQuadTree_TL) ||
         _pNode->SubNode(ex::eQuadTree_TR) ||
         _pNode->SubNode(ex::eQuadTree_BL) ||
         _pNode->SubNode(ex::eQuadTree_BR) )
    {
        ex::rectf_t rect = _pTree->MapToWorld( _pNode->Rect() );
        ex::vec2f_t center = rect.center();
        lineRGBA ( SDL_GetVideoSurface(), int(rect.left()), int(center.y()), int(rect.right()), int(center.y()), 255, 255, 0, 255 );
        lineRGBA ( SDL_GetVideoSurface(), int(center.x()), int(rect.top()), int(center.x()), int(rect.bot()), 255, 255, 0, 255 );
    }
}

// ======================================================== 
// test_in_sdl
// ======================================================== 

TEST ( TQuadTree, test_in_sdl, off )
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
    static int mouse_dx = 0;
    static int mouse_dy = 0;
    static bool drawing_select = false;
    static bool drawing_create = false;
    static bool drawing_qtree = false;
    static bool moving_select = false;
    static bool resizing_select = false;
    static int resizing_flag = -1;

    // create the quad tree
    qtree_t::CreateNodeList ();
    {
        qtree_t qtree;
        qtree.init ( 0.0f, 0.0f, 1024.0f, 1024.0f, 512, 6 );

        // insert nodes to the tree
        typedef ex::Pool<CTestObject> obj_pool_t;
        typedef ex::Array<CTestObject> obj_list_t; 

        obj_pool_t objs; 
        obj_list_t selected_objs; 
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

                        if ( drawing_select )
                        {
                            selected_objs.clear();
                            qtree.Query( ex::rectf_t( (float)mouse_rect.left(), (float)mouse_rect.top(), (float)mouse_rect.right(), (float)mouse_rect.bot() ), 
                                         &selected_objs );
                        }
                        if ( moving_select || resizing_select )
                        {
                            // only available when mouse button down
                            mouse_dx = event.button.x - mouse_dx; 
                            mouse_dy = event.button.y - mouse_dy; 

                            if ( moving_select )
                            {
                                selected_objs.front().rect().left() += mouse_dx;
                                selected_objs.front().rect().right() += mouse_dx;
                                selected_objs.front().rect().top() += mouse_dy;
                                selected_objs.front().rect().bot() += mouse_dy;
                            }
                            else if ( resizing_select )
                            {
                                if ( resizing_flag == 0 )
                                {
                                    selected_objs.front().rect().left() += mouse_dx;
                                    selected_objs.front().rect().top() += mouse_dy;
                                }
                                else if ( resizing_flag == 1 )
                                {
                                    selected_objs.front().rect().right() += mouse_dx;
                                    selected_objs.front().rect().top() += mouse_dy;
                                }
                                else if ( resizing_flag == 2 )
                                {
                                    selected_objs.front().rect().left() += mouse_dx;
                                    selected_objs.front().rect().bot() += mouse_dy;
                                }
                                else if ( resizing_flag == 3 )
                                {
                                    selected_objs.front().rect().right() += mouse_dx;
                                    selected_objs.front().rect().bot() += mouse_dy;
                                }
                            }

                            obj_pool_t::iterator iter = objs.to_iter( selected_objs.front().id() );
                            (*iter).rect() = selected_objs.front().rect(); 
                            qtree.Update ( *iter );

                            mouse_dx = event.button.x;
                            mouse_dy = event.button.y;
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
                            if ( !moving_select || !drawing_select || !resizing_select )
                            {
                                selected_objs.clear();
                                qtree.Query( ex::vec2f_t( (float)mouse_x, (float)mouse_y ), &selected_objs );
                                if ( selected_objs.empty() )
                                    drawing_select = true;
                                else
                                {
                                    const ex::recti_t& irect = selected_objs.front().rect();
                                    const ex::rectf_t rect( (float)irect.left(), (float)irect.top(), (float)irect.right(), (float)irect.bot() ); 

                                    ex::vec2f_t mouse_pos( float(event.button.x), float(event.button.y) );
                                    if ( (mouse_pos - rect.top_left()).length() <= 4 )
                                    {
                                        resizing_flag = 0;
                                    }
                                    else if ( (mouse_pos - rect.top_right()).length() <= 4 )
                                    {
                                        resizing_flag = 1;
                                    }
                                    else if ( (mouse_pos - rect.bot_left()).length() <= 4 )
                                    {
                                        resizing_flag = 2;
                                    }
                                    else if ( (mouse_pos - rect.bot_right()).length() <= 4 )
                                    {
                                        resizing_flag = 3;
                                    }

                                    if ( resizing_flag != -1 )
                                    {
                                        resizing_select = true;
                                    }
                                    else
                                    {
                                        moving_select = true;
                                    }
                                    mouse_dx = event.button.x;
                                    mouse_dy = event.button.y;
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    {
                        mouse_rect.setInScreen ( mouse_x, mouse_y, event.button.x, event.button.y );

                        // create a rect object
                        if ( event.button.button == SDL_BUTTON_RIGHT )
                        {
                            if ( drawing_create)
                            {
                                obj_pool_t::iterator iter = objs.insert (CTestObject());
                                (*iter).id() = (int)objs.index( iter );
                                (*iter).rect() = mouse_rect;

                                qtree.insert ( *iter );
                                drawing_create = false;
                            }
                        }
                        // confirm a selection
                        else if ( event.button.button == SDL_BUTTON_LEFT )
                        {
                            if ( drawing_select )
                            {
                                selected_objs.clear();
                                qtree.Query( ex::rectf_t( (float)mouse_rect.left(), (float)mouse_rect.top(), (float)mouse_rect.right(), (float)mouse_rect.bot() ), 
                                             &selected_objs );
                                drawing_select = false;
                            }
                            else if ( moving_select )
                            {
                                moving_select = false;
                            }
                            else if ( resizing_select )
                            {
                                resizing_flag = -1;
                                resizing_select = false;
                            }
                        }
                    }
                    break;

                case SDL_KEYDOWN:
                    {
                        if ( event.key.keysym.sym == SDLK_SPACE )
                        {
                            drawing_qtree = !drawing_qtree;
                        }
                        else if ( event.key.keysym.sym == SDLK_DELETE )
                        {
                            //
                            for ( obj_list_t::iterator iter = selected_objs.begin(); iter != selected_objs.end(); ++iter )
                            {
                                ex::result_t eResult = qtree.remove ( (*iter) );
                                ex_assert ( eResult == ex::EResult::ok, "can't remove the item! ID: %d", (*iter).id() );
                                objs.erase_at( (*iter).id() );
                            }
                            selected_objs.clear();
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

            // draw quadtree nodes
            if ( drawing_qtree )
            {
                DrawNode ( &qtree, qtree.Root() );
            }

            // draw rects
            for ( obj_pool_t::iterator iter = objs.begin(); iter != objs.end(); ++iter )
            {
                rectangleRGBA ( SDL_GetVideoSurface(), (*iter).rect().left(), (*iter).rect().top(), (*iter).rect().right(), (*iter).rect().bot(), 255, 255, 255, 255 );
            }

            // draw selected rects
            for ( obj_list_t::iterator iter = selected_objs.begin(); iter != selected_objs.end(); ++iter )
            {
                ex::recti_t& obj_rect = (*iter).rect();
                rectangleRGBA ( SDL_GetVideoSurface(), obj_rect.left(), obj_rect.top(), obj_rect.right(), obj_rect.bot(), 255, 0, 0, 255 );
            }
            if ( selected_objs.size() == 1 ) // draw resize button when only one item select
            {
                ex::recti_t& obj_rect = selected_objs.front().rect();
                int size = 4;

                filledCircleRGBA ( SDL_GetVideoSurface(), obj_rect.top_left().x(), obj_rect.top_left().y(), size, 128, 255, 0, 80 );
                filledCircleRGBA ( SDL_GetVideoSurface(), obj_rect.top_right().x(), obj_rect.top_right().y(), size, 128, 255, 0, 80 );
                filledCircleRGBA ( SDL_GetVideoSurface(), obj_rect.bot_left().x(), obj_rect.bot_left().y(), size, 128, 255, 0, 80 );
                filledCircleRGBA ( SDL_GetVideoSurface(), obj_rect.bot_right().x(), obj_rect.bot_right().y(), size, 128, 255, 0, 80 );

                circleRGBA ( SDL_GetVideoSurface(), obj_rect.top_left().x(), obj_rect.top_left().y(), size, 255, 255, 0, 255 );
                circleRGBA ( SDL_GetVideoSurface(), obj_rect.top_right().x(), obj_rect.top_right().y(), size, 255, 255, 0, 255 );
                circleRGBA ( SDL_GetVideoSurface(), obj_rect.bot_left().x(), obj_rect.bot_left().y(), size, 255, 255, 0, 255 );
                circleRGBA ( SDL_GetVideoSurface(), obj_rect.bot_right().x(), obj_rect.bot_right().y(), size, 255, 255, 0, 255 );
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
            stringRGBA ( SDL_GetVideoSurface(), 10, 10, "Test QuadTree", 255, 255, 255, 255 );

            //
            SDL_Flip ( SDL_GetVideoSurface() );
        }
    }


    // destroy the tree
    qtree_t::DestroyNodeList ();
}
