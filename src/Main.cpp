// PngToAlfaMask.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "MyImage.h"
#include "Amask.h"
#include "paths.h"
#include "arch.h"

/// <summary>
/// main
/// </summary>
/// <param name="argv"> need flag alfa - convert images to alfamasks; png - convert masks to images </param>
int main(int argc, const char** argv)
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
