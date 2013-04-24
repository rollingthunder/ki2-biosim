/**
 *************************************************************************
 *
 * @file sim_area_widget.hpp
 *
 * Custom control responsible for drawing the map and any creatures.
 *
 ************************************************************************/


#if !defined(INCLUDED_SIM_AREA_WIDGET_HPP)
#define INCLUDED_SIM_AREA_WIDGET_HPP


#include "build_config.hpp"


#include <map>

#include <wx/control.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>


#include "world_map.hpp"


namespace biosim
{


class image;
class creature_prototype;


/**
 *************************************************************************
 *
 * @class sim_area_widget
 *
 * A specialized widget for drawing the environment.
 *
 ************************************************************************/
class sim_area_widget : public wxControl
{

	public:

		sim_area_widget(wxWindow *parent);

		void resize(wxSizeEvent&);
		void ignore_erase_background(wxEraseEvent&) { }
		void paint_world(wxPaintEvent&);
		void click(wxMouseEvent& event);

		void set_scroll_x(int scroll_x) { scroll_x_ = scroll_x; }
		void set_scroll_y(int scroll_y) { scroll_y_ = scroll_y; }


		static const int tile_size_x;
		static const int tile_size_y;


	private:

		static wxBitmap convert_to_bitmap(const image& i);


		int scroll_x_;
		int scroll_y_;

		wxBitmap env_bitmaps_[world_tile::climate_count];
		wxBitmap cursor_bitmap_;
		wxBitmap dead_bitmap_;

		std::map<const creature_prototype*, wxBitmap> creature_bitmaps_;


		DECLARE_EVENT_TABLE()
};




} /* namespace biosim */


#endif /* !defined(INCLUDED_SIM_AREA_WIDGET_HPP) */
