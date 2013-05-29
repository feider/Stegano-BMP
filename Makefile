all: encrypt decrypt stegano
	g++ encrypt.o stegano.o -o encrypt
	g++ decrypt.o stegano.o -o decrypt

encrypt: encrypt.cpp
	g++ -c encrypt.cpp -o encrypt.o

decrypt: decrypt.cpp
	g++ -c decrypt.cpp -o decrypt.o

stegano: stegano.c
	gcc -c stegano.c -o stegano.o
