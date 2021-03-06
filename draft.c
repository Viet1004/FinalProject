
/*
int readfromjson(size_t size,char words[size][40],next pointersToNext[size]){
    json_t *json;
    json_error_t error;
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

    return size;
}
*/


/*
void encodeIP(size_t sizeOfLibrary, size_t sizeOfEncode, int *p, FILE *fptr, char words[sizeOfLibrary][40],next pointersToNext[sizeOfLibrary]){
			memcpy(str1,words[a],strlen(words[a]));
		}else{
			int j = 0;
			while(j<sizeOfLibrary && strcmp(str1,words[j])!=0){//str1 is the last word we have printed in the text file
				j++;
			}
			
			//printf("this is j : %d \n", j);
			if(j == sizeOfLibrary){//if the last word was not in our library => simply print the words[binvalue[binaryarray[i]]]
				fprintf(fptr, "%s",words[a]);
				fprintf(fptr, "%s", " ");
				free(str1);
				str1 = (char*)malloc(40*sizeof(char));
				memcpy(str1,words[a],strlen(words[a]));
				//printf("the string %s in %d \n", words[a],a);
				//str1 = words[a];
			}else{
				fprintf(fptr, "%s", (pointersToNext[j].nextWords)[a]);//we print the correspong pointersToNext
				fprintf(fptr, "%s", " ");
				//printf("%d with the string %s \n", a , (pointersToNext[j].nextWords)[a]);
				//printf("333333 \n");
				free(str1);
				str1 = (char*)malloc(40*sizeof(char));
				memcpy(str1,(pointersToNext[j].nextWords)[a],strlen((pointersToNext[j].nextWords)[a]));
				//str1 = (pointersToNext[j].nextWords)[a];
			}
		}
	}
	 
    fclose(fptr);
}
*/
