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
	for(int i=0; i<4; i++)
	{
		return_char[i] = bs[i*2]*2 + bs[i*2 + 1];
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
	data_char &= UNTOUCHED;
	data_char += info*TOUCHED;
	return data_char;
}



bool encrypt(BMP &bmp, const char * src)
{
	int free_chars = bmp.TellWidth() * bmp.TellHeight();
	free_chars/=2; // two pixels are needed for one char
	unsigned int length = bmp.TellWidth();
	if(free_chars<strlen(src))
	{
		printf("Image is too small. \nIt needs at least %i more pixels\n", (strlen(src)-free_chars)*2);
		return false;
	}



	printf("used: %i/%i chars\n", strlen(src), free_chars);


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

	}
	pos--;
	x = pos%length;
	y= pos/length;
	bmp(x,y)->Blue=(char)mark_end(bmp(x,y)->Blue);


	return true;
}




bool decrypt(BMP &bmp, std::string &info)
{
	int max_chars = (bmp.TellWidth() * bmp.TellHeight()) / 2;
	unsigned int length = bmp.TellWidth();
	for(int pos=0; pos<max_chars; pos+=2)
	{
		//std::cout<<pos<<std::endl;
		int x = pos%length;
		int y = pos/length;
		std::bitset<8> bs;
		bs[0]= (bmp(x, y)->Red & 2)/2;
		bs[1] = (bmp(x, y)->Red & 1);
		bs[2] = (bmp(x, y)->Green & 2)/2;
		bs[3] = (bmp(x, y)->Green & 1);
		//std::cout<<bmp(x, y)->Red<<std::endl;

		x = (pos+1)%length;
		y = (pos+1)/length;
		bs[4]= (bmp(x, y)->Red & 2)/2;
		bs[5] = (bmp(x, y)->Red & 1);
		bs[6] = (bmp(x, y)->Green & 2)/2;
		bs[7] = (bmp(x, y)->Green & 1);
		unsigned char data_char = (unsigned char) bs.to_ulong();
		info += data_char;

		x = pos%length;
		y = pos/length;
		if(0==(bmp(x, y)->Blue&1))
		{
			return true;
		}
	}
	return true;
}
