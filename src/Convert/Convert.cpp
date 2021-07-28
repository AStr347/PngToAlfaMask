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
str Convert::u16_to_str(const u16 i) {
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
