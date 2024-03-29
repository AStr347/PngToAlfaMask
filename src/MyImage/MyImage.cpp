#include "MyImage.h"
#include "paths.h"
#include <iostream>
#include <fstream>
#include "Convert.h"
#include "StringHelp.h"
#include "CompressedMem.h"


/// <summary>
/// create not compressed payload
/// </summary>
/// <param name="img"> ref to SFML Image </param>
void MyImage::PixelsToPayload(sf::Image& img) {
	vec_i bits;
	/* read all colors from image */
	for (u16 i = 0; i < height; i++) {
		for (u16 j = 0; j < width; j++) {
			u16 color = img.getPixel(j, i).toInteger() == 255 ? 1 : 0;
			bits.push_back(color);
		}
	}

	/* convert bits to u8 values */
	u16 bit = 0;
	u16 bitcount = 0;
	for (u16 i = 0; i < bits.size(); i++) {
		if (bitcount < 7) {
			bit += bits[i] << bitcount;
			bitcount++;
		} else {
			bit += bits[i] << bitcount;
			payload.push_back(bit);
			bit = 0;
			bitcount = 0;
		}
	}
	if(bitcount != 0){
		payload.push_back(bit);
	}
}


/// <summary>
/// MyImage constructor
/// open image and fill all need data
/// </summary>
/// <param name="path"> path to image </param>
MyImage::MyImage(const str& path) {
	sf::Image img;
	if (!img.loadFromFile(path))
		return;
	sf::Vector2u sizes = img.getSize();
	width = sizes.x - 1;
	height = sizes.y - 1;

	/* get file name */
	const size_t begin = path.rfind('/') + 1;
	const size_t count = path.rfind('.') - begin;
	name = path.substr((size_t)begin, (size_t)count);
	name = StringHelp::cut_from_end(name, "_low");
	
	/* get folder name */
	const size_t fbegin = path.rfind('/', begin - 2) + 1;
	const size_t fcount = path.rfind('/', begin) - fbegin;
	folder_name = path.substr((size_t)fbegin, (size_t)fcount);

	/* set bits sizes in struct */
	u16 wtype = 0;
	u16 htype = 0;

	for (u16 i = 0; width > wmax[i]; i++) {
		wtype = i;
	}

	for (u16 i = 0; height > hmax[i]; i++) {
		htype = i;
	}

	type = (wtype > htype ? wtype : htype) + 1;

	/* inc sizes for work with image */
	width++;
	height++;
	/* fill payload */
	PixelsToPayload(img);
}


/// <summary>
/// return string for image.c file
/// </summary>
str  MyImage::ToString() {
	str spayload = "";
#ifdef COMPRESSED
	Compress();
#endif
	/* cre string with payload */
	for (u16 i = 0; i < payload.size(); i++) {
		const str hex = Convert::u16_to_hex(payload[i]);
		spayload += hex + ", ";
	}

	/* cre string for output */
	str s = "";
	s += "const struct {\n\tunsigned key : " + str(keysizes[type]) + ";\n\t";
	s += "unsigned width : " + str(wsizes[type]) + ";\n\t";
	s += "unsigned height : " + str(hsizes[type]) + ";\n\t";
	s += "u8 payload[" + std::to_string(payload.size()) + "];\n";
	s += "} " + name + " __attribute__((section (\"" + folder_name + "\"))) = {\n\t";
	s += ".key = " + str(bitkeys[type]) + ",\n\t";
	s += ".width = " + std::to_string(width - 1) + ",\n\t";
	s += ".height = " + std::to_string(height - 1) + ",\n\t";
	s += ".payload = {" + spayload + "},\n";
	s += "};\n\n";
	return s;
}

/// <summary>
/// return string for image.h
/// </summary>
str  MyImage::Extern() {
	return "extern const amask_t " + name + ";\n\n";
}


/// <summary>
/// dbg info output
/// </summary>
std::ostream& operator <<(std::ostream& os, MyImage& img) {
	os << "width = " << img.width << "\theight = " << img.height << std::endl << std::hex;
	for (u16 i = 0; i < img.payload.size(); i++){
		os << img.payload[i] << " ";
	}
	os << std::dec << std::endl;
	return os;
}

/// <summary>
/// static func for convert all .png/.bmp to alfa masks and write this in images.c and images.h
/// </summary>
void MyImage::Png_To_Mask(const str& Inpath, const str& Outpath) {
	vec_str pngs;
	/* get all files in dir and subdirs */
	read_directory(Inpath, pngs);

	std::vector<MyImage> imgs;
	/* get only images .png/.bmp */
	for (u16 i = 0; i < pngs.size(); i++) {
		str file = pngs[i];
		const size_t len = file.length();

		if (len > 4) {
			str sub = file.substr((size_t)(len - 4), 4);
			if (sub == ".png" || sub == ".bmp") {
				MyImage img(file);
				imgs.push_back(img);
			}
		}
	}
	/* if we have images write all in images.h and images.c */
	if (imgs.size() != 0) {
		std::ofstream header(Outpath + "images.h");
		std::ofstream source(Outpath + "images.c");

		source << "#include \"arch.h\"\n\n\n";
		header << "#ifndef IMAGES_H\n#define IMAGES_H\n#include \"graphics.h\"\n\n";

		for (u16 i = 0; i < imgs.size(); i++) {
			header << imgs[i].Extern();
			source << imgs[i].ToString();
		}
		header << "#endif//IMAGES_H";
		header.close();
		source.close();
	} else {
		std::cout << "Images not found" << std::endl;
	}
}

void MyImage::Compress() {
	str fill = "";
	for (auto i : payload){
		fill += Convert::u8_to_bin((u8)i);
	}
	payload = CompressedMem::from_string(fill);
#ifdef __DEBUG
	//draw(fill); 
	str dbg_fill = "";
	for (auto i : payload){
		std::cout << i << '\t';
		if((i>>7) == 1){
			const u8 cnt = (i & 0b00111111) + 7;
			const u8 color = ((i >> 6) & 1);
			str bits(cnt ,'0'+ color);
			dbg_fill += bits;
		} else {
			str bits = Convert::u8_to_bin((u8)i).substr(0, 7);
			std::reverse(bits.begin(), bits.end());
			dbg_fill += bits;
		}
	}
	std::cout << (fill == dbg_fill) << std::endl;
	draw(dbg_fill);
#endif
}

/**
 * show image in console throw 0 and 1
*/
void MyImage::draw(str s){
	u32 index = 0;
	const u32 w = width;
	for(auto c : s){
		std::cout << c;
		index++;
		if(index % w == 0){
			std::cout << std::endl;
			index = 0;
		}
	}
	std::cout << "\n\n\n" << std::endl;
}
