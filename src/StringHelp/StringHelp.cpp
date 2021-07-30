#include "StringHelp.h"



str StringHelp::replace(const str& in, const char old, const char newc) {
	str s(in);
	for (u16 i = 0; i < s.length(); i++) {
		if (s[i] == old) {
			s[i] = newc;
		}
	}
	return s;
}

str StringHelp::cut_from_end(const str& name, const str for_cut){
	const size_t len = name.length();
	const size_t pos = name.rfind(for_cut);
    const size_t clen = for_cut.length();
	bool result = false;
	if(pos == len - clen){
		return name.substr(0, pos);
	}
    return name;
}

str StringHelp::del_spaces(const str& s) {
	str result("");
	for (auto& i : s) {
		if (i != ' ' && i != '\t' && i != '\n') {
			result += i;
		}
	}
	return result;
}

vec_str StringHelp::split(const str& s, const char c) {
	vec_str result;
	str tmp("");
	for (u16 i = 0; i < s.length(); i++) {
		if (s[i] != c) {
			tmp += s[i];
		} else {
			result.push_back(del_spaces(tmp));
			tmp = "";
		}
	}
	return result;
}

bool StringHelp::islowcase(str& s){
	for (auto& c : s){
		if(c >= 'A' && c <= 'Z'){
			return false;
		}
	}
	return true;
}
