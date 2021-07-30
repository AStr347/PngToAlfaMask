#include "Convert.h"
#include <sstream>

u16 Convert::string_to_u16(const str& s) {
	u16 result = 0;
	std::stringstream ss(s);
	ss >> result;
	return result;
}

u16 Convert::char_to_u16(const char c) {
	u16 result = c - '0';
	if (c >= 'A' && c <= 'F')
		result = c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		result = c - 'a' + 10;
	return result;
}

u16 Convert::hex_to_u16(const str& s) {
	u16 result = 0;
	str tmp = s.substr(2);
	u16 left = char_to_u16(tmp[0]);
	u16 right = char_to_u16(tmp[1]);
	result = (left << 4) + right;
	return result;
}

/// <summary>
/// convert u16(u8) to hex string
/// </summary>
str Convert::u16_to_hex(const u16 i) {
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

u16 Convert::bin_to_u16(const str& s){
	u16 result = 0;
	for(auto c : s){
		u16 bit = char_to_u16(c);
		result <<= 1;
		result += bit;
	}
	return result;
}


str Convert::u8_to_bin(const u8 num){
	str result("");
	for (int i = 0; i < 8; i++){
		result += '0' + ((num >> i) & 1);
	}
	return result;
}
