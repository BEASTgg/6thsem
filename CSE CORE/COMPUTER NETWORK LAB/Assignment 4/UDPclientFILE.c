#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h> //contains definitions of a number of data types used in system calls. These types are used in the next two include files.
#include<sys/socket.h> //includes a number of definitions of structures needed for sockets.
#include<netinet/in.h> //contains constants and structures needed for internet domain addresses.
#include<unistd.h>
#define SERV_PORT 6349
main(int argc,char **argv)
{
char filename[80];
int sockfd;
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERV_PORT);
inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
// The inet_pton() function converts an address in its standard text presentation form into its numeric binary form.
printf("Enter the file name: ");
scanf("%s",filename);
sendto(sockfd,filename,strlen(filename),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
}

