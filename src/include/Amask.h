#pragma once
#include "arch.h"

class Amask
{
public:
	str name;
	u16 width;
	u16 height;
	vec_i payload;
	
	/// <summary>
	/// Constructor
	/// </summary>
	Amask(const str& _name, u16 _width, u16 _height,const str& _payload);
	
	/// <summary>
	/// convert mask to png
	/// </summary>
	void ToPng(const str& path);

	/// <summary>
	/// find all alfamasks in file
	/// </summary>
	static std::vector<Amask*> ReadFile(const str& path);
	
	/// <summary>
	/// static func for convert all alfamasks from images.c to pngs
	/// </summary>
	static void Mask_To_Png(const str& Inpath, const str& Outpath);
};

