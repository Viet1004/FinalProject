#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <jansson.h>
#include "encode.h"
#define LENBUF 1024

//int readfromjson(size_t size,char words[size][40],next pointersToNext[size]);
//void encodeIP(size_t sizeOfLibrary, size_t sizeOfEncode, int *p, FILE *fptr, char words[sizeOfLibrary][40],next pointersToNext[sizeOfLibrary]);

static void run(char *cmd) {
  printf("Execute `%s`\n", cmd);
  if (system(cmd)) {
    perror(cmd);
    exit(1);
  }
}


int tun_alloc(char *dev, int flags) {

  struct ifreq ifr;
  int fd, err;
  char *clonedev = "/dev/net/tun";

  /* Arguments taken by the function:
   *
   * char *dev: the name of an interface (or '\0'). MUST have enough
   *   space to hold the interface name if '\0' is passed
   * int flags: interface flags (eg, IFF_TUN etc.)
   */

   /* open the clone device */
   if( (fd = open(clonedev, O_RDWR)) < 0 ) {
     return fd;
   }

   /* preparation of the struct ifr, of type "struct ifreq" */
   memset(&ifr, 0, sizeof(ifr));

   ifr.ifr_flags = flags;   /* IFF_TUN or IFF_TAP, plus maybe IFF_NO_PI */

   if (*dev) {
     /* if a device name was specified, put it in the structure; otherwise,
      * the kernel will try to allocate the "next" device of the
      * specified type */
     strncpy(ifr.ifr_name, dev, IFNAMSIZ);
   }

   /* try to create the device */
   if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
     close(fd);
     return err;
   }

  /* if the operation was successful, write back the name of the
   * interface to the variable "dev", so the caller can know
   * it. Note that the caller MUST reserve space in *dev (see calling
   * code below) */
  strcpy(dev, ifr.ifr_name);

  /* this is the special file descriptor that the caller will use to talk
   * with the virtual interface */
  return fd;
}

int tun_allocAlt() {
  struct ifreq ifr;
  int fd, e;

  if ((fd = open("/dev/net/tun", O_RDWR)) < 0) {
    perror("Cannot open /dev/net/tun");
    return fd;
  }
  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  strncpy(ifr.ifr_name, "tun1", IFNAMSIZ);

  if ((e = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
    perror("ioctl[TUNSETIFF]");
    close(fd);
    return e;
  }

  return fd;
}


int main(){
/*
  struct timeval tv;
  memset(&tv,0,sizeof(struct timeval));
  tv.tv_sec = 1;
  tv.tv_usec = 10;
*/

//Add new code 
//	size_t size = 2000; 
//  char words[size][40];
//	next pointersToNext[size];
//  size = readfromjson(size, words, pointersToNext);
//  FILE *fptr;
//  fptr = fopen("message.txt", "w");

// end of new code

  uint8_t tun_buf[LENBUF];
//  unsigned char buff[LENBUF];
  bzero(tun_buf,LENBUF);
  int tun_fd;
  if ((tun_fd = tun_allocAlt())<0){
    perror("Error at tun allocation");
    exit(EXIT_FAILURE);
  }
  FILE *wptr; 
  wptr = fopen("textToTwitter.txt","w");
//  write_ptr = fopen("test.bin","wb");
/*  
  run("sudo openvpn --mktun --dev tun1");
  run("sudo ip link set tun1 up");
  run("sudo ip addr add 10.0.0.1/24 dev tun1");
*/
  while(1){
//    FILE *write_ptr;
//    write_ptr = fopen("test.bin","wb");

    fd_set readset;
    FD_ZERO(&readset);
    FD_SET(tun_fd, &readset);

    if(select(tun_fd+1,&readset, NULL, NULL, NULL) == -1){
      perror("select error");
      exit(EXIT_FAILURE);
    }

    int r;
    if (FD_ISSET(tun_fd, &readset)) {
      r = read(tun_fd, tun_buf, LENBUF);
      
      if (r < 0) {
        // TODO: ignore some errno
        perror("read from tun_fd error");
        break;
      }
      printf("There are %d bytes in the packets\n", r);  
      uint32_t *temp = malloc(r*sizeof(uint32_t));      
      for(int i = 0; i<r; i++){
/*
        (*(temp+2*i)) = (int)(*(tun_buf+i))/16; 
        (*(temp+2*i+1)) = (int)(*(tun_buf+i))%16;
*/      
        *(temp+i) = (uint32_t)*(tun_buf+i);
      }     
/* 
      for(int i = 0; i<r;i++){
        if( *(temp+i) < 8){
                fputc(*(temp+i),wptr);
        }
        else{fputc(*(temp+i),wptr);}
      }
*/  
      int iter = r*2/20;
      int res = r*2%20;
/*      for (int i  = 0; i < iter; i++){
        encodeIP(size, 20, temp+i*20, fptr, words, pointersToNext);
        run("python3 postTweet.py");
      }
      encodeIP(size, res, temp+iter*20, fptr, words, pointersToNext);
      run("python3 postTweet.py");
*/
      
      for(int i = 0; i<r; i++){
        /*
        printf("%d ", *(temp+2*i));
        printf("%d ", *(temp+2*i+1));
        */
        printf("%d ", *(temp+i));
        if (i == r-1){
          printf("\n");
        } 
      }


      
//      fwrite(temp,4,r,wptr);
      fseek(wptr, 0L, SEEK_END);  
      long int length = ftell(wptr); 
      printf("Length of file is: %ld", length); 
//      run("python3 postTweet.py");
      free(temp);
    }
    else{
      printf("If fails");
    }
//    free(temp);
    
  }
  fclose(wptr);
}

/*
Reference:  https://backreference.org/2010/03/26/tuntap-interface-tutorial/
            https://lxd.me/a-simple-vpn-tunnel-with-tun-device-demo-and-some-basic-concepts
*/


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