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
int i,j; //i and j are loop counters.
ssize_t n; //n stores the number of bytes received from the client.
char line[MAXLINE],revline[MAXLINE]; //line is an array to store the received data from the client.
									//revline is an array to store the reversed data before sending it back to the client.
int listenfd,connfd,clilen; //listenfd is the socket file descriptor for the listening socket.
							//connfd is the socket file descriptor for the connected socket.
							//clilen stores the size of the client address structure.
struct sockaddr_in servaddr,cliaddr; //servaddr and cliaddr are structures to hold the server and client socket addresses, respectively.
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
listenfd=socket(AF_INET,SOCK_STREAM,0); //This line creates a TCP socket using the socket() system call. 
										//It specifies that the socket will use the IPv4 address family (AF_INET) and 
										//stream service (SOCK_STREAM), corresponding to TCP protocol.
	/*
	int socket(int family,int type,int proto);
	--> family specifies the protocol family (AF_INET for Internet, PF_INET for TCP/IP).
	--> type specifies the type of service (SOCK_STREAM, SOCK_DGRAM).
	--> protocol specifies the specific protocol (IPPROTO_TCP, IPPROTO_UDP, usually 0, which means the default).
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
servaddr.sin_port=htons(SERV_PORT); //sin_port is set to the port number defined by SERV_PORT. 
	/*sin_addr.s_addr is set to htons(SERV_PORT), which means the server will accept connections from any IP address assigned to the host.
	instead of simply copying the port number to this field, it is necessary to convert this to network byte order using the function htons() 
	which converts a port number in host byte order to a port number in network byte order.
	*/
bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)); //This line binds the socket to the server address specified by servaddr 
															//using the bind() system call. 
															//It associates the socket with a specific address and port number.
	/*
	The bind() system call is used to assign an address to an existing socket.
	int bind( int sockfd, const struct sockaddr *myaddr, int addrlen);
	--> sockid: integer, socket descriptor; addrport: struct sockaddr, the (IP) address and port of the machine; 
	--> for TCP/IP server, internet address is usually set to INADDR_ANY, i.e., chooses any incoming interface
	-->size: the size (in bytes) of the addrport structure; status: upon failure -1 is returned
	-->bind returns 0 if successful or -1 on error.
	--> calling bind() assigns the address specified by the sockaddr structure to the socket descriptor.
	--> You can give bind() a sockaddr_in structure:
	--> bind( mysock, (struct sockaddr*) &myaddr, sizeof(myaddr) );
	*/
listen(listenfd,1); //Accepts a connection request
					//This line makes the server listen for incoming connections on the socket listenfd. 
					//The second argument (1) specifies the maximum number of pending connections in the listen queue.
for( ; ; )
{
clilen=sizeof(cliaddr); //stores the size of the address of the client. This is needed for the accept system call.
connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen); //Initiates a connection to a remote host
printf("Connect to client.\n");

/*This loop runs indefinitely and accepts incoming connection requests using the accept() system call. 
It initializes a new socket descriptor connfd for each accepted connection. 
The server then communicates with the client using this new socket descriptor.*/

while(1)
{
if((n=read(connfd,line,MAXLINE))==0)
/* This inner loop reads data from the client into the line buffer using the read() system call. 
If read() returns 0, it means the client has closed the connection, so the server breaks out of the loop.*/
break;
printf("Data Received.\n");
printf("Data: %s",line);
line[n-1]='\0';
j=0;
for(i=n-2;i>=0;i--)
revline[j++]=line[i];
revline[j]='\0';
write(connfd,revline,n); //This line writes the reversed data (revline) back to the client using the write() system call.
}
}
}

