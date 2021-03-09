#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    FILE *rptr = fopen("test.bin", "rb");
    if (rptr == NULL){
        perror("open file error");
    }
    char b[12];
    bzero(b,12);
//    int *b = malloc(10*sizeof(int));
    int c = fread(b, 12, sizeof(char), rptr);
    printf("%d Bytes\n", c);
    for (int i = 0; i<12; i++){
        printf("%d\n", b[i]);
    }
    fclose(rptr);
}