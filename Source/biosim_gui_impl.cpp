/**
 *************************************************************************
 *
 * @file biosim_gui_impl.hpp
 *
 * Event handlers for the biosim GUI, implementation.
 *
 ************************************************************************/


#include "biosim_gui_impl.hpp"


#include "creature.hpp"
#include "model.hpp"


#include "decision_tree.hpp"

namespace biosim
{


//////////////////////////////////////////////////////////////////////////
//
// biosim_gui_impl
//
//////////////////////////////////////////////////////////////////////////


biosim_gui_impl::biosim_gui_impl(model& app_model)
	:
	main_frame(NULL),
	app_model_(app_model)
{
	initialize_creature_prototypes();
	update_scroll_ranges();
}


void biosim_gui_impl::scroll_v_event(wxScrollEvent& event)
{
	sim_area->set_scroll_y(event.GetPosition());
	sim_area->Refresh();
}

void biosim_gui_impl::scroll_h_event(wxScrollEvent& event)
{
	sim_area->set_scroll_x(event.GetPosition());
	sim_area->Refresh();
}


void biosim_gui_impl::select_creature_event(wxCommandEvent& event)
{
	if (select_creature->IsEmpty()) return;

	int selected = select_creature->GetSelection();
	if (selected < 0 || selected >= (int)select_creature->GetCount()) return;

	void *data = select_creature->GetClientData(selected);
	if (!data) return;

	const creature_prototype& proto =
		*reinterpret_cast<const creature_prototype*>(data);
	
	show_strength->SetValue(wxString::Format(_("%i"), proto.strength()));
	show_speed->SetValue(wxString::Format(_("%i"), proto.speed()));
	show_lifetime->SetValue(wxString::Format(_("%i"), proto.lifetime()));
 	show_properties->SetValue(wxString::FromUTF8(proto.properties().c_str()));
}


void biosim_gui_impl::place_creature_event(wxCommandEvent& event)
{
	if (select_creature->IsEmpty()) return;

	int selected = select_creature->GetSelection();
	if (selected < 0 || selected >= (int)select_creature->GetCount()) return;

	void *data = select_creature->GetClientData(selected);
	if (!data) return;

	const creature_prototype& proto =
		*reinterpret_cast<const creature_prototype*>(data);
	
	app_model_.create_creature_at_cursor(proto);

	sim_area->Refresh();
}


void biosim_gui_impl::button_start_event(wxCommandEvent& event)
{
	if (step_timer_.IsRunning()) return;

	step_timer_.SetOwner(this);
	step_timer_.Start(100);
}

void biosim_gui_impl::button_pause_event(wxCommandEvent& event)
{
	if (!step_timer_.IsRunning()) return;
	step_timer_.Stop();
}

void biosim_gui_impl::button_step_event(wxCommandEvent& event)
{
	if (step_timer_.IsRunning()) return;

	auto true_action = std::make_shared<action<int>>([&](int i){
		status_bar->SetStatusText(wxT("True"));
	});
	auto false_action = std::make_shared<action<int>>([&](int i){
		status_bar->SetStatusText(wxT("False"));
	});
	inrange<int> test([](int i){return i;}, 0, 10, true_action, false_action);
	int i2 = 11;
	test.decide_action(i2).act(i2);

	app_model_.perform_step();
	sim_area->Refresh();
}

void biosim_gui_impl::timer_step_event(wxTimerEvent& event)
{

	app_model_.perform_step();
	sim_area->Refresh();
}


void biosim_gui_impl::update_scroll_ranges()
{
	wxSize clientsize(sim_area->GetClientSize());

	int size_x = app_model_.map().size_x() * sim_area->tile_size_x - 1;
	int size_y = app_model_.map().size_y() * sim_area->tile_size_y - 1;

	int max_thumb_x = size_x - clientsize.GetX();
	int max_thumb_y = size_y - clientsize.GetY();

	int thumb_x = scroll_h->GetThumbPosition();
	thumb_x = std::min(max_thumb_x, thumb_x);

	int thumb_y = scroll_v->GetThumbPosition();
	thumb_y = std::min(max_thumb_y, thumb_y);

	scroll_h->SetScrollbar
		(thumb_x, clientsize.GetX(), size_x, clientsize.GetX());
	scroll_v->SetScrollbar
		(thumb_y, clientsize.GetY(), size_y, clientsize.GetY());

	sim_area->set_scroll_x(thumb_x);
	sim_area->set_scroll_y(thumb_y);

	sim_area->Refresh();
}


void biosim_gui_impl::initialize_creature_prototypes()
{
	const std::list<creature_prototype>& prototypes =
		app_model_.prototypes();

	for (std::list<creature_prototype>::const_iterator c(prototypes.begin());
		 c != prototypes.end(); ++c)
	{
		select_creature->Append
 			(wxString::FromUTF8(c->name().c_str()), const_cast<creature_prototype*>(&*c));
	}

	select_creature->Select(0);
	wxCommandEvent foo = wxCommandEvent();
	select_creature_event(foo);
}




} /* namespace biosim */
