#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <jansson.h>

#include "encode.h"

//we have a list of 4-bit binary numbers and we want to encode it using the json library

int main(int argc, char * argv[]){
		
	json_t *json;
    json_error_t error;
	size_t size = 2000;
	char words[size][40];
	next pointersToNext[size];
    json = json_load_file("json_dump_file.json", 0, &error);
	if(json_is_array(json)){
		size = json_array_size(json);
		for(int i=0;i < size;i++){
			json_t *jsontmp = json_array_get(json,i);//in the jsontmp we have the i_th json cell that constaints
			//the word and the array nextwords
			
			json_t *word = json_object_get(jsontmp,"mainWord");
			json_t *nextwords = json_object_get(jsontmp,"nextWords");
			memcpy(words[i],json_string_value(word),json_string_length(word));
			//words[i] = json_string_value(word);
			size_t index;
			json_t *value;

			json_array_foreach(nextwords, index, value) {//values are the next words that we have to convert
			//to string and put them back into the next structure "pointersToNext"
			
				const char *str = json_string_value(value);
				memcpy((pointersToNext[i].nextWords)[index],str,strlen(str));
				//(pointersToNext[i].nextWords)[index] = str;
			}
		}
	}
	
	//now we have all the information in the two arrays words and pointersToNext, we encode 4-bit binary numbers
	//suppose we have the number of these numbers
    FILE *fptr;
    fptr = fopen("message.txt", "w"); 
    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }
	int binaryarray[10] = {1001,1111,0111,0011,0001,1010,1110,1100,1000,0101};
	char* str1 = (char*)malloc(40*sizeof(char));
	memcpy(str1,"",strlen(""));
	for(int i = 0;i < 10;i++){//i_th 4-bit number to encode
		int a = binvalue(binaryarray[i]);
		if(strcmp(str1, "")==0){
			fprintf(fptr, "%s", words[0]);
			fprintf(fptr, "%s", " ");
			memcpy(str1,words[0],strlen(words[0]));
		}else{
			int j = 0;
			while(j<size && !strcmp(str1,words[j])){//str1 is the last word we have printed in the text file
				j++;
			}
			if(j == size){//if the last word was not in our library => simply print the words[binvalue[binaryarray[i]]]
				fprintf(fptr, "%s",words[a]);
				fprintf(fptr, "%s", " ");
				memcpy(str1,words[a],strlen(words[a]));
				//str1 = words[a];
			}else{
				fprintf(fptr, "%s", (pointersToNext[j].nextWords)[a]);//we print the correspong pointersToNext
				fprintf(fptr, "%s", " ");
				memcpy(str1,(pointersToNext[j].nextWords)[a],strlen((pointersToNext[j].nextWords)[a]));
				//str1 = (pointersToNext[j].nextWords)[a];
			}
		}
	}
	 
    fclose(fptr);
    return 0;
}


int binvalue (int binary){
		int i = 1;
		int sum = 0;
		while(binary > 0){
			sum += i*(binary%10);
			binary = binary/10;
			i = i*2;
		}
		return sum;
	}
