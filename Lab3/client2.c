/* STREAMCLIENT */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
#include<time.h>

#define PORT "3490"  //the port client will connecting to
#define MAXDATASIZE 100  //max number of bytes we can get at once
#define MAX_BUFFER 128 

//get sockaddr, ipv4 or ipv6
void *get_in_addr(struct sockaddr *sa)
 {
  if(sa->sa_family == AF_INET)
    {
     return &(((struct sockaddr_in*)sa)->sin_addr);
    }

   return &(((struct sockaddr_in6*)sa)->sin6_addr);
 }

 int main(int argc, char *argv[])
  {
   int sock_fd, numbytes, in;
   char buf[MAXDATASIZE];
   struct addrinfo hints, *servinfo, *p;
   int rv, first, second;
   char s[INET6_ADDRSTRLEN];
   char userinput[100];
   char serverreply[100];
   char clientinput;
   char timebuffer[MAX_BUFFER+1];
   char command[10];

   if(argc != 2)
     {
      fprintf(stderr,"usage: client hostname\n");
      exit(1);
     }

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;

   if((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0)
     {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
     }

   //loop through all results and connect to the first we can
   for(p = servinfo; p != NULL; p = p->ai_next)
      {
       if((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
         {
          perror("client: socket");
          continue;
         }

       if(connect(sock_fd, p->ai_addr, p->ai_addrlen) == -1)
         {
          close(sock_fd);
          perror("client: connect");
          continue;
         }

    break;
      }

   if(p == NULL)
     {
      fprintf(stderr, "client: failed to connect\n");
      return 2;
     }

   inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
   printf("client: connecting to %s\n", s);

   freeaddrinfo(servinfo);  //all done with this structure

   while((in = read(sock_fd, timebuffer, MAX_BUFFER)) > 0)
    {
     timebuffer[in] = 0;
     printf("\nThe current time is: %s", timebuffer);
     continue;
    }

//   continue;
   
   while(1)
      {
       bzero(userinput, 100);
       bzero(serverreply, 100);

       printf("Client request: %s", userinput);
       fgets(userinput, 100, stdin);
       write( sock_fd, userinput, strlen(userinput)+1);
       read(sock_fd, serverreply, 100);
       printf("Server reply: %s", serverreply);

       continue;
       }

//     }

   close(sock_fd);

   return 0;
}
