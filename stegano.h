#ifndef STEGANO_FEIDER
#define STEGANO_FEIDER

#include "easybmp/EasyBMP.h"

bool encrypt(BMP &bmp, const char * src);
char * decrypt(BMP &bmp);


#endif
