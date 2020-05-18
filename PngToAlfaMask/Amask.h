#pragma once
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>
#include <Image.hpp>
#include "arch.h"

class Amask
{
public:
	str name;
	u16 width;
	u16 height;
	vec_i payload;

	Amask(const str& _name, u16 _width, u16 _height,const str& _payload);
	void ToPng(const str& path);
	static std::vector<Amask*> ReadFile(const str& path);
	static void Mask_To_Png(const str& Inpath, const str& Outpath);
};

