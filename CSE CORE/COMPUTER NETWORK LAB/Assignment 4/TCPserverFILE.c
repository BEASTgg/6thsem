#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 5576
main(int argc,char **argv)
{
int i,j;
ssize_t n;
FILE *fp;
char s[80],f[80];
struct sockaddr_in servaddr,cliaddr;
int listenfd,connfd,clilen;
listenfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERV_PORT);
bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
listen(listenfd,1);
clilen=sizeof(cliaddr);
connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
printf("\nClient connected. ");
read(connfd,f,80);
fp=fopen(f,"r");
printf("\nName of the file: %s",f);
while(fgets(s,80,fp)!=NULL)
{
printf("\nContent of the file: %s",s);
write(connfd,s,sizeof(s));
}
}

