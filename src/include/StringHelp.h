#pragma once
#include "arch.h"

class StringHelp{
    public:
        static str replace(const str& in, const char old, const char newc);
        static str cut_from_end(const str& name, const str for_cut);
        static str del_spaces(const str& s);
        static vec_str split(const str& s, const char c);
        static bool islowcase(str& s);
};
