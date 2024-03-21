#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

// SOCK 구조체를 위한 매크로
#define GetSockPtr(sock) \
	(sock.mySock)
// socket의 file descriptor를 반환
#define GetSockFd(sock) \
	(GetSockPtr(sock)->sockfd)
// socket의 IPv4 주소를 반환
#define GetSockAddr(sock) \
	(GetSockPtr(sock)->addr)
// socket의 주소 길이를 반환
#define GetAddrLen(sock) \
	(GetSockPtr(sock)->addr_len)
// SOCK 구조체 생성 오류값 반환
#define GetError(sock) \
	(sock.error_no)

//SOCK의 주소 설정을 위한  매크로
#define SetFamily(sock,family) \
	GetSockAddr(sock).sin_family=family 
#define SetAddr(sock,addr) \
	GetSockAddr(sock).sin_addr.s_addr=addr
#define SetPort(sock,port) \
	GetSockAddr(sock).sin_port=port

typedef struct
{
	struct sockaddr_in addr;
	socklen_t addr_len;
	int sockfd;
	
}__SOCKV4;

typedef struct 
{
	__SOCKV4* mySock;
	char error_no;
}SOCK;

//SOCK's public functions
//non_bind:1 create a non_bind socket
SOCK createTCPSocket(const uint32_t ipv4address,const int port,int non_bind);
int listenSocket(SOCK sock, int backlog);
int acceptSocket(SOCK serv_sock,SOCK clnt_sock);
ssize_t readSocket(SOCK sock,void* const buf,size_t byte);
ssize_t writeSocket(SOCK sock,const void* buf,size_t byte);
int closeSocket(SOCK sock);
int destroySocket(SOCK sock);
//int shutdownSocket(SOCK sock,int how);


void error_handler(const char* msg);

int main(int argc, char* argv[])
{
	char buf[BUF_SIZE];
	int read_len=0;
	SOCK serv_sock, clnt_sock;

	if(argc!=2)
	{
		printf("Usage: %s <port>\n",argv[0]);
		exit(1);
	}

	serv_sock=createTCPSocket(INADDR_ANY,htons(atoi(argv[1])),0);
	if(GetError(serv_sock)!=0)
		error_handler("createTCPSocket() errro!");

	clnt_sock=createTCPSocket(NULL,NULL,1);
	if(GetError(clnt_sock)!=0)
		error_handler("createTCPSocket() errro!");

	if(listenSocket(serv_sock,5)==-1)
		error_handler("listenSocket() errro!");

	printf("wait for client\n");

	if(acceptSocket(serv_sock,clnt_sock)==-1)
		error_handler("acceptSocket() error!");

	printf("client conntted!\n");

	//echo 서버
	while((read_len=readSocket(clnt_sock,buf,BUF_SIZE-1))!=0)
	{
		buf[read_len]=0;
		writeSocket(clnt_sock,buf,read_len);

		printf("%s",buf);
	}

	closeSocket(clnt_sock);
	closeSocket(serv_sock);
}

void error_handler(const char* msg)
{
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}

SOCK createTCPSocket(const uint32_t ipv4address,const int port,int non_bind)
{
	SOCK newSock;
	GetError(newSock)=0;

	// alloc space for struct sockaddr_in, socklen_t, file descriptor
	newSock.mySock=(__SOCKV4*)malloc(sizeof(__SOCKV4));
	if(newSock.mySock==NULL)
	{
		GetError(newSock)=-1;
		return newSock;
	}

	// if newSock is for accept()'s return  
	if(ipv4address==NULL&&port==NULL)
		return newSock;
	
	// set the struct sockaddr_in
	GetAddrLen(newSock)= sizeof(struct sockaddr_in);

	memset(&GetSockAddr(newSock),0,GetAddrLen(newSock));
	SetFamily(newSock,AF_INET);	
	SetAddr(newSock,ipv4address);
	SetPort(newSock,port);


	// call socket() and bind()
	GetSockFd(newSock)= socket(PF_INET,SOCK_STREAM,0);

	if(non_bind==1)
		return newSock;

	if( bind(GetSockFd(newSock), (struct sockaddr*)&GetSockAddr(newSock), GetAddrLen(newSock))==-1)
	{
		GetError(newSock)=-2;
		return newSock;
	}
		
	return newSock;
}

int  acceptSocket(SOCK serv_sock,SOCK clnt_sock)
{
	GetSockFd(clnt_sock)= accept(GetSockFd(serv_sock),(struct sockaddr*)&GetSockAddr(clnt_sock), &GetAddrLen(clnt_sock));

	return GetSockFd(clnt_sock);
}

int  listenSocket(SOCK sock, int backlog)
{
	return listen(GetSockFd(sock),backlog);

}

ssize_t readSocket(SOCK sock,void* const buf,size_t byte)
{
	return read( GetSockFd(sock), buf, byte); 
}

ssize_t writeSocket(SOCK sock,const void* buf,size_t byte)
{
	return write( GetSockFd(sock), buf, byte);
}

int closeSocket(SOCK sock)
{
	close( GetSockFd(sock));
	destroySocket(sock);	
}

int destroySocket(SOCK sock)
{
	free( GetSockPtr(sock) );
}
