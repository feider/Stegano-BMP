#include "stegano.h"
#include <iostream>


int main(int argc, char* argv[])
{
	BMP bmp;
	std::string in_file, info;
	switch(argc)
	{
		case 1:
			std::cout<<"Input file: ";
			std::getline(std::cin, in_file);
			break;

		case 2:
			in_file = argv[1];
			break;

		default:
			std::cout<<"Usage:\n\tdecrypt <bmpfile>\nOr just:\n\tdecrypt\n";
			return -1;
	}
	return 0;
}
