#include<stdio.h> //standard input/output operations (stdio.h), 
#include<unistd.h> //system calls (unistd.h, sys/socket.h, sys/types.h), 
#include<sys/socket.h> 
#include<string.h> //string manipulation (string.h), 
#include<sys/types.h>
#include<netinet/in.h> //network-related operations (netinet/in.h), 
#include<stdlib.h> //and memory allocation (stdlib.h).
#define SERV_PORT 5839 //These lines define two constants: SERV_PORT, which specifies the port number the client will connect to, 
#define MAXLINE 20 //and MAXLINE, which specifies the maximum length of a line.
int main(int argc,char **argv)
{
ssize_t n;	//n stores the number of bytes received from the server.
struct sockaddr_in servaddr; //servaddr is a structure to hold the server's socket address.
char sendline[MAXLINE],recvline[MAXLINE]; //sendline is an array to store the data to be sent to the server.
					//recvline is an array to store the received data from the server.
int sockfd; //sockfd is the socket file descriptor.
if(argc!=2)	//This block checks if the program is run with exactly 
{		//one command-line argument (the IP address of the server). 
printf("usage:<IPADDRESS>");	//If not, it prints a usage message and exits the program.
exit(0);
}
bzero(&servaddr,sizeof(servaddr));	//These lines initialize the server address structure servaddr:
					//bzero() clears the structure to ensure there are no leftover values.
servaddr.sin_family=AF_INET;  //sin_family is set to AF_INET to indicate the use of IPv4.
servaddr.sin_port=htons(SERV_PORT); //sin_port is set to the port number defined by SERV_PORT.
inet_pton(AF_INET,argv[1],&servaddr.sin_addr); //inet_pton() converts the IP address provided as a command-line argument to binary form 
					 //and stores it in servaddr.sin_addr.
sockfd=socket(AF_INET,SOCK_DGRAM,0); //This line creates a UDP socket using the socket() system call. 
				  //It specifies that the socket will use the IPv4 address family (AF_INET) 
				 //and datagram service (SOCK_DGRAM), corresponding to UDP protocol.
printf("enter the data to be send: ");
while(fgets(sendline,MAXLINE,stdin)!=NULL) //This loop reads data from the standard input (stdin) using fgets() function 
					 //until the end-of-file (EOF) or an error occurs.
{
sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr*)&servaddr,sizeof(servaddr)); 
//sendto() sends the data in sendline to the server specified by servaddr.
printf("Line sent. "); //It then prints a message confirming that the line has been sent.
n=recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL); //recvfrom() receives data from the server into recvline.
recvline[n]='\0';
//fputs(recvline,stdout);
printf("\nReverse of the sentense is %s",recvline); 
//It prints the received data, which is assumed to be the reverse of the sentence sent by the client.
printf("\n");
printf("Enter the data to be send: "); //Finally, it prompts the user to enter more data to be sent to the server.
}
exit(0);
}

