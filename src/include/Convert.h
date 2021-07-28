#pragma once
#include "arch.h"

/// <summary>
/// class for convert funcs
/// </summary>
class Convert{
    public:
        static u16 string_to_u16(const str& s);
        static u16 char_to_u16(const char c);
        static u16 hex_to_u16(const str& s);
        static str u16_to_str(const u16 i);
};