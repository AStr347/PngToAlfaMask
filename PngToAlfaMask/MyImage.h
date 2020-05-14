#pragma once
#include <iostream>
#include <Image.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "arch.h"

class MyImage
{
	constexpr static const char* keysizes[4] = { "1","2","3","4" };
	constexpr static const char* wsizes[4] = { "3","7","10","14" };
	constexpr static const char* hsizes[4] = { "4","7","11","14" };
	constexpr static const char* bitkeys[4] = { "0b1","0b10","0b100","0b1000" };
	constexpr static u32 wmax[4] = { 0b111, 0b1111111, 0b1111111111, 0b11111111111111 };
	constexpr static u32 hmax[4] = { 0b1111, 0b1111111, 0b11111111111, 0b11111111111111 };
	
	void PixelsToPayload(sf::Image& img);

public:
	u32 width = 0;
	u32 height = 0;
	u16 type = 0;
	str name;
	vec_i payload;

	MyImage(const str& path);
	str ToString();
	str Extern();
	static void Png_To_Mask(const str& Inpath, const str& Outpath);
};

extern str To_Hex(u16 i);
extern std::ostream& operator <<(std::ostream& os, MyImage& img);