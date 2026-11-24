#include "compressor.h"
#include "internal/internal.h"
#include <sstream>

typedef vec_u8 (*to_Xbpp_compressor)(const vec_pixels &pixels, const vec_pallet_data &pallet);
typedef vec_pixels (*from_8bpp_decompressor)(const vec_u8 &vec_8bpp, const vec_pallet_data &pallet);

static const
to_Xbpp_compressor compressors[] = {
	[ci_none] = to_8bpp,

	[ci_1bpp] = to_1bpp,
	[ci_2bpp] = to_2bpp,
	[ci_4bpp] = to_4bpp,
	[ci_8bpp] = to_8bpp,

	[ci_1bpp_rle] = to_1bpp_rle,
	[ci_2bpp_rle] = to_2bpp_rle,
	[ci_4bpp_rle] = to_4bpp_rle,
	[ci_8bpp_rle] = to_8bpp_rle,
};

static const
from_8bpp_decompressor decompressors[] = {
	[ci_none] = from_8bpp,

	[ci_1bpp] = from_1bpp,
	[ci_2bpp] = from_2bpp,
	[ci_4bpp] = from_4bpp,
	[ci_8bpp] = from_8bpp,

	[ci_1bpp_rle] = from_1bpp_rle,
	[ci_2bpp_rle] = from_2bpp_rle,
	[ci_4bpp_rle] = from_4bpp_rle,
	[ci_8bpp_rle] = from_8bpp_rle,
};

static const
str ci2name[] = {
	[ci_none] = "none",

	[ci_1bpp] = "1BPP",
	[ci_2bpp] = "2BPP",
	[ci_4bpp] = "4BPP",
	[ci_8bpp] = "8BPP",

	[ci_1bpp_rle] = "1BPP_RLE",
	[ci_2bpp_rle] = "2BPP_RLE",
	[ci_4bpp_rle] = "4BPP_RLE",
	[ci_8bpp_rle] = "8BPP_RLE",
};


compressor::compressor(const fs::path& png_path){
	name = png_path.stem().string();
	img = sf::Image();

	const b8 load_res = img.loadFromFile(png_path.string());
	if(false == load_res){
		return;
	}

	const sf::Vector2u sizes = img.getSize();
	const u32 w = sizes.x;
	const u32 h = sizes.y;

	pixels = vec_pixels(w * h, color_t::Black);
	map_pallet map_pallet;

	for(u32 y = 0; y < h; y++){
		for(u32 x = 0; x < w; x++){
			const color_t color = img.getPixel(x, y);

			const u32 index = x + y * w;
			pixels[index] = color;

			const u32 color_repeat_cnt = map_pallet.count(color);
			if(0 == color_repeat_cnt){
				map_pallet.insert(std::pair<color_t, u32>(color, 1));
			} else {
				map_pallet[color] += 1;
			}
		}
	}

	vec_pallet = map_sort_by_value(map_pallet);
}

std::pair<compressed_images, vec_u8> compressor::best_compress(void){
	std::pair<compressed_images, vec_u8> result = std::pair<compressed_images, vec_u8>(ci_none, vec_u8());
	const size_t pallet_size = vec_pallet.size();
	compressed_images full_type = ci_none;
	compressed_images rle_type = ci_none;

	if(pallet_size > 256){
		std::cout << "pallet overflow: " << pallet_size << std::endl;
		return result;
	} else if(pallet_size <= 2){
		full_type = ci_1bpp;
		rle_type = ci_1bpp_rle;
	} else if(pallet_size <= 4){
		full_type = ci_2bpp;
		rle_type = ci_2bpp_rle;
	} else if(pallet_size <= 16){
		full_type = ci_4bpp;
		rle_type = ci_4bpp_rle;
	} else if(pallet_size <= 256){
		full_type = ci_8bpp;
		rle_type = ci_8bpp_rle;
	}

	vec_u8 compressed_data = compressors[full_type](pixels, vec_pallet);
	vec_u8 compressed_rle_data = compressors[rle_type](pixels, vec_pallet);
	const size_t size = compressed_data.size();
	const size_t rle = compressed_rle_data.size();
	if(size >= rle){
		result.first = rle_type;
		result.second = compressed_rle_data;
	} else {
		result.first = full_type;
		result.second = compressed_data;
	}
	return result;
}

void compressor::save_img(const fs::path& out_path){
	std::pair<compressed_images, vec_u8> best = best_compress();
	const compressed_images type = best.first;
	const vec_u8 compressed_data = best.second;

	const sf::Vector2u sizes = img.getSize();
	const u32 w = sizes.x;
	const u32 h = sizes.y;

	const str path = out_path.string() + name + "_" + ci2name[type] + ".png";
	const vec_pixels image_data = decompressors[type](compressed_data, vec_pallet);
	sf::Image img2save = sf::Image();
	img2save.create(w, h, color_t::White);
	for(u32 y = 0; y < h; y++){
		for(u32 x = 0; x < w; x++){
			const u32 i = x + y * w;
			img2save.setPixel(x, y, image_data[i]);
		}
	}
	img2save.saveToFile(path);
}

str compressor::extern_line(void){
	const str extern_name = "extern const ngimage_t __" + name + ";";
	return extern_name;
}

str compressor::data_line(void){
	std::pair<compressed_images, vec_u8> best = best_compress();
	const compressed_images type = best.first;
	const vec_u8 compressed_data = best.second;
	const size_t data_size = compressed_data.size();

	const sf::Vector2u sizes = img.getSize();
	const u32 w = sizes.x;
	const u32 h = sizes.y;

	str data = "";
	data += "const struct {\n";
	data += "\tng_image_type_t type;\n";
	data += "\tu16 w;\n";
	data += "\tu16 h;\n";
	data += "\tu8 data[" + std::to_string(data_size) + "]\n";
	data += "} __" + name + " = {\n";
	data += "\t.type = NGIT_" + ci2name[type] + ",\n";
	data += "\t.w = " + std::to_string(w) + ",\n";
	data += "\t.h = " + std::to_string(h) + ",\n";
	data += "\t.data = {\n\t\t";
	for (auto d : compressed_data){
		std::stringstream ss("");
		ss << std::hex << "0x" << (u32)d << ", ";
		str d_str;
		ss >> d_str;
		data += d_str;
	}
	data += "\n\t},\n";
	data += "};\n\n";

	return data;
}
