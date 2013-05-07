/**
 *************************************************************************
 *
 * @file sim_area_widget.cpp
 *
 * Custom control responsible for drawing the map and any creatures.
 *
 ************************************************************************/


#include "sim_area_widget.hpp"


#include "image.hpp"
#include "biosim_gui_impl.hpp"
#include "model.hpp"


namespace biosim
{


//////////////////////////////////////////////////////////////////////////
//
// sim_area_widget
//
//////////////////////////////////////////////////////////////////////////

 
BEGIN_EVENT_TABLE(sim_area_widget, wxControl)
	EVT_SIZE(sim_area_widget::resize)
	EVT_ERASE_BACKGROUND(sim_area_widget::ignore_erase_background)
    EVT_PAINT(sim_area_widget::paint_world)
	EVT_LEFT_DOWN(sim_area_widget::click)
END_EVENT_TABLE()


 sim_area_widget::sim_area_widget
	(wxWindow *parent)
	:
	wxControl(parent, wxID_ANY),
	scroll_x_(0),
	scroll_y_(0)
{
	env_bitmaps_[world_tile::deep_water] =
		convert_to_bitmap(*image::load("terrain/deep_sea.tga"));
	env_bitmaps_[world_tile::shallow_water] =
		convert_to_bitmap(*image::load("terrain/shallow_water.tga"));
	env_bitmaps_[world_tile::sand] =
		convert_to_bitmap(*image::load("terrain/sand.tga"));
	env_bitmaps_[world_tile::earth] =
		convert_to_bitmap(*image::load("terrain/earth.tga"));
	env_bitmaps_[world_tile::stones] =
		convert_to_bitmap(*image::load("terrain/rocks.tga"));
	env_bitmaps_[world_tile::snow] =
		convert_to_bitmap(*image::load("terrain/snow.tga"));

	cursor_bitmap_ =
		convert_to_bitmap(*image::load("cursor.tga"));
	dead_bitmap_ =
		convert_to_bitmap(*image::load("dead.tga"));
}


void sim_area_widget::resize(wxSizeEvent& size_event)
{
	size_event.Skip();

	biosim_gui_impl* parent =
		dynamic_cast<biosim_gui_impl*>(GetParent());

	// Parent not fully initialized to biosim_gui_impl yet.
	if (!parent) return;

	parent->update_scroll_ranges();
}


void sim_area_widget::paint_world(wxPaintEvent&)
{
	const model& app_model =
		(dynamic_cast<biosim_gui_impl&>(*GetParent())).app_model();
	const world_map& map =
		app_model.map();

	wxBufferedPaintDC dc(this);

	dc.SetBackground(wxBrush(wxColor(0,0,0)));
	dc.Clear();	

	wxSize client_size(GetClientSize());

	int scroll_pixel_x = scroll_x_ % tile_size_x;
	int scroll_pixel_y = scroll_y_ % tile_size_y;

	int tile_x_start = (scroll_x_ - scroll_pixel_x) / tile_size_x;
	int tile_y_start = (scroll_y_ - scroll_pixel_y) / tile_size_y;
	int tile_x_end = (scroll_x_ + client_size.GetX() - scroll_pixel_x) / tile_size_x + 1; 
	int tile_y_end = (scroll_y_ + client_size.GetY() - scroll_pixel_y) / tile_size_y + 1;

	for (int y = tile_y_start; y <= tile_y_end; ++y)
	for (int x = tile_x_start; x <= tile_x_end; ++x)
	{
		if (x < 0 || y < 0 || x >= map.size_x() || y >= map.size_y())
			continue;

		int tilepos_x = (x - tile_x_start) * tile_size_x - scroll_pixel_x;
		int tilepos_y = (y - tile_y_start) * tile_size_y - scroll_pixel_y;

		dc.DrawBitmap(env_bitmaps_[map.at(x, y).climate()],
					  tilepos_x, tilepos_y);

		if (x == app_model.cursor_x() &&
			y == app_model.cursor_y())
		{
			dc.DrawBitmap(cursor_bitmap_, tilepos_x, tilepos_y);
		}

		const world_tile& tile = map.at(x, y);

		for (world_tile::creature_iterator it(tile.begin()); it != tile.end(); ++it)
		{
			if((*it)->is_alive())
			{

				const creature_prototype *prototype = &((*it)->prototype);

				std::map<const creature_prototype*, wxBitmap>::iterator find_graphics
					(creature_bitmaps_.find(prototype));

				if (find_graphics == creature_bitmaps_.end())
				{
					find_graphics =
						creature_bitmaps_.insert
							(std::pair<const creature_prototype*, wxBitmap>
								(prototype, convert_to_bitmap(prototype->graphics()))).first;
				}

				dc.DrawBitmap(find_graphics->second, tilepos_x, tilepos_y);
			}
			else
				dc.DrawBitmap(dead_bitmap_, tilepos_x, tilepos_y);
		}
	}
}


void sim_area_widget::click(wxMouseEvent& event)
{
	model& app_model =
		(dynamic_cast<biosim_gui_impl&>(*GetParent())).app_model();

	int x = (event.GetPosition().x + scroll_x_) / tile_size_x;
	int y = (event.GetPosition().y + scroll_y_) / tile_size_y;

	app_model.set_cursor(x, y);	

	Refresh();
}


wxBitmap sim_area_widget::convert_to_bitmap(const image& img)
{
	std::vector<unsigned char> rgb;
	rgb.reserve(img.size_x() * img.size_y() * 3);
	std::vector<unsigned char> alpha;
	alpha.reserve(img.size_x() * img.size_y());

	for (int i = 0; i < img.size_x() * img.size_y(); ++i)
	{
		rgb.push_back(img.data()[i * 4]);
		rgb.push_back(img.data()[i * 4 + 1]);
		rgb.push_back(img.data()[i * 4 + 2]);
		alpha.push_back(img.data()[i * 4 + 3]);
	}
	
	return wxBitmap
		(wxImage(img.size_x(), img.size_y(), &rgb.front(), &alpha.front(), true));
}


const int sim_area_widget::tile_size_x = 32;
const int sim_area_widget::tile_size_y = 32;




} /* namespace biosim */