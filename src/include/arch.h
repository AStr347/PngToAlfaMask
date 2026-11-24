#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef bool b8;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef std::string str;
typedef std::vector<u8> vec_u8;
typedef std::vector<u16> vec_i;
typedef std::vector<u16> vec_u16;
typedef std::vector<u32> vec_u32;
typedef std::vector<str> vec_str;


#define DBG_LOG()   std::cout << __FILE__ << "\t" << __LINE__ << std::endl

/**
 * settings
*/
/* create compresed masks */
#define COMPRESSED
/* save lowcase name files with '_low' in end */
//#define WORK_WITH_SYMBOL
/* add __attribute__(section ("{dir_name}")) */
//#define WORK_WITH_SECTIONS
