#pragma once
#include "arch.h"
#include "Image.hpp"

class MyImage
{
	constexpr static const char* keysizes[4] = { "1","2","3","4" };
	constexpr static const char* wsizes[4] = { "3","7","10","14" };
	constexpr static const char* hsizes[4] = { "4","7","11","14" };
	constexpr static const char* bitkeys[4] = { "0b1","0b10","0b100","0b1000" };
	constexpr static u32 wmax[4] = { 0b111, 0b1111111, 0b1111111111, 0b11111111111111 };
	constexpr static u32 hmax[4] = { 0b1111, 0b1111111, 0b11111111111, 0b11111111111111 };
	

	/// <summary>
	/// create not compressed payload
	/// </summary>
	/// <param name="img"> ref to SFML Image </param>
	void PixelsToPayload(sf::Image& img);
	void draw(str s);
	void Compress();

public:
	u32 width = 0;
	u32 height = 0;
	u16 type = 0;
	str name;
	str folder_name;
	vec_i payload;


	/// <summary>
	/// MyImage constructor
	/// open image and fill all need data
	/// </summary>
	/// <param name="path"> path to image </param>
	MyImage(const str& path);

	/// <summary>
	/// return string for image.c file
	/// </summary>
	str ToString();

	/// <summary>
	/// return string for image.h
	/// </summary>
	str Extern();


	/// <summary>
	/// static func for convert all .png/.bmp to alfa masks and write this in images.c and images.h
	/// </summary>
	static void Png_To_Mask(const str& Inpath, const str& Outpath);
};


/// <summary>
/// dbg info output
/// </summary>
extern std::ostream& operator <<(std::ostream& os, MyImage& img);