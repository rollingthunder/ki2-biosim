///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __biosim_gui__
#define __biosim_gui__

#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include "sim_area_widget.hpp"
#include <wx/scrolbar.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace biosim
{
	
	///////////////////////////////////////////////////////////////////////////////
	/// Class main_frame
	///////////////////////////////////////////////////////////////////////////////
	class main_frame : public wxFrame 
	{
		private:
		
		protected:
			wxStatusBar* status_bar;
			sim_area_widget *sim_area;
			wxScrollBar* scroll_v;
			wxScrollBar* scroll_h;
			
			
			wxChoice* select_creature;
			wxStaticText* m_staticText5;
			wxTextCtrl* show_strength;
			wxStaticText* m_staticText1;
			wxTextCtrl* show_speed;
			wxStaticText* m_staticText2;
			wxTextCtrl* show_lifetime;
			wxStaticText* m_staticText3;
			wxTextCtrl* show_properties;
			wxStaticText* m_staticText4;
			
			wxButton* button_place;
			
			
			wxButton* button_start;
			wxButton* button_pause;
			wxButton* button_step;
			
			// Virtual event handlers, overide them in your derived class
			virtual void scroll_v_event( wxScrollEvent& event ) { event.Skip(); }
			virtual void scroll_h_event( wxScrollEvent& event ) { event.Skip(); }
			virtual void select_creature_event( wxCommandEvent& event ) { event.Skip(); }
			virtual void place_creature_event( wxCommandEvent& event ) { event.Skip(); }
			virtual void button_start_event( wxCommandEvent& event ) { event.Skip(); }
			virtual void button_pause_event( wxCommandEvent& event ) { event.Skip(); }
			virtual void button_step_event( wxCommandEvent& event ) { event.Skip(); }
			
		
		public:
			
			main_frame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("BioSim"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,480 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
			~main_frame();
		
	};
	
} // namespace biosim

#endif //__biosim_gui__
