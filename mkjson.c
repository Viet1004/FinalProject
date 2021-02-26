#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <jansson.h>

#include "mkjson.h"
#include "jansson.h"

#define LEN_TEXT 2000

int main(int argc, char * argv[]){

//first we need to read from a text in a txt file
//and analyse it word by word

//we nedd to make a library, from each word and its next one
//this library is an array of words along with an array of pointers. each pointer pointing to an array of words
//the size of this array is 64. in the case that is not complete we will add generated words to the array.
//to make things simple, we define a struct for this purpose.
	char words[2000][40];
	printf("can we see here");

	struct inf pointersToInf[2000];//an array of pointers to inf structs
	printf("can we see here");

	//pointersToInf = (inf*)malloc(2000* sizeof(inf));
	/*for(int i = 0; i < 2000; i++){
		pointersToInf[i] = (inf*)malloc(sizeof(inf)); 
	}*/
	for(int i = 0; i < 2000; i++){
		pointersToInf[i].size = 0;
	}
	//memcpy((pointersToInf[0]->nextWords),"highvideo",strlen("highvideo"));
	
				printf("can we see here");

	FILE * fp = fopen("text2.txt", "r"); 
	if (fp == NULL) return 1; 
	char c; 
	int count = 0,countext = 0;
	char str1[40],str2[40];
	strcpy(str1,"hiiiii");
		printf("can we see here");

	int pointersize = 0;
	while((c = fgetc(fp)) != EOF  && countext < 2000) //getting characters
	{ 
		if(c == ' ' || c == '\n') //this is the end of the word
		{ 
			printf("\n");
			++count;countext++;
			//now we have the two consecutive words in str1 and str2, we put them in the library.
			//we must first find str1 in the words array.
			int i = 0;//to search if we have already seen the word
			printf("%s and %s \n",str1,str2);
			while(i < 2000 && i<pointersize && strcmp(str1,words[i])!=0){
				i++;
			}		
			printf("%d and %d and %d\n",i,pointersize,pointersToInf[i].size);
			printf("we come here and %d",pointersize);
			if(i!=2000 && i!=pointersize){
								printf("we come here");

				//first we check if we have enough space in the library of str1.
				if(pointersToInf[i].size < 64){
					int size = pointersToInf[i].size;
					pointersToInf[i].size  = size + 1;
					//pointersToInf[i]-> nextWords)[size] = str2;
					memcpy((pointersToInf[i].nextWords)[size],str2,strlen(str2));
				}
			}else{//pointersize is the number of elements we have analyzed, without repetation
				printf("we come here");
				memcpy(words[pointersize],str1,strlen(str1));
				int size = pointersToInf[i].size;
				pointersToInf[i].size  = size + 1;
				memcpy((pointersToInf[pointersize].nextWords)[size],str2,strlen(str2));
				pointersize++;
			}
							printf("we come here");

			strcpy(str1,str2);// two consecutive words being like : str1 str2
			memset(str2,0,sizeof(str2));
			count = 0;
		} 
		else 
		{ 
			printf("%c",c);
			strncat(str2, &c, 1);
			count++;//to have the length of the word
		} 
			printf("can we see here??");
	} 
	fclose(fp); 
	printf("can we see here??");
	
	//now we have the library but maybe not all the words have a complete array : nextWords.
	//to complete these arrays we use the function "complete" to fix this.
	complete(words,pointersToInf,countext);
	
	//and now we make a json file to save all this information. this json file consist of an array.
	//each cell of this array has two "keys" : "mainWord" and "nextArray". first one is a string and the
	//second one is an array of strings.
	createJson(words,pointersToInf,countext);
 

	return 0; 
	

}


void complete(char words[2000][40],inf* pointersToInf,int countext){
	//an array of random prefixes:
	char prefixes[63][40] = {"pasta-","macabre-","creepy-","contra-","ultra-","big-","small-"
	,"little-","tiny-","bloody-","blushing-","breakable-","bored-","careful-","adorable-","adventurous-",
	"aggressive-","agreeable-","alert-","alive-","amused-","angry-","annoyed-","annoying-","anxious-",
	"arrogant-","ashamed-","evil-","excited-","expensive-","exuberant-","fair-","faithful-","famous-",
	"fancy-","sore-","sparkling-","splendid-","spotless-","stormy-","monster-","strange-","stupid-","successful-",
	"super-","uptight-","vast-","victorious-","vivacious-","wandering-","weary-","wicked-","wide-eyed-","wild-"
	,"witty-","worried-","worrisome-","eager-","easy-","elated-","elegant-","embarrassed-","enchanting-"};
	
	

	for(int i=0;i < countext;i++){
		int size = pointersToInf[i].size;
		int j = size;
		while(j < 64){
			//we copy the (j-size)-th prefix at the end of the j-th word in the array nextWords
			//memcpy((pointersToInf[i]->nextWords)[j]+strlen((pointersToInf[i]->nextWords)[j]),prefixes[j-size],strlen(prefixes[j-size]));
			strcat((pointersToInf[i].nextWords)[j], prefixes[j-size]);
			j++;
		}
	}
	
	
	printf("can we see here");

}

void createJson(char words[2000][40],inf* pointersToInf,int countext){
	
	//you can find the function used in this code in the example: 
	//https://github.com/akheron/jansson/blob/master/test/suites/api/test_dump.c
	
	
	json_t *jsonarray;//json object
	jsonarray = json_array();
	for(int i=0;i < countext;i++){
		json_t *json;
		json = json_object();//this should hold the mainWord and nextWords
		json_object_set_new(json, "mainWord", json_string(words[i]));
		json_t *jsonarraytmp;
		jsonarraytmp = json_array();//Array of the next words
		for(int j=0;j < 64;j++){
			json_array_append_new(jsonarraytmp, json_string((pointersToInf[i].nextWords)[j]));
		}
		json_object_set_new(json, "nextWords", jsonarraytmp);
		
		json_array_append_new(jsonarray,json);
	}
	
	
	//now we have to put the jsonarray in a json file
	
    int result = json_dump_file(NULL, "", 0);
    if (result != -1)
        printf("json_dump_file succeeded with invalid args");

  
    result = json_dump_file(jsonarray, "json_dump_file.json",0);
    if (result != 0)
        printf("json_dump_file failed");
	else
		printf("json_dump_file created");

    json_decref(jsonarray);
    //remove("json_dump_file.json");
}
