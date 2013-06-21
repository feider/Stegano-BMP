all: easybmp.o encrypt.o decrypt.o stegano.o
	g++ encrypt.o stegano.o easybmp.o -o encrypt
	g++ decrypt.o stegano.o easybmp.o -o decrypt

encrypt.o: encrypt.cpp
	g++ -c encrypt.cpp -std=c++0x -o encrypt.o

decrypt.o: decrypt.cpp
	g++ -c decrypt.cpp -std=c++0x -o decrypt.o

stegano.o: stegano.cpp
	g++ -c stegano.cpp -std=c++0x -o stegano.o

easybmp.o: easybmp/EasyBMP.cpp
	g++ -c easybmp/EasyBMP.cpp -std=c++0x -o easybmp.o

install:
	cp -f encrypt /usr/local/bin/
	cp -f decrypt /usr/local/bin/

uninstall:
	rm /usr/local/bin/encrypt
	rm /usr/local/bin/decrypt

