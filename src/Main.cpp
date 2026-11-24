// PngToAlfaMask.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "arch.h"
#include "boost.h"
#include "compressor.h"
#include <fstream>

int compress(fs::path& cip, fs::path& cop){
	// check cip
	const b8 cip_is_exist = fs::exists(cip);
	const b8 cip_is_dir = fs::is_directory(cip);
	if(false == cip_is_exist || false == cip_is_dir){
		std::cout << "cip not exist or not dir" << std::endl;
		return -__LINE__;
	}

	// find all png files
	std::vector<fs::path> pngs;
	for (const auto& entry : fs::recursive_directory_iterator(cip)) {
		fs::path p = entry.path();
		const b8 is_dir = fs::is_directory(p);
		if(true == is_dir){
			continue;
		}
		const str extension = p.extension().string();
		const b8 is_png = (extension == ".png");
		if(false == is_png){
			continue;
		}
		pngs.push_back(p);
	}

	const u32 pngs_count = pngs.size();
	if(0 == pngs_count){
		std::cout << "cip have no `*.png` files" << std::endl;
		return -__LINE__;
	}

	std::ofstream images_h(cop.string() + "/images.h", std::ios_base::out);
	images_h << "#ifndef IMAGES_H" << std::endl;
	images_h << "#define IMAGES_H" << std::endl;
	images_h << "#include \"ia_arch.h\"" << std::endl;
	images_h << "#include \"image.h\"\n\n\n" << std::endl;

	std::ofstream images_c(cop.string() + "/images.c", std::ios_base::out);
	images_c << "#include \"ia_arch.h\"" << std::endl;
	images_c << "#include \"image.h\"\n\n\n" << std::endl;

	for(u32 i = 0; i < pngs_count; i++){
		compressor c = compressor(pngs[i]);
		images_h << c.extern_line() << std::endl;
		images_c << c.data_line() << std::endl;
		//c.save_img("./dop/");
	}
	images_h << "\n\n\n#endif//IMAGES_H" << std::endl;
	images_h.close();

	images_c.close();
	
	return 0;
}

int decompress(fs::path& dip, fs::path& dop){
	std::cout << dip << std::endl;
	std::cout << dop << std::endl;
	return 0;
}

int main(int argc, const char** argv)
{
	fs::path pwd = fs::current_path();

#if defined(__DEBUG)
	str compress_in_path("./cip");
	str compress_out_path("./cip");
	str decompress_in_path("./cip");
	str decompress_out_path("./dop");
#else
	str compress_in_path(pwd.string() + "/imgs");
	str compress_out_path(pwd.string() + "/images");
	str decompress_in_path(pwd.string() + "/images");
	str decompress_out_path(pwd.string() + "/imgs");
#endif

	po::options_description desc("PngCompressor v26.11.03");
	{
		desc.add_options()
		("help,h", "Show this help message")
		("cip", po::value<str>(&compress_in_path), "Path to files to be compressed")
		("cop", po::value<str>(&compress_out_path), "Path to compression results")
		("dip", po::value<str>(&decompress_in_path), "Path to files to be decompressed")
		("dop", po::value<str>(&decompress_out_path), "Path to decompression results");
	}
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

#if defined(__DEBUG)
	fs::path cip(compress_in_path);
	fs::path cop(compress_out_path);
	return compress(cip, cop);
#else
	if (vm.empty() || (0 != vm.count("help"))) {
		// desc можно сразу выводить в поток для красивого вывода хелпа
		std::cout << desc << std::endl;
		return 0;
	}

	if(0 != vm.count("cip") || 0 != vm.count("cop")){
		fs::path cip(compress_in_path);
		fs::path cop(compress_out_path);
		compress(cip, cop);
	}
	
	if(0 != vm.count("dip") || 0 != vm.count("dop")){
		fs::path dip(decompress_in_path);
		fs::path dop(decompress_out_path);
		decompress(dip, dop);
	}
#endif

	return 0;
}
