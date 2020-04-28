// PngToAlfaMask.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "MyImage.h"
#include "paths.h"
#include <windows.h>
#include <fstream>



int main(int argc, const char** argv)
{
	std::string Inpath;
	std::string Outpath;
	if (argc > 1) {
		Inpath = std::string(argv[1]);
	} else {
		std::string sub = std::string(argv[0]);
		sub = sub.substr(0, sub.rfind('\\') + 1);
		Inpath = sub;
	}

	Inpath = replace(Inpath, '\\', '/');

	if (argc > 2) {
		Outpath = std::string(argv[2]);
		Outpath = replace(Outpath, '\\', '/');
	} else {
		Outpath = Inpath;
	}


	std::vector<std::string> pngs;
	std::vector<bool> check;
	read_directory(Inpath, pngs, check);

	std::vector<MyImage> imgs;

	for (int i = 0; i < pngs.size(); i++) {
		std::string file = pngs[i];

		u32 len = file.length();

		if (len > 4) {
			std::string sub = file.substr((len - 4), 4);
			if (sub == ".png" || sub == ".bmp") {
				MyImage img(file);
				imgs.push_back(img);
			}
		}
	}

	if (imgs.size() != 0) {
		std::ofstream header(Outpath + "images.h");
		std::ofstream source(Outpath + "images.c");

		source << "#include \"arch.h\"\n\n\n";
		header << "#ifmdef PNGS_H\n#define PNGS_H\n#include \"graphics.h\"\n\n";

		for (int i = 0; i < imgs.size(); i++) {
			header << imgs[i].Extern();
			source << imgs[i].ToString();
		}
		header << "#endif//PNGS_H";
		header.close();
		source.close();
	}

	return 0;
}
