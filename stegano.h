#ifndef STEGANO_FEIDER
#define STEGANO_FEIDER

#include "easybmp/EasyBMP.h"

bool encrypt(BMP &bmp, const char * src);
bool decrypt(BMP &bmp, std::string &info);
char * decrypt(BMP &bmp);

#endif
