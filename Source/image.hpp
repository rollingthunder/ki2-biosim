/**
 *************************************************************************
 *
 * @file image.hpp
 *
 * Management of input images.
 *
 ************************************************************************/


#if !defined(INCLUDED_IMAGE_HPP)
#define INCLUDED_IMAGE_HPP


#include "build_config.hpp"


#include <vector>
#include <string>


namespace biosim
{


/**
 *************************************************************************
 *
 * @class color
 * 
 * A single RGBA quadruplet.
 *
 ************************************************************************/
class color
{
	public:

		color() NOTHROW : r(0), g(0), b(0), a(0) { }

		color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) NOTHROW 
			: r(r), g(g), b(b), a(a) { }

		union
		{
			struct
			{
				unsigned char r;
				unsigned char g;
				unsigned char b;
				unsigned char a;
			};

			unsigned char c[4];
		};
};




/**
 *************************************************************************
 *
 * @class image
 * 
 * Represents a 4-channel RGBA image.
 *
 * Usage:
 * - Create with image::load("path/to/image.tga")
 *
 ************************************************************************/
class image
{
	public:

		int size_x() const NOTHROW { return size_x_; }
		int size_y() const NOTHROW { return size_y_; }

		const std::vector<unsigned char>& data() const NOTHROW { return data_; }

		color at(int x, int y);

		static std::unique_ptr<image> load(const std::string& path);


	private:

		image(int size_x, int size_y, const std::vector<unsigned char>& data);


		int size_x_;
		int size_y_;
		std::vector<unsigned char> data_;


		static const char tga_header_[12];

		static const int max_size_x_;
		static const int max_size_y_;
};




}; /* namespace biosim */


#endif /* !defined(INCLUDED_IMAGE_HPP) */
