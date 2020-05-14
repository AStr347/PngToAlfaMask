#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "arch.h"

#define NOT_FOUND 18446744073709551615


extern void read_directory(const str& name, vec_str& v, std::vector<bool>& check);

extern str replace(str& in, const char old, const char newc);

extern void Argvs(u16 argc, const char** argv, str& Inpath, str& Outpath, str& Flag);