#pragma once
#include "arch.h"
struct CompressedMem {
	bool monochrom = true;
	str bits = "";
	int len = 0;

	CompressedMem(const char firstbit);
	/**
	 * add 1 bit to bits if can
	 * @param bit 	- [in] bit for add '1' or '0'
	 * @return 		- true if CompressedMem fill end, false if can fill more
	*/
	bool add_bit(const char bit);

public:
	u16 to_u16();

	str toString();

	static vec_i from_string(str& s);
};
