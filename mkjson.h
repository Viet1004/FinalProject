#ifndef URL_H
#define URL_H

typedef struct inf
{
	//the array of size 64 of words
	char nextWords[64][40];
	//we must also keep the current size of this array
	int size;//must be initialized to 0
} inf ;
void complete(char words[2000][40],inf* pointersToInf,int countext);
void createJson(char words[2000][40],inf* pointersToInf,int countext);

#endif
