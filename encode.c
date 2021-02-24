#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <jansson.h>

#include "encode.c"

//we have a list of 4-bit binary numbers and we want to encode it using the json library

int main(int argc, char * argv[]){
		
	json_t *json;
    json_error_t error;
    char *pos;
	size_t size;
    json = json_load_file("textlib.json", 0, &error);
	if(json_is_array(json)){
		size = json_array_size(json);
		char words[size][20];
		next* pointersToNext[size];
		for(int i=0;i < size;i++){
			json_t *jsontmp = json_array_get(json,i);//in the jsontmp we have the i_th json cell that constaints
			//the word and the array nextwords
			
			json_t *word = json_object_get(jsontmp,"mainWord");
			json_t *nextwords = json_object_get(jsontmp,"nextWords");
			words[i] = json_string_value(word);
			size_t index;
			json_t *value;

			json_array_foreach(nextwords, index, value) {//values are the next words that we have to convert
			//to string and put them back into the next structure "pointersToNext"
			
				char *str = json_string_value(value);
				(pointersToNext[i]->nextWords)[index] = str;
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
	const int number = 1000;
	int binaryarray[number];
	char* str1 = "";
	char* str2 = "";
	for(int i = 0;i < number;i++){//i_th 4-bit number to encode
		int a = binvalue(binaryarray[i]);
		if(strcmp(str1, "")){
			fprintf(fptr, "%s", words[0]);
		}else{
			int j = 0;
			while(j<size && !strcmp(str1,words[j])){//str1 is the last word we have printed in the text file
				j++;
			}
			if(j == size){//if the last word was not in our library => simply print the words[binvalue[binaryarray[i]]]
				fprintf(fptr, "%s",words[binvalue[binaryarray[i]]]);
			}else{
				fprintf(fptr, "%s", (pointersToNext[i]->nextWords)[binvalue(binaryarray[i])]);//we print the correspong pointersToNext
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
