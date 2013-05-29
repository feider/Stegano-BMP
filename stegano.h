#ifndef STEGANO_FEIDER
#define STEGANO_FEIDER

#include <bmpfile.h>
#include <SDL/SDL.h>

bmpfile_t * bmpFromSurface(SDL_Surface * srfc);

void encrypt(bmpfile_t *bmp, char *source);
void decrypt(bmpfile_t *bmp, char *dest);


#endif
