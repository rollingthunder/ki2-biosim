/**
 *************************************************************************
 *
 * @file biosim_app.hpp
 *
 * Main wxwidgets application.
 *
 ************************************************************************/


#if !defined(INCLUDED_BIOSIM_APP_HPP)
#define INCLUDED_BIOSIM_APP_HPP


#include "build_config.hpp"


#include <wx/wx.h>


#include "model.hpp"


namespace biosim
{


/**
 *************************************************************************
 *
 * @class biosim_app
 *
 * High-level application class. Initializes the GUI and houses all
 * application data classes.
 *
 ************************************************************************/
class biosim_app : public wxApp
{

	private:

		virtual bool OnInit();

		model model_;
};


IMPLEMENT_APP(biosim_app)




} /* namespace biosim */


#endif /* !defined(INCLUDED_BIOSIM_APP_HPP) */
