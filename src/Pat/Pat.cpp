#include "paths.h"


/// <summary>
/// find all filesand dirs in directory(name)
/// </summary>
/// <param name="v"> ref for output paths vector </param>
/// <param name="check"> vector for recursive check dirs </param>
void read_directory(const str& Inpath, vec_str& v, std::vector<bool>& check)
{
	str pattern(Inpath + "*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			v.push_back(data.cFileName);
			v[v.size() - 1] = Inpath + v[v.size() - 1];
			check.push_back(false);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	for (u16 i = 0; i < v.size(); i++) {
		str tmp = v[i];
		bool read = tmp.rfind('.') == -1;
		if (read && !check[i]) {
			check[i] = true;
			read_directory(v[i] + "/", v, check);
		}
	}
}

str replace(str& in, const char old, const char newc) {
	str s(in);
	for (u16 i = 0; i < s.length(); i++) {
		if (s[i] == old) {
			s[i] = newc;
		}
	}
	return s;
}

/// <summary>
/// init paths and flag from console args
/// </summary>
void Argvs(u16 argc, const char** argv, str& Inpath, str& Outpath, str& Flag) {
	if (argc > 1) {
		Flag = str(argv[1]);
	}

	if (argc > 2) {
		Inpath = str(argv[2]);
	}
	else {
		str sub = str(argv[0]);
		sub = sub.substr(0, sub.rfind('\\') + 1);
		Inpath = sub;
	}
	Inpath = replace(Inpath, '\\', '/');

	if (argc > 3) {
		Outpath = str(argv[3]);
		Outpath = replace(Outpath, '\\', '/');
	}
	else {
		Outpath = Inpath;
	}

	if (Inpath[Inpath.length() - 1] != '/') {
		Inpath += '/';
	}
	if (Outpath[Outpath.length() - 1] != '/') {
		Outpath += '/';
	}
}