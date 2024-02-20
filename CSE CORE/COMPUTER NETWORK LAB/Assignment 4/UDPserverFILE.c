#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h> //contains definitions of a number of data types used in system calls. These types are used in the next two include files.
#include<sys/socket.h> //includes a number of definitions of structures needed for sockets.
#include<netinet/in.h> //contains constants and structures needed for internet domain addresses.
#define SERV_PORT 6349
main(int argc,char **argv)
{
char filename[80],recvline[80];
FILE *fp;
struct sockaddr_in servaddr,cliaddr;
int clilen,sockfd;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERV_PORT);
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
clilen=sizeof(cliaddr);
recvfrom(sockfd,filename,80,0,(struct sockaddr*)&cliaddr,&clilen);
//The recvfrom socket function receives data on a socket with descriptor s and stores it in a buffer.
printf("\nData in the file is: \n ");
fp=fopen(filename,"r");
while(fgets(recvline,80,fp)!=NULL)
{
printf("\n %s\n ",recvline);
}
fclose(fp);
}

