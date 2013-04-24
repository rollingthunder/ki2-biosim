/**
 *************************************************************************
 *
 * @file image.cpp
 *
 * Management of input images, implementation.
 *
 ************************************************************************/


#include "image.hpp"


#include <iostream>
#include <fstream>


#include "exception.hpp"


namespace biosim
{


//////////////////////////////////////////////////////////////////////////
//
// image
//
//////////////////////////////////////////////////////////////////////////


color image::at(int x, int y)
{
	if (x < 0 || y < 0 ||
		x >= size_x_ || y >= size_y_)
	{
		std::cerr << "Pixel index out of bounds." << std::endl;
		throw invalid_parameter();
	}

	return color(data_[(y * size_x_ + x) * 4],
				 data_[(y * size_x_ + x) * 4 + 1],
				 data_[(y * size_x_ + x) * 4 + 2],
				 data_[(y * size_x_ + x) * 4] + 3);
}


std::unique_ptr<image> image::load(const std::string& path)
{
	std::ifstream input(path, std::ifstream::binary);

	if (!input)
	{
		std::cerr << "Could not open file: " << path << std::endl;
		throw file_operation_failed();
	}


	// Extract header, resolution, bitdepth, and
	// check these with bounds. Finally, the last byte
	// of the header is ignored on purpose.
	char header[12];
	input.read(header, 12);

	if (memcmp(header, tga_header_, 12)	 != 0)
	{
		std::cerr << "Corrupt or unsupported targa header." << std::endl;
		throw corrupt_data();
	}

	unsigned short size_x;
	input.read(reinterpret_cast<char*>(&size_x),
			   sizeof(unsigned short));
	unsigned short size_y;
	input.read(reinterpret_cast<char*>(&size_y),
			   sizeof(unsigned short));

	if (size_x <= 0 || size_x > max_size_x_ ||
		size_y <= 0 || size_y > max_size_y_)
	{
		std::cerr << "Targa resolution not supported." << std::endl;
		throw bounds_exceeded();
	}

	unsigned char bit_depth;
	input.read(reinterpret_cast<char*>(&bit_depth),
			   sizeof(unsigned char));
	int bytes_per_pixel = bit_depth / 8;

	if (bytes_per_pixel != 3 && bytes_per_pixel != 4)
	{
		std::cerr << "Targa bitdepth not supported." << std::endl;
		throw unsupported_feature();
	}

	input.seekg(1, std::ifstream::cur);


	// Allocate image storage and read in image data.
	//
	// We need to fix a few things along the way:
	// - Targas are stored bottom-up, we store top-down.
	// - Targa colors are BGRA, and hence need to be switched.
	// - Targa 24 bit images need to be inflated to 32 bit.
	//
	// Idea: Handle entire rows at a time for performance.
	std::vector<unsigned char> data;	

	data.resize(size_x * size_y * 4);

	std::vector<unsigned char> row_buffer;
	row_buffer.resize(size_x * bytes_per_pixel);

	for (int y = 0; y < size_y; ++y)
	{
		input.read(reinterpret_cast<char*>(&row_buffer.front()),
				   size_x * bytes_per_pixel);

		unsigned char* target_row =
			&data[(size_y - 1 - y) * size_x * 4];

		if (bytes_per_pixel == 3)
		{
			for (int i = 0; i < size_x; ++i)
			{
				target_row[i * 4] = row_buffer[i * 3 + 2];
				target_row[i * 4 + 1] = row_buffer[i * 3 + 1];
				target_row[i * 4 + 2] = row_buffer[i * 3];
				target_row[i * 4 + 3] = 255;
			}
		}
		else if (bytes_per_pixel == 4)
		{
			for (int i = 0; i < size_x; ++i)
			{
				target_row[i * 4] = row_buffer[i * 4 + 2];
				target_row[i * 4 + 1] = row_buffer[i * 4 + 1];
				target_row[i * 4 + 2] = row_buffer[i * 4];
				target_row[i * 4 + 3] = row_buffer[i * 4 + 3];
			}		
		}
		else
		{
			std::cerr << "Image loading accepted TGA file with invalid bitdepth." << std::endl;
			throw assert_failed();
		}
	}

	return std::unique_ptr<image>(new image(size_x, size_y, data));
}


image::image(int size_x, int size_y, const std::vector<unsigned char>& data)
	: size_x_(size_x), size_y_(size_y), data_(data)
{
	if (size_x_ < 0 || size_y_ < 0 ||
		size_x_ > max_size_x_ || size_y_ > max_size_y_)
	{
		std::cerr << "Image exceeds maximum allowed bounds." << std::endl;
		throw bounds_exceeded();
	}

	if (data_.size() != size_x_ * size_y_ * 4)
	{
		std::cerr << "Mismatch between image size and allocated data." << std::endl;
		throw invalid_parameter();
	}
}


const char image::tga_header_[12] =
		{ 0, 0, 2, 0,  0, 0, 0, 0,  0, 0, 0, 0 };

const int image::max_size_x_ = 512;
const int image::max_size_y_ = 512;




} /* namespace biosim */
