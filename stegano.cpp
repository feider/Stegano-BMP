#include "stegano.h"
#include "string.h"
#include <iostream>
#include <bitset>

#define UNTOUCHED 0xFC
#define TOUCHED 0x01
#define DECRYPT 0x03
#define BORDER 0x04

void charToData(unsigned char data_char, char * return_char)
{
	std::bitset<8> bs(data_char);
	char data[4];
	for(int i=0; i<4; i++)
	{
		data[i] = bs[i*2]*2 + bs[i*2 + 1];
	}

	return;
}

unsigned char mark(unsigned char char_mark)
{
	return (char_mark&0xFE)+1;
}

unsigned char mark_end(unsigned char char_mark)
{
	return char_mark&0xFE;
}

unsigned char decryptChar(unsigned char char_crypted)
{
	char_crypted&=DECRYPT;
	return char_crypted;
}

unsigned char dataToChar(char * data)
{
	char return_char=0;
	for(int i = 0; i>=0; i--)
	{
		return_char += data[i]*(4-i);
	}
	return return_char;
}

unsigned char encryptChar(unsigned char data_char, char info)
{
	printf("%i", data_char);
	data_char &= UNTOUCHED;
	data_char += info*TOUCHED;
	printf(" %i\n", data_char);
	return data_char;
}



bool encrypt(BMP &bmp, const char * src)
{
	int free_chars = bmp.TellWidth() * bmp.TellHeight();
	free_chars/=2; // two pixels are needed for one char
	unsigned char length = strlen(src);
	if(free_chars<length)
	{
		printf("Image is too small. \nIt needs at least %i more pixels\n", (length-free_chars)*2);
		return false;
	}



	printf("used: %i/%i chars\n", length, free_chars);


	int x, y, pos;
	for(int i=0; src[i]!='\0'; i++)
	{
		char data[4];
		charToData(src[i], data);
		pos = i*2;
		x = pos%length;
		y= pos/length;

		bmp(x, y)->Red = encryptChar(bmp(x, y)->Red, data[0]);
		bmp(x, y)->Green =encryptChar(bmp(x, y)->Green, data[1]);
		bmp(x, y)->Blue =mark(bmp(x, y)->Blue);
		pos++;
		x = pos%length;
		y= pos/length;
		bmp(x, y)->Red =encryptChar(bmp(x, y)->Red, data[2]);
		bmp(x, y)->Green = encryptChar(bmp(x, y)->Green, data[3]);

		printf("%i\n", bmp(x, y)->Red);
	}
	pos--;
	x = pos%length;
	y= pos/length;
	bmp(x,y)->Blue=(char)mark_end(bmp(x,y)->Blue);


	return true;
}

