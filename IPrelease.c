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

int tun_allocAlt() {
  struct ifreq ifr;
  int fd, e;

  if ((fd = open("/dev/net/tun", O_RDWR)) < 0) {
    perror("Cannot open /dev/net/tun");
    return fd;
  }
  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  strncpy(ifr.ifr_name, "tun2", IFNAMSIZ);

  if ((e = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
    perror("ioctl[TUNSETIFF]");
    close(fd);
    return e;
  }

  return fd;
}

int main(){
    FILE *rptr;
    uint8_t buff[84];
    bzero(buff,84);
    fd_set writefd;
    int tun_fd;
    if ((tun_fd = tun_allocAlt())<0){
      perror("Error at tun allocation");
      exit(EXIT_FAILURE);
    }

    rptr = fopen("test.bin", "rb");
    
    if(rptr == NULL){
        perror("Opening file error");
    }
    int a = fread(buff, 1, sizeof(buff), rptr);
    printf("%d\n", a);

    FD_ZERO(&writefd);
    FD_SET(tun_fd,&writefd);
    if(select(tun_fd+1, NULL, &writefd, NULL, NULL) == -1){
      perror("select write");
    }

    if(FD_ISSET(tun_fd, &writefd)){
      int r = write(tun_fd, buff, sizeof(buff));
      if (r < 0){
        perror("write to file descriptor error");
      }
    }
//    fwrite(tun_buf,1,r,write_ptr);
//    fseek(rptr, 0L, SEEK_END);  
//    size_t length = ftell(rptr);
//    unsigned char *buff = malloc((size_t)length);
//    printf("Length: %ld\n", length);


    for(int i = 0; i<84; i++){
        printf("%u ", *(buff+i));  
    }
    
//    free(buff);
    fclose(rptr);
}
