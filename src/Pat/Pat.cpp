#include "paths.h"
#include "StringHelp.h"

#include "boost/filesystem.hpp"


using namespace boost::filesystem;
struct recursive_directory_range
{
    typedef recursive_directory_iterator iterator;
    recursive_directory_range(path p) : p_(p) {}

    iterator begin() { return recursive_directory_iterator(p_); }
    iterator end() { return recursive_directory_iterator(); }

    path p_;
};

/// <summary>
/// find all files in directory(Inpath)
/// </summary>
/// <param name="v"> ref for output paths vector </param>
/// <param name="check"> vector for recursive check dirs </param>
void read_directory(const str& Inpath, vec_str& v)
{
    for (auto it : recursive_directory_range(Inpath))
    {
		/* replace for windows slash change to universal */
        std::string tmp = StringHelp::replace((it.path().string()), '\\', '/');

        const size_t dot_pos = tmp.rfind('.');
        const size_t slash_pos = tmp.rfind('/');
		/* need only files */
		if((dot_pos != -1) && (slash_pos < dot_pos)){
        	v.push_back(tmp);
		}
    }
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
	} else {
		str sub = str(argv[0]);
		sub = sub.substr(0, sub.rfind('\\') + 1);
		Inpath = sub;
	}
	Inpath = StringHelp::replace(Inpath, '\\', '/');

	if (argc > 3) {
		Outpath = str(argv[3]);
		Outpath = StringHelp::replace(Outpath, '\\', '/');
	} else {
		Outpath = Inpath;
	}

	if (Inpath[Inpath.length() - 1] != '/') {
		Inpath += '/';
	}
	if (Outpath[Outpath.length() - 1] != '/') {
		Outpath += '/';
	}
}