#include "compressor.h"
#include "internal/internal.h"

static
b8 pair_sorter(pallet_data_t& l, pallet_data_t& r){
	return l.repeat_count > r.repeat_count;
}

vec_pallet_data map_sort_by_value(const map_pallet& origin_map){
	vec_pallet_data map_as_vector;
	for (const auto& pair : origin_map){
		const pallet_data_t data = {
			.color = pair.first,
			.repeat_count = pair.second,
		};
		map_as_vector.push_back(data);
	}

	std::sort(map_as_vector.begin(), map_as_vector.end(), pair_sorter);
	return map_as_vector;
}

map_color2bits color2bits_ctor(const vec_pallet_data& pallet, const u8 otherwise_value){
	typedef std::pair<color_t, u8> color2bits_t;

	map_color2bits color2bits;
	const u32 pallet_size = pallet.size();
	for(u32 i = 0; (i < otherwise_value) && (i < pallet_size); i++){
		color2bits.insert(color2bits_t(pallet[i].color, i));
	}
	for(u32 i = otherwise_value; (i < pallet_size); i++){
		color2bits.insert(color2bits_t(pallet[i].color, otherwise_value));
	}
	return color2bits;
}

map_bits2color bits2color_ctor(const vec_pallet_data& pallet, const u8 otherwise_value){
	typedef std::pair<u8, color_t> bits2color_t;
	
	map_bits2color color2bits;
	const u32 pallet_size = pallet.size();
	for(u32 i = 0; (i <= otherwise_value) && (i < pallet_size); i++){
		color2bits.insert(bits2color_t(i, pallet[i].color));
	}
	return color2bits;
}
