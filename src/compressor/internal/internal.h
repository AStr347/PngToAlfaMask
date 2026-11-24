#ifndef COMPRESSOR_INTERNAL_H
#define COMPRESSOR_INTERNAL_H
#include "compressor.h"

extern
vec_pallet_data map_sort_by_value(const map_pallet& origin_map);

extern
map_color2bits color2bits_ctor(const vec_pallet_data& pallet, const u8 otherwise_value);

extern
map_bits2color bits2color_ctor(const vec_pallet_data& pallet, const u8 otherwise_value);

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
extern
vec_u8 to_1bpp(const vec_pixels& pixels, const vec_pallet_data& pallet);

extern
vec_u8 to_1bpp_rle(const vec_pixels& pixels, const vec_pallet_data& pallet);

extern
vec_pixels from_1bpp(const vec_u8& vec_1bpp, const vec_pallet_data& pallet);

extern
vec_pixels from_1bpp_rle(const vec_u8& vec_data, const vec_pallet_data& pallet);

/**
 * @brief Convert u32 pixel data to 2bpp.
 *
 * Bit = 00 for pixels equal to pallet[0].first
 * Bit = 01 for pixels equal to pallet[1].first
 * Bit = 10 for pixels equal to pallet[2].first
 * Bit = 11 otherwise
 *
 * @param pixels  [in] flat pixel buffer (e.g. ARGB8888).
 * @param pallet  [in] sorted (color, count) list, [0] = most popular color.
 *
 * @return packed 2bpp bitmap.
 */
extern
vec_u8 to_2bpp(const vec_pixels& pixels, const vec_pallet_data& pallet);

extern
vec_u8 to_2bpp_rle(const vec_pixels& pixels, const vec_pallet_data& pallet);

extern
vec_pixels from_2bpp(const vec_u8& vec_2bpp, const vec_pallet_data& pallet);

extern
vec_pixels from_2bpp_rle(const vec_u8& vec_data, const vec_pallet_data& pallet);

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
extern
vec_u8 to_4bpp(const vec_pixels& pixels, const vec_pallet_data& pallet);

extern
vec_u8 to_4bpp_rle(const vec_pixels& pixels, const vec_pallet_data& pallet);

extern
vec_pixels from_4bpp(const vec_u8& vec_4bpp, const vec_pallet_data& pallet);

extern
vec_pixels from_4bpp_rle(const vec_u8& vec_data, const vec_pallet_data& pallet);

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
extern
vec_u8 to_8bpp(const vec_pixels& pixels, const vec_pallet_data& pallet);

extern
vec_u8 to_8bpp_rle(const vec_pixels& pixels, const vec_pallet_data& pallet);

extern
vec_pixels from_8bpp(const vec_u8& vec_8bpp, const vec_pallet_data& pallet);

extern
vec_pixels from_8bpp_rle(const vec_u8& vec_data, const vec_pallet_data& pallet);

#endif//COMPRESSOR_INTERNAL_H