#pragma once
#include <string>
#include <vector>
typedef unsigned int u16;
typedef unsigned long long u32;
typedef std::string str;

typedef std::vector<u16> vec_i;
typedef std::vector<str> vec_str;


#define DBG_LOG()   std::cout << __LINE__ << std::endl
