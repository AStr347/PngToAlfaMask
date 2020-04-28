#pragma once
#include <windows.h>
#include <string>
#include <vector>


#define NOT_FOUND 18446744073709551615


extern void read_directory(const std::string& name, std::vector<std::string>& v, std::vector<bool>& check);

extern std::string replace(std::string in, const char old, const char newc);