libs = -ljansson

all: mkjson

mkjson: mkjson.o
	cc -g -o mkjson mkjson.o -ljansson
mkjson.o: mkjson.c
	cc -c -Wall -g mkjson.c -g
	
clean:
	rm mkjson mkjson.o
