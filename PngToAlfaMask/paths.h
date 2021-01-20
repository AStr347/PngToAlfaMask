#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "arch.h"

#define NOT_FOUND 18446744073709551615

/// <summary>
/// find all filesand dirs in directory(name)
/// </summary>
/// <param name="v"> ref for output paths vector </param>
/// <param name="check"> vector for recursive check dirs </param>
extern void read_directory(const str& name, vec_str& v, std::vector<bool>& check);

extern str replace(str& in, const char old, const char newc);


/// <summary>
/// init paths and flag from console args
/// </summary>
extern void Argvs(u16 argc, const char** argv, str& Inpath, str& Outpath, str& Flag);