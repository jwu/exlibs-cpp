// ======================================================================================
// File         : main.cpp
// Author       : Wu Jie 
// Last Change  : 08/09/2010 | 11:39:07 AM | Monday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "widgets/EditorMain.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[] )
{
    int ret = -1;

    ex::result_t eResult = ex::EResult::ok;
    ex_check ( ex::core_t::startup(), "failed to start up core." );

    if ( eResult == ex::EResult::ok )
    {
        QApplication app ( argc, argv );

        EX_GP(EditorMain)->show ();
        EX_GP(EditorMain)->readSettings ();

        if ( EX_GP(EditorMain)->init () == ex::EResult::ok ) {
            ret = app.exec();
        }
        EX_GP(EditorMain)->deinit ();

        // close the programme
        EditorMain::destroy();

        // tear down core
        ex::core_t::teardown();
    }

    return ret;
}

