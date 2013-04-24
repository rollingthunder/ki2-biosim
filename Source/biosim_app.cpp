/**
 *************************************************************************
 *
 * @file biosim_app.cpp
 *
 * Main wxwidgets application, implementation.
 *
 ************************************************************************/


#include "biosim_app.hpp"


#include "biosim_gui_impl.hpp"


namespace biosim
{


//////////////////////////////////////////////////////////////////////////
//
// biosim_app
//
//////////////////////////////////////////////////////////////////////////


bool biosim_app::OnInit()
{
	biosim_gui_impl *i(new biosim_gui_impl(model_));
    i->Show(true);
    SetTopWindow(i);
    return true;
}




} /* namespace biosim */

// HA-AAAAACK!
#ifndef main
int main(int argc, char **argv) { ; ; return wxEntry(argc, argv); } 
#endif
