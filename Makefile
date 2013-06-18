all: easybmp.o encrypt.o decrypt.o stegano.o
	g++ encrypt.o stegano.o easybmp.o -o encrypt
	g++ decrypt.o stegano.o easybmp.o -o decrypt

encrypt.o: encrypt.cpp
	g++ -c encrypt.cpp -o encrypt.o

decrypt.o: decrypt.cpp
	g++ -c decrypt.cpp -o decrypt.o

stegano.o: stegano.cpp
	g++ -c stegano.cpp -o stegano.o

easybmp.o: easybmp/EasyBMP.cpp
	g++ -c easybmp/EasyBMP.cpp -o easybmp.o

install:
	cp -f encrypt /usr/local/bin/
	cp -f decrypt /usr/local/bin/
