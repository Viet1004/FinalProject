all: IPoverTwitter

IPoverTwitter: IPoverTwitter.o
	cc -g -o IPoverTwitter IPoverTwitter.o
IPoverTwitter.o: IPoverTwitter.c
	cc -c -Wall -g IPoverTwitter.c