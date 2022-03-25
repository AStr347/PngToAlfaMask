#pragma once
#include <string>
#include <vector>
#include "arch.h"

/// <summary>
/// find all files in directory(Inpath)
/// </summary>
/// <param name="v"> ref for output paths vector </param>
/// <param name="check"> vector for recursive check dirs </param>
extern void read_directory(const str& name, vec_str& v);


/// <summary>
/// init paths and flag from console args
/// </summary>
extern void Argvs(u16 argc, const char** argv, str& Inpath, str& Outpath, str& Flag);
