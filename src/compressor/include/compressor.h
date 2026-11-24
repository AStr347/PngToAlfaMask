#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include "arch.h"
#include "sfml.h"
#include "boost.h"

typedef sf::Color color_t;
// Структура для сравнения цветов
struct compare_color_t {
    bool operator()(const color_t& left, const color_t& right) const {
        return left.toInteger() < right.toInteger();
    }
};

typedef std::vector<color_t> vec_pixels;
typedef std::map<color_t, u8, compare_color_t> map_color2bits;
typedef std::map<color_t, u32, compare_color_t> map_pallet;
typedef std::map<u8, color_t> map_bits2color;
struct pallet_data_t {
	color_t color;
	u32 repeat_count;
};

enum compressed_images {
	ci_none = 0, // not compressed

	ci_1bpp, // 1 bit per pixel (image have 2 colors)
	ci_2bpp, // 2 bit per pixel (image have 4 colors)
	ci_4bpp, // 4 bit per pixel (image have 16 colors)
	ci_8bpp, // 8 bit per pixel (image have 256 colors)

	ci_1bpp_rle, // 1 bit per pixel (image have 2 colors) + Run-Length Encoding
	ci_2bpp_rle, // 2 bit per pixel (image have 4 colors) + Run-Length Encoding
	ci_4bpp_rle, // 4 bit per pixel (image have 16 colors) + Run-Length Encoding
	ci_8bpp_rle, // 8 bit per pixel (image have 256 colors) + Run-Length Encoding

	ci_32bpp = ci_none, // not compressed
};

typedef std::map<compressed_images, vec_u8> map_ci_vec_u8;
typedef std::vector<pallet_data_t> vec_pallet_data;

class compressor{
	sf::Image img;
	vec_pallet_data vec_pallet;
	vec_pixels pixels;

	std::pair<compressed_images, vec_u8> best_compress(void);

	public:
		str name;
		compressed_images best_type;

		compressor(const fs::path& png_path);
		
		void save_img(const fs::path& out_path);
		str extern_line(void);
		str data_line(void);
};

#endif//COMPRESSOR_H