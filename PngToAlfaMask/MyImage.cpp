#include "MyImage.h"
#include "paths.h"

void MyImage::PixelsToPayload(sf::Image& img) {
	vec_i bits;
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

MyImage::MyImage(const str& path) {
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

	type = (wtype > htype ? wtype : htype) + 1;

	width++;
	height++;

	PixelsToPayload(img);
}

str  MyImage::ToString() {
	str spayload = "";

	for (u16 i = 0; i < payload.size(); i++) {
		spayload += To_Hex(payload[i]) + ", ";
	}

	str s = "";
	s += "const struct {\n\tunsigned key : " + str(keysizes[type]) + ";\n\t";
	s += "unsigned width : " + str(wsizes[type]) + ";\n\t";
	s += "unsigned height : " + str(hsizes[type]) + ";\n\t";
	s += "u8 payload[" + std::to_string(payload.size()) + "];\n";
	s += "} " + name + " = {\n\t";
	s += ".key = " + str(bitkeys[type]) + ",\n\t";
	s += ".width = " + std::to_string(width - 1) + ",\n\t";
	s += ".height = " + std::to_string(height - 1) + ",\n\t";
	s += ".payload = {" + spayload + "},\n";
	s += "};\n\n";
	return s;
}

str  MyImage::Extern() {
	return "extern amask_t " + name + ";\n\n";
}

str To_Hex(u16 i) {
	str s = "0x";
	if (i < 0x10) {
		s += "0";
	}
	std::stringstream ss;
	ss << s << std::hex << i;
	str result;
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


void MyImage::Png_To_Mask(const str& Inpath, const str& Outpath) {
	vec_str pngs;
	std::vector<bool> check;
	read_directory(Inpath, pngs, check);

	std::vector<MyImage> imgs;

	for (u16 i = 0; i < pngs.size(); i++) {
		str file = pngs[i];

		u32 len = file.length();

		if (len > 4) {
			str sub = file.substr((len - 4), 4);
			if (sub == ".png" || sub == ".bmp") {
				MyImage img(file);
				imgs.push_back(img);
			}
		}
	}

	if (imgs.size() != 0) {
		std::ofstream header(Outpath + "images.h");
		std::ofstream source(Outpath + "images.c");

		source << "#include \"arch.h\"\n\n\n";
		header << "#ifmdef PNGS_H\n#define PNGS_H\n#include \"graphics.h\"\n\n";

		for (u16 i = 0; i < imgs.size(); i++) {
			header << imgs[i].Extern();
			source << imgs[i].ToString();
		}
		header << "#endif//PNGS_H";
		header.close();
		source.close();
	}
}