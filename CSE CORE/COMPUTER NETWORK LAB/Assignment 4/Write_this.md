### 1. Write a TCP client server program to send hello message from client  to server. Server reverses the message and sends back to client. Client print the reversed message. 

Server Code -

```
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
	  sin_port a TCP/IP port number.
	  sin_addr an IP address.
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
```
Client Code -

```
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
	  sin_port a TCP/IP port number.
	  sin_addr an IP address.
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
```

Output -

```
 Enter the data to be send: this is a test

 Line send
 Reverse of the given sentence is : tset a si siht
```

### 2. Write a UDP client server message where the client sends a file to the server. The server reads the content of the file and prints it on the console. 

Server Code -

```
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
```
Client Code -

```
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
```

Output -

```
./a.out 8080
Enter the file name: a.txt

Data in the file is:

this is a test
```

### 3. Write a TCP client server message where the client sends a file to the server. The server reads the content of the file and prints it on the console. 

Server Code -

```
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
```
Client Code -

```
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
char filename[80],recvline[80];
struct sockaddr_in servaddr;
int sockfd;
sockfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERV_PORT);
inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
printf("Enter the file name: ");
scanf("%s",filename);
write(sockfd,filename,sizeof(filename));
printf("\n Data from server: \n");
while(read(sockfd,recvline,80)!=0)
{
fputs(recvline,stdout);
}
}
```

Output -

```
./a.out 8080
Enter the file name: a.txt

Data from server:
this is a test
```

### 4. Write a  TCP client server program where client will send an input file to the server. Inside that input file a sentence will be there. After receiving the file server reverse individual word of that sentence and write it into another file and reply back that new file to the client. Client will read the file and print the content of the file on the console.

Server Code -

```

```
Client Code -

```

```

Output -

```
🖕
```
