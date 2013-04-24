/**
 *************************************************************************
 *
 * @file biosim_gui_impl.hpp
 *
 * Event handlers for the biosim GUI.
 *
 ************************************************************************/


#if !defined(INCLUDED_BIOSIM_GUI_IMPL_HPP)
#define INCLUDED_BIOSIM_GUI_IMPL_HPP


#include "build_config.hpp"


#include <wx/timer.h>


#include "biosim_gui.hpp"


namespace biosim
{


class model;


/**
 *************************************************************************
 *
 * @class biosim_gui_impl
 *
 * Class which implements GUI events.
 *
 *************************************************************************
 */
class biosim_gui_impl : public main_frame
{
	friend class sim_area_widget;


	public:

		biosim_gui_impl(model& app_model);


		model& app_model() NOTHROW { return app_model_; }
		const model& app_model() const NOTHROW { return app_model_; }


	protected:

		void scroll_v_event(wxScrollEvent& event);
		void scroll_h_event(wxScrollEvent& event);
		void select_creature_event(wxCommandEvent& event);
		void place_creature_event(wxCommandEvent& event);
		void button_start_event(wxCommandEvent& event);
		void button_pause_event(wxCommandEvent& event);
		void button_step_event(wxCommandEvent& event);
		void timer_step_event(wxTimerEvent& event);


	private:

		void initialize_creature_prototypes();
		void update_scroll_ranges();
	
		model& app_model_;

		wxTimer step_timer_;
};




} /* namespace biosim */


#endif /* !defined(INCLUDED_BIOSIM_GUI_IMPL_HPP) */
