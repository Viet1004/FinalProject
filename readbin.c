#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LENBUF 2048
int main(){
    FILE *readFile;
    unsigned char buff[LENBUF];
    readFile = fopen("test.bin","rb");
    fread(buff,sizeof(buff), 1, readFile);
    for (int i = 0; i < LENBUF; i++){
        printf("%x ", buff[i]);
    }
}