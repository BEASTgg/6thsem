#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h> //includes a number of definitions of structures needed for sockets.
#include<netinet/in.h> //contains constants and structures needed for internet domain addresses.
#include<sys/types.h> //contains definitions of a number of data types used in system calls. These types are used in the next two include files.
#define MAXLINE 20
#define SERV_PORT 5777
main(int argc,char *argv)
{
char sendline[MAXLINE],revline[MAXLINE];
int sockfd;
struct sockaddr_in servaddr;
	/*
	Generic socket address :--
	struct sockaddr {
		uint8_t 		sa_len;
		sa_family_t 	sa_family;
		char 		sa_data[14];
	};
	--> sa_family specifies the address type.
	--> sa_data specifies the address value.

	struct sockaddr_in {
		uint8_t 		sin_len;
		sa_family_t 	sin_family;
		in_port_t 		sin_port;
		struct in_addr 	sin_addr;
		char 		sin_zero[8];
	};
	A special kind of sockaddr structure.
	All values stored in a sockaddr_in must be in network byte order.
	– sin_port a TCP/IP port number.
	– sin_addr an IP address.
	*/
sockfd=socket(AF_INET,SOCK_STREAM,0);
	/*
	int socket(int family,int type,int proto);
	--> family specifies the protocol family (AF_INET for Internet, PF_INET for TCP/IP).
	--> type specifies the type of service (SOCK_STREAM, SOCK_DGRAM).
	--> protocol specifies the specific protocol (usually 0, which means the default).
	[ The socket() system call returns a socket descriptor (small integer) or -1 on error.
	socket() allocates resources needed for a communication endpoint - but it does not deal with endpoint addressing. ]
	*/
bzero(&servaddr,sizeof(servaddr));
	/*
	The function bzero() sets all values in a buffer to zero. 
	It takes two arguments, the first is a pointer to the buffer and the second is the size of the buffer. 
	Thus, this line initializes serv_addr to zeros.
	*/
servaddr.sin_family=AF_INET; //sin_family is set to AF_INET to indicate the use of IPv4.
servaddr.sin_port=ntohs(SERV_PORT); //sin_port is set to the port number defined by SERV_PORT. 
									//ntohs() function converts the port number to host byte order.
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)); //Establish queue for connection request. 
															 //It initiates the three-way handshake to establish the TCP connection.
printf("\n Enter the data to be send: ");
while(fgets(sendline,MAXLINE,stdin)!=NULL)
{
write(sockfd,sendline,strlen(sendline)); //write() function sends the data in sendline to the server.
										 //It then prints a message confirming that the line has been sent.
printf("\n Line send");
read(sockfd,revline,MAXLINE);  //This line reads data from the server into revline and prints it as the reverse of the sentence sent by the client.
printf("\n Reverse of the given sentence is : %s",revline);
printf("\n");
printf("\n Enter the data to be send: ");
}
exit(0);
}

