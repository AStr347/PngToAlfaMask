#include "Amask.h"
#include <regex>
#include <fstream>
#include <iostream>
#include <Image.hpp>
#include "Convert.h"
#include "StringHelp.h"



/// <summary>
/// Constructor
/// </summary>
Amask::Amask(const str& _name, u16 _width, u16 _height, const str& _payload)
{
	name = _name;
	width = _width;
	height = _height;
	vec_str values = StringHelp::split(_payload, ',');
	for (auto& i : values) {
		u16 num = Convert::hex_to_u16(i);
		payload.push_back(num);
	}
}

/// <summary>
/// convert mask to png
/// </summary>
void Amask::ToPng(const str& path) {
	sf::Image* img = new sf::Image();
	const u16 fwidth = width + 1;
	const u16 fheight = height + 1;

	const sf::Color White = sf::Color(255, 255, 255, 0);
	const sf::Color Black = sf::Color(0, 0, 0, 255);

	img->create(fwidth, fheight, White);


	vec_i bits;
	u16 size = fwidth * fheight;

	for (u16 i = 0; i < payload.size(); i++) {
		for (u16 j = 0; j < 8; j++) {
			bits.push_back(((payload[i] >> j) & 1));
		}
	}

	u16 index = 0;
	for (u16 i = 0; i < fheight; i++) {
		for (u16 j = 0; j < fwidth; j++) {
			if (bits[index]) {
				img->setPixel(j, i, Black);
			}
			index++;
		}
	}
	str last_name(name);
#ifdef WORK_WITH_SYMBOL
	if(StringHelp::islowcase(last_name)){
		last_name += "_low";
	}
#endif
	if(img->saveToFile(path + last_name + ".png")){
		std::cout << last_name << std::endl;
	}
	delete img;
}

/// <summary>
/// find all alfamasks in file
/// </summary>
void Amask::ReadFile(const str& path, const str& Outpath)
{
	std::ifstream file(path);
	str line("");
	std::regex re("\\}\\s*([_\\w\\d]+)\\s*=\\s*\\{\n*\t*\\s*\\.key\\s*=\\s*([\\db]+)\\s*,\n*\t*\\s*\\.width\\s*=\\s*(\\d+),\n*\t*\\s*\\.height\\s*=\\s*(\\d+),\n*\t*\\s*\\.payload\\s*=\\s*\\{([\\w\\d,\\s\t\n]+)\\s*\\},\\s*\n*\\};");
	
	for (str tmp; std::getline(file, tmp);) {
		if (tmp != "\n") {
			line += tmp + "\n";
		}
		if (tmp == "};") {
			std::smatch* mask_match = new std::smatch();
			if (std::regex_search(line, (*mask_match), re)) {
				if(5 > mask_match->length()){
					std::cout << "that not mask" << std::endl;
				} else {
					str name((*mask_match)[1]);
					u16 width = Convert::string_to_u16((*mask_match)[3]);
					u16 height = Convert::string_to_u16((*mask_match)[4]);
					str payload = (*mask_match)[5];
					Amask* mask = new Amask(name, width, height, payload);
					mask->ToPng(Outpath);
					delete mask;
				}
			}
			line = "";
			delete mask_match;
		}
	}
	file.close();
}

/// <summary>
/// static func for convert all alfamasks from images.c to pngs
/// </summary>
void Amask::Mask_To_Png(const str& Inpath, const str& Outpath) {
	Amask::ReadFile(Inpath + "images.c", Outpath);
}