#include "paths.h"

/*
find all files and dirs in directory (name)
	@param name [in]
	@param v [out]
	@param check [out]
*/
void read_directory(const std::string& name, std::vector<std::string>& v, std::vector<bool>& check)
{
	std::string pattern(name + "*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			v.push_back(data.cFileName);
			v[v.size() - 1] = name + v[v.size() - 1];
			check.push_back(false);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	for (int i = 0; i < v.size(); i++) {
		std::string tmp = v[i];
		bool read = tmp.rfind('.') == -1;
		if (read && !check[i]) {
			check[i] = true;
			read_directory(v[i] + "/", v, check);
		}
	}
}

std::string replace(std::string in, const char old, const char newc) {
	std::string s(in);
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == old) {
			s[i] = newc;
		}
	}
	return s;
}