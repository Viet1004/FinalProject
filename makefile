libs = -ljansson


all: IPoverTwitter

IPoverTwitter: IPoverTwitter.o encode.o
	cc -g -o IPoverTwitter IPoverTwitter.o encode.o -ljansson
IPoverTwitter.o: IPoverTwitter.c 
	cc -c -Wall -g IPoverTwitter.c 
encode.o: encode.c
	cc -c -Wall -g encode.c 
clean: 
	rm -f IPoverTwitter IPoverTwitter.o encode.o
