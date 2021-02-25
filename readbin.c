#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LENBUF 2048
char *convertToBinary(unsigned char d, char* bits);

int main(){
    FILE *readFile;
    unsigned char buff[LENBUF];
    readFile = fopen("test.bin","rb");
    if (readFile == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
    fseek(readFile, 0L, SEEK_END); 
  
    // calculating the size of the file 
    long int length = ftell(readFile); 
    printf("Length of file is: %ld", length); 
//    unsigned char *buff = malloc(length); 
    fread(buff,LENBUF, 1, readFile);
    for (int i = 0; i < LENBUF; i++){
//        char* temp = malloc(8);
//        unsigned char temp1 = buff[i];
//        printf("%d ", temp1);
//        printf("%s ", convertToBinary(temp1,temp));
//        printf("%s ", convertToBinary(buff[i], temp));
//        free(temp);
    int res = (int)buff[i] % 16;
    int quotien = (int)buff[i] / 16;
    printf("The number is :%d the quotien is: %d the residus is: %d\n", (int)buff[i], quotien, res);
    
    }
    // closing the file 
    fclose(readFile);
/*    unsigned char a = 1;
    char *temp = malloc(8*sizeof(char));
    convertToBinary(a, temp);
    for(int i =0; i < 8; i++){
        printf("klhjj %c\n",*(temp+i));
    }
*/
}
/*
char *convertToBinary(unsigned char d, char *bits){
//    d = (int)d;
    unsigned char mask = 1;
    for (int i = 0; i < 8; i++) {
    // Mask each bit in the byte and store it
        *(bits+i) = (char)((d & (mask << i)) != 0);
        printf("Binary: %c\n",*(bits+i));
    }
 // For debug purposes, lets print the received data
    for (int i = 0; i < 8; i++) {
        printf("Binary: %c\n",*(bits+i));
    }
  return bits;
}
*/