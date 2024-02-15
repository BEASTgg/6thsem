#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#define SERV_PORT 5839 //These lines define two constants: SERV_PORT, which specifies the port number the server will listen on,
#define MAXLINE 20 //and MAXLINE, which specifies the maximum length of a line.
main(int argc,char **argv)
{
int i,j;
ssize_t n;
char line[MAXLINE],recvline[MAXLINE];
struct sockaddr_in servaddr,cliaddr; //servaddr and cliaddr are structures to hold server and client socket addresses, respectively.
int sockfd,clilen; //sockfd is the socket file descriptor. clilen stores the size of the client address.
sockfd=socket(AF_INET,SOCK_DGRAM,0); /*This line creates a socket using the socket() system call. 
					It specifies that the socket will use the IPv4 address family (AF_INET) 
					and datagram service (SOCK_DGRAM), which corresponds to UDP protocol.*/
bzero(&servaddr,sizeof(servaddr)); /*This line initializes the server address structure servaddr with zeros using the bzero() function. 
				 This is done to ensure that there are no leftover values in the structure.*/
servaddr.sin_family=AF_INET; //sin_family is set to AF_INET to indicate the use of IPv4.
servaddr.sin_addr.s_addr=htonl(INADDR_ANY); //sin_addr.s_addr is set to htonl(INADDR_ANY), 
					  //which means the server will accept connections from any IP address assigned to the host.
servaddr.sin_port=htons(SERV_PORT); //sin_port is set to the port number defined by SERV_PORT.
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)); //This line binds the socket to the server address specified by servaddr. 
							//The bind() function associates the socket with a specific address and port number.
for( ; ; )
{
clilen=sizeof(cliaddr); //This begins an infinite loop where the server continuously listens for incoming UDP packets. 
			//It initializes the variable clilen with the size of the client address structure.
while(1)
{
if((n=recvfrom(sockfd,line,MAXLINE,0,(struct sockaddr*)&cliaddr,&clilen))==0) 
//This line receives data from the client using the recvfrom() function. 
//It reads at most MAXLINE bytes of data into the line buffer. 
//If recvfrom() returns 0, it means the client has closed the connection, so the server breaks out of the inner loop.
break;
printf("\nLine received successfully: %s",line);
line[n-1]='\0';  
//This line ensures that the received line is null-terminated by replacing the newline character (\n) with the null character (\0).
j=0;
for(i=n-2;i>=0;i--)
{
recvline[j++]=line[i];  //This loop reverses the received line (line) and stores it in the recvline buffer.
}
recvline[j]='\0';
sendto(sockfd,recvline,n,0,(struct sockaddr*)&cliaddr,clilen); 
//This line sends the reversed line (recvline) back to the client using the sendto() function.
}
}
}

