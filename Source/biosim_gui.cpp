///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "biosim_gui.hpp"

///////////////////////////////////////////////////////////////////////////
using namespace biosim;

main_frame::main_frame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 640,480 ), wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	status_bar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 0 );
	fgSizer2->AddGrowableRow( 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 0 );
	fgSizer3->AddGrowableRow( 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	sim_area = new sim_area_widget(this);
	fgSizer3->Add( sim_area, 0, wxALL|wxEXPAND, 5 );
	
	scroll_v = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL );
	fgSizer3->Add( scroll_v, 0, wxEXPAND, 5 );
	
	scroll_h = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	fgSizer3->Add( scroll_h, 0, wxEXPAND, 5 );
	
	fgSizer2->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 3, 1, 0, 0 );
	fgSizer4->AddGrowableRow( 1 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizer6->AddGrowableCol( 0 );
	fgSizer6->AddGrowableCol( 2 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString select_creatureChoices;
	select_creature = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, select_creatureChoices, 0 );
	select_creature->SetSelection( 0 );
	bSizer10->Add( select_creature, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Kreatur"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer10->Add( m_staticText5, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer10, 1, 0, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	show_strength = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer5->Add( show_strength, 0, wxALL, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Stärke"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer5->Add( m_staticText1, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer5, 1, 0, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	show_speed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer7->Add( show_speed, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Geschwindigkeit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer7->Add( m_staticText2, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer7, 1, 0, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	show_lifetime = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer8->Add( show_lifetime, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Lebensdauer"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer8->Add( m_staticText3, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer8, 1, 0, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	show_properties = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer9->Add( show_properties, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Eigenschaften"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer9->Add( m_staticText4, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer9, 1, 0, 5 );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	button_place = new wxButton( this, wxID_ANY, wxT("Kreatur plazieren"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( button_place, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	fgSizer6->Add( bSizer11, 1, wxEXPAND, 5 );
	
	
	fgSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	fgSizer4->Add( fgSizer6, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	button_start = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( button_start, 0, wxALL, 5 );
	
	button_pause = new wxButton( this, wxID_ANY, wxT("Pause"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( button_pause, 0, wxALL, 5 );
	
	button_step = new wxButton( this, wxID_ANY, wxT("Schritt"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( button_step, 0, wxALL, 5 );
	
	fgSizer4->Add( bSizer6, 1, wxEXPAND, 5 );
	
	fgSizer2->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	this->SetSizer( fgSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	scroll_v->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	select_creature->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_frame::select_creature_event ), NULL, this );
	button_place->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_frame::place_creature_event ), NULL, this );
	button_start->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_frame::button_start_event ), NULL, this );
	button_pause->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_frame::button_pause_event ), NULL, this );
	button_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_frame::button_step_event ), NULL, this );
}

main_frame::~main_frame()
{
	// Disconnect Events
	scroll_v->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_v->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( main_frame::scroll_v_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	scroll_h->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( main_frame::scroll_h_event ), NULL, this );
	select_creature->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( main_frame::select_creature_event ), NULL, this );
	button_place->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_frame::place_creature_event ), NULL, this );
	button_start->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_frame::button_start_event ), NULL, this );
	button_pause->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_frame::button_pause_event ), NULL, this );
	button_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( main_frame::button_step_event ), NULL, this );
	
}
