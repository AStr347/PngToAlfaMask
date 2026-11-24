#include "internal/internal.h"

/**
 * @brief Convert u32 pixel data to 1bpp.
 *
 * Bit = 0 for pixels equal to the most-popular color (pallet[0].first), bit = 1 otherwise.
 *
 * @param pixels  [in] flat pixel buffer (e.g. ARGB8888).
 * @param pallet  [in] sorted (color, count) list, [0] = most popular color.
 *
 * @return packed 1bpp bitmap, size = (pixels.size() + 7) / 8.
 */
vec_u8 to_1bpp(const vec_pixels& pixels, const vec_pallet_data& pallet){
	const u32 pallet_size = pallet.size();
	if ((pallet_size < 1) || pixels.empty()){
        return vec_u8();
	}

	map_color2bits color2bits = color2bits_ctor(pallet, 0b1);

	const u32 pixels_size = pixels.size();
	vec_u8 out((pixels_size + 7) / 8, 0);
    for (u32 i = 0; i < pixels_size; ++i) {
        const color_t c = pixels[i];
		const u8 bits = color2bits[c];

		const u32 pos = (i >> 3);
		const u8 shift = (i & 7);
		out[pos] |= bits << shift;
    }
    return out;
}

vec_u8 to_1bpp_rle(const vec_pixels& pixels, const vec_pallet_data& pallet){
	const u32 pallet_size = pallet.size();
	const u8 bpp_cnt = 1;
	const u8 bpp_mask = (1 << bpp_cnt) - 1;

	if ((pallet_size < bpp_cnt) || pixels.empty()){
        return vec_u8();
	}
	

	map_color2bits color2bits = color2bits_ctor(pallet, bpp_mask);

	const size_t pixels_size = pixels.size();
	
	static const u16 prev_cnt_limit = (1 << (8 - bpp_cnt)) - 1;
	u16 prev_cnt = 1;
	u8 prev_bits = color2bits[pixels[0]];

	vec_u8 out;
    for (size_t i = 1; i < pixels_size; ++i) {
        const color_t c = pixels[i];
		const u8 now_bits = color2bits[c];
		const b8 need_push = (prev_bits != now_bits) || (prev_cnt == prev_cnt_limit);
		if(need_push){
			const u8 push_data = ((prev_cnt << bpp_cnt) | prev_bits);
			out.push_back(push_data);
			prev_cnt = 0;
		}

		prev_bits = now_bits;
		prev_cnt++;
    }
	if(0 != prev_cnt){
		const u8 push_data = ((prev_cnt << bpp_cnt) | prev_bits);
		out.push_back(push_data);
	}
    return out;
}

vec_pixels from_1bpp(const vec_u8& vec_1bpp, const vec_pallet_data& pallet){
	map_bits2color bits2color = bits2color_ctor(pallet, 0b1);

	const u32 pixel_cnt = vec_1bpp.size() * 8;
	vec_pixels out(pixel_cnt);

	for(u32 i = 0; i < pixel_cnt; i++){
		const u32 pos = (i >> 3);
		const u8 shift = (i & 7);
		const u8 bits = ((vec_1bpp[pos] >> shift) & 0b1);
		const color_t pixel_value = bits2color[bits];
		out[i] = pixel_value;
	}

	return out;
}

vec_pixels from_1bpp_rle(const vec_u8& vec_data, const vec_pallet_data& pallet){
	const u8 bpp_cnt = 1;
	const u8 bpp_mask = (1 << bpp_cnt) - 1;
	map_bits2color bits2color = bits2color_ctor(pallet, bpp_mask);
	vec_pixels out;

	const size_t vec_size = vec_data.size();
	for(u32 i = 0; i < vec_size; i++){
		const u8 data = vec_data[i];

		const u8 pixle_cnt = data >> bpp_cnt;
		const u8 pixel_bits = data & bpp_mask;
		const color_t pixel_value = bits2color[pixel_bits];
		for(u16 j = 0; j < pixle_cnt; j++){
			out.push_back(pixel_value);
		}
	}

	return out;
}
