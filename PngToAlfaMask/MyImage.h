#pragma once
#include <iostream>
#include <Image.hpp>
#include <string>
#include <vector>
#include <sstream>

typedef unsigned int u16;
typedef unsigned long long u32;

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
	std::string name;
	std::vector<u16> payload;

	MyImage(std::string path);
	std::string ToString();
	std::string Extern();
};

extern std::string To_Hex(u16 i);
extern std::ostream& operator <<(std::ostream& os, MyImage& img);