// PngToAlfaMask.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "MyImage.h"
#include "Amask.h"
#include "paths.h"


u16 main(u16 argc, const char** argv)
{
	str Inpath;
	str Outpath;
	str Flag("alfa");
	Argvs(argc, argv, Inpath, Outpath, Flag);
	if (Flag == "alfa") {
		MyImage::Png_To_Mask(Inpath, Outpath);
	} else if(Flag == "png"){
		Amask::Mask_To_Png(Inpath, Outpath);
	}
	return 0;
}
