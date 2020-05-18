#include "Amask.h"

static u16 string_to_u16(const str& s) {
	u16 result = 0;
	std::stringstream ss(s);
	ss >> result;
	return result;
}

static u16 char_to_u16(const char c) {
	u16 result = c - '0';
	if (c >= 'A' && c <= 'F')
		result = c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		result = c - 'a' + 10;
	return result;
}

static u16 hex_to_u16(const str& s) {
	u16 result = 0;
	str tmp = s.substr(2);
	u16 left = char_to_u16(tmp[0]);
	u16 right = char_to_u16(tmp[1]);
	result = (left << 4) + right;
	return result;
}

static str del_spaces(const str& s) {
	str result("");
	for (auto& i : s) {
		if (i != ' ' && i != '\t' && i != '\n') {
			result += i;
		}
	}
	return result;
}

static vec_str split(const str& s, const char c) {
	vec_str result;
	str tmp("");
	for (u16 i = 0; i < s.length(); i++) {
		if (s[i] != c) {
			tmp += s[i];
		} else {
			result.push_back(del_spaces(tmp));
			tmp = "";
		}
	}
	return result;
}



Amask::Amask(const str& _name, u16 _width, u16 _height, const str& _payload)
{
	name = _name;
	width = _width;
	height = _height;
	vec_str values = split(_payload, ',');
	for (auto& i : values) {
		payload.push_back(hex_to_u16(i));
	}
}

void Amask::ToPng(const str& path) {
	sf::Image* img = new sf::Image();
	const u16 fwidth = width + 1;
	const u16 fheight = height + 1;

	const sf::Color White = sf::Color(255, 255, 255, 0);
	const sf::Color Black = sf::Color(0, 0, 0, 255);

	img->create(fwidth, fheight, White);


	vec_i bits;
	u16 size = fwidth * fheight;
	bits.resize(size);
	u16 index = 0;

	for (u16 i = 0; i < payload.size(); i++) {
		for (u16 j = 0; j < 8; j++) {
			bits[index] = ((payload[i] >> j) & 1);
			index++;
		}
	}

	index = 0;
	for (u16 i = 0; i < fheight; i++) {
		for (u16 j = 0; j < fwidth; j++) {
			if (bits[index]) {
				img->setPixel(j, i, Black);
			}
			index++;
		}
	}
	//std::cout << path + name + ".png" << std::endl;
	img->saveToFile(path + name + ".png");
	delete img;
}

std::vector<Amask*> Amask::ReadFile(const str& path)
{
	std::vector<Amask*> masks;
	std::ifstream file(path);
	vec_str alllines;
	str line("");
	for (str tmp; std::getline(file, tmp);) {
		if (tmp != "\n") {
			line += tmp + "\n";
		}
		if (tmp == "};") {
			alllines.push_back(line);
			line = "";
		}
	}
	std::regex re("\\}\\s*([_\\w\\d]+)\\s*=\\s*\\{\n*\t*\\s*\\.key\\s*=\\s*([\\db]+)\\s*,\n*\t*\\s*\\.width\\s*=\\s*(\\d+),\n*\t*\\s*\\.height\\s*=\\s*(\\d+),\n*\t*\\s*\\.payload\\s*=\\s*\\{([\\w\\d,\\s\t\n]+)\\s*\\},\\s*\n*\\};");
	std::smatch mask_match;
	for (auto i : alllines) {
		if (std::regex_search(i, mask_match, re)) {
			str name(mask_match[1]);
			u16 width = string_to_u16(mask_match[3]);
			u16 height = string_to_u16(mask_match[4]);
			str payload = mask_match[5];
			Amask* mask = new Amask(name, width, height, payload);
			masks.push_back(mask);
		}
	}
	return masks;
}


void Amask::Mask_To_Png(const str& Inpath, const str& Outpath) {
	std::vector<Amask*> masks = Amask::ReadFile(Inpath + "images.c");
	for (auto& i : masks) {
		i->ToPng(Outpath);
		delete i;
	}
}