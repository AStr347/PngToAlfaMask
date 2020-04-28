#include "MyImage.h"


void MyImage::PixelsToPayload(sf::Image& img) {
	std::vector<u16> bits;
	for (u16 i = 0; i < height; i++) {
		for (u16 j = 0; j < width; j++) {
			u16 color = img.getPixel(j, i).toInteger() == 255 ? 1 : 0;
			bits.push_back(color);
		}
	}

	u16 bit = 0;
	u16 bitcount = 0;
	for (u16 i = 0; i < bits.size(); i++) {
		if (bitcount < 7) {
			bit += bits[i] << bitcount;
			bitcount++;
		}
		else {
			bit += bits[i] << bitcount;
			payload.push_back(bit);
			bit = 0;
			bitcount = 0;
		}
	}


}

MyImage::MyImage(std::string path) {
	sf::Image img;
	if (!img.loadFromFile(path))
		return;
	sf::Vector2u sizes = img.getSize();
	width = sizes.x - 1;
	height = sizes.y - 1;
	u32 begin = path.rfind('/') + 1;
	u32 count = path.rfind('.') - begin;
	name = "__" + path.substr(begin, count) + "_png";

	u16 wtype = 0;
	u16 htype = 0;

	for (u16 i = 0; width > wmax[i]; i++) {
		wtype = i;
	}

	for (u16 i = 0; height > hmax[i]; i++) {
		htype = i;
	}

	type = (wtype > htype ? wtype : htype);

	width++;
	height++;

	PixelsToPayload(img);
}

std::string  MyImage::ToString() {
	std::string spayload = "";

	for (int i = 0; i < payload.size(); i++) {
		spayload += To_Hex(payload[i]) + ", ";
	}

	std::string s = "";
	s += "struct {\n\tunsigned key : " + std::string(keysizes[type]) + ";\n\t";
	s += "unsigned width : " + std::string(wsizes[type]) + ";\n\t";
	s += "unsigned height: " + std::string(hsizes[type]) + ";\n\t";
	s += "u8 payload[" + std::to_string(payload.size()) + "];\n";
	s += "} " + name + " = {\n\t";
	s += ".key = " + std::string(bitkeys[type]) + ",\n\t";
	s += ".width = " + std::to_string(width - 1) + ",\n\t";
	s += ".height = " + std::to_string(height - 1) + ",\n\t";
	s += ".payload = {" + spayload + "},\n";
	s += "}\n\n";
	return s;
}

std::string  MyImage::Extern() {
	return "extern amask_t " + name + ";\n\n";
}

std::string To_Hex(u16 i) {
	std::string s = "0x";
	if (i < 0x10) {
		s += "0";
	}
	std::stringstream ss;
	ss << s << std::hex << i;
	std::string result;
	ss >> result;
	return result;
}


std::ostream& operator <<(std::ostream& os, MyImage& img) {
	os << "width = " << img.width << "\theight = " << img.height << std::endl << std::hex;
	for (u16 i = 0; i < img.payload.size(); i++)
		os << img.payload[i] << " ";
	os << std::dec << std::endl;
	return os;
}