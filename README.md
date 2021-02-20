# FinalProject

the file should run with root permission

we use following structures : 


struct ifreq {
               char ifr_name[IFNAMSIZ]; /* Interface name */
               union {
                   struct sockaddr ifr_addr;
                   struct sockaddr ifr_dstaddr;
                   struct sockaddr ifr_broadaddr;
                   struct sockaddr ifr_netmask;
                   struct sockaddr ifr_hwaddr;
                   short           ifr_flags;
                   int             ifr_ifindex;
                   int             ifr_metric;
                   int             ifr_mtu;
                   struct ifmap    ifr_map;
                   char            ifr_slave[IFNAMSIZ];
                   char            ifr_newname[IFNAMSIZ];
                   char           *ifr_data;
               };
           };
the user specifies which device to affect by setting ifr_name to the name of the interface.  All other members of the structure may share memory.      

we try to open the indicated interface and put it in the file descriptor "fd".

size_t IFNAMSIZ:
This constant defines the maximum buffer size needed to hold an interface name, including its terminating zero byte.

in these two lines we create a tunneling device:(more precisely we try)
ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
ioctl(fd, TUNSETIFF, (void *) &ifr))



in the main function we use timeval which is a structure defined in  <sys/time.h> header with at least the following members:

time_t         tv_sec      seconds
suseconds_t    tv_usec     microseconds


fd_set datatype : The fd_set data type represents file descriptor sets for the select function.

"select" function used in main:
select() allows a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation. A file descriptor is considered ready if it is possible to perform the corresponding I/O operation (e.g.read) without blocking.

arguments of this function are : 
int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);
int nfds :????????????????????????? 
fd_set *readfds : 
fd_set *writefds :
fd_set *exceptfds : ?????????????

Four macros are provided to manipulate the sets. FD_ZERO() clears a set. FD_SET() and FD_CLR() respectively add and remove a given file descriptor from a set. FD_ISSET() tests to see if a file descriptor is part of the set; this is useful after select() returns.

an example of the above functions (https://linux.die.net/man/3/fd_set) is :
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    fd_set rfds;
    struct timeval tv;
    int retval;

   /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

   /* Wait up to five seconds. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;

   retval = select(1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */

   if (retval == -1)
        perror("select()");
    else if (retval)
        printf("Data is available now.\n");
        /* FD_ISSET(0, &rfds) will be true. */
    else
        printf("No data within five seconds.\n");

   exit(EXIT_SUCCESS);
}


           
      
