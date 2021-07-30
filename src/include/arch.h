#pragma once
#include <string>
#include <vector>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef std::string str;

typedef std::vector<u16> vec_i;
typedef std::vector<str> vec_str;


#define DBG_LOG()   std::cout << __FILE__ << "\t" << __LINE__ << std::endl

/**
 * settings
*/
/* create compresed masks */
#define COMPRESSED
/* save lowcase name files with '_low' in end */
//#define WORK_WITH_SYMBOL
