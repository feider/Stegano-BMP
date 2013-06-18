#include "stegano.h"
#include <iostream>


int main(int argc, char* argv[])
{
	BMP bmp;
	std::string in_file, info, out_file;
	switch(argc)
	{
		case 1:
			std::cout<<"Input file: ";
			std::getline (std::cin, in_file);
			std::cout<<"Info: ";
			std::getline (std::cin, info);

			std::cout<<"Output file: ";
			std::getline (std::cin, out_file);
			break;

		case 4:
			in_file = argv[1];
			info = argv[2];
			out_file = argv[3];
			break;

		default:
			std::cout<<"Usage:\n\tencrypt <bmpfile> <sentence> <output bmpfile>\nOr just:\n\tencrypt\n";
			return -1;
			break;
	}

	bmp.ReadFromFile(in_file.c_str());
	if(!encrypt(bmp, info.c_str()))
	{
		std::cout<<"Sentence is too big for the image!";
		return -1;
	}
	bmp.WriteToFile(out_file.c_str());
	return 0;

}
