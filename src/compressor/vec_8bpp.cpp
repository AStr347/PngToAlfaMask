#include "internal/internal.h"

/**
 * @brief Convert u32 pixel data to 2bpp.
 *
 * Bit = 0000 for pixels equal to pallet[0].first
 * Bit = 0001 for pixels equal to pallet[1].first
 * Bit = 0010 for pixels equal to pallet[2].first
 * Bit = 0011 for pixels equal to pallet[3].first
 * ...
 * Bit = 1111 otherwise
 *
 * @param pixels  [in] flat pixel buffer (e.g. ARGB8888).
 * @param pallet  [in] sorted (color, count) list, [0] = most popular color.
 *
 * @return packed 2bpp bitmap.
 */
vec_u8 to_8bpp(const vec_pixels& pixels, const vec_pallet_data& pallet){
	const u32 pallet_size = pallet.size();
	if ((pallet_size < 1) || pixels.empty()){
        return vec_u8();
	}

	map_color2bits color2bits = color2bits_ctor(pallet, 0b11111111);

	const u32 pixels_size = pixels.size();
	vec_u8 out(pixels_size, 0);
	for (u32 i = 0; i < pixels_size; ++i) {
		const color_t c = pixels[i];
		const u8 bits = color2bits[c];

		const u32 pos = i;
        const u8 shift = 0;
		out[pos] |= bits << shift;
	}
	return out;
}

vec_u8 to_8bpp_rle(const vec_pixels& pixels, const vec_pallet_data& pallet){
	const u32 pallet_size = pallet.size();
	const u8 bpp_cnt = 8;
	const u8 bpp_mask = (1 << bpp_cnt) - 1;

	if ((pallet_size < bpp_cnt) || pixels.empty()){
        return vec_u8();
	}
	

	map_color2bits color2bits = color2bits_ctor(pallet, bpp_mask);

	const size_t pixels_size = pixels.size();
	
	static const u16 prev_cnt_limit = (1 << (16 - bpp_cnt)) - 1;
	u16 prev_cnt = 1;
	u8 prev_bits = color2bits[pixels[0]];

	vec_u8 out;
    for (size_t i = 1; i < pixels_size; ++i) {
        const color_t c = pixels[i];
		const u8 now_bits = color2bits[c];
		const b8 need_push = (prev_bits != now_bits) || (prev_cnt == prev_cnt_limit);
		if(need_push){
			const u16 push_data = ((prev_cnt << bpp_cnt) | prev_bits);
			const u8 hi = ((push_data >> 8) & 0xff);
			const u8 lo = ((push_data >> 0) & 0xff);
			out.push_back(hi);
			out.push_back(lo);
			prev_cnt = 0;
		}

		prev_bits = now_bits;
		prev_cnt++;
    }
	if(0 != prev_cnt){
		const u16 push_data = ((prev_cnt << bpp_cnt) | prev_bits);
		const u8 hi = ((push_data >> 8) & 0xff);
		const u8 lo = ((push_data >> 0) & 0xff);
		out.push_back(hi);
		out.push_back(lo);
	}
    return out;
}

vec_pixels from_8bpp(const vec_u8& vec_8bpp, const vec_pallet_data& pallet){
	map_bits2color  bits2color = bits2color_ctor(pallet, 0b11111111);

	const u32 pixel_cnt = vec_8bpp.size();
	vec_pixels out(pixel_cnt);

	for(u32 i = 0; i < pixel_cnt; i++){
		const u32 pos = i;
		const u8 shift = 0;
		const u8 bits = ((vec_8bpp[pos] >> shift) & 0b11111111);
		const color_t pixel_value = bits2color[bits];
		out[i] = pixel_value;
	}

	return out;
}

vec_pixels from_8bpp_rle(const vec_u8& vec_data, const vec_pallet_data& pallet){
	const u8 bpp_cnt = 8;
	const u8 bpp_mask = (1 << bpp_cnt) - 1;
	map_bits2color bits2color = bits2color_ctor(pallet, bpp_mask);
	vec_pixels out;

	const size_t vec_size = vec_data.size();
	if((vec_size & 1) != 0){
		return out;
	}
	for(u32 i = 0; i < vec_size; i+=2){
		const u8 hi = vec_data[i];
		const u8 lo = vec_data[i+1];
		const u16 data = (hi << 8) | (lo << 0);

		const u16 pixle_cnt = data >> bpp_cnt;
		const u8 pixel_bits = data & bpp_mask;
		const color_t pixel_value = bits2color[pixel_bits];
		for(u16 j = 0; j < pixle_cnt; j++){
			out.push_back(pixel_value);
		}
	}

	return out;
}
