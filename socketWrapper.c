#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

#define GetAddrLen(sock) \
	((sock.mySock)->addr_len)
#define GetSockFd(sock) \
	((sock.mySock)->sockfd)
#define GetSockAddr(sock) \
	((sock.mySock)->addr)
#define GetError(sock) \
	(sock.error_no)

#define SetFamily(sock,family) \
	GetSockAddr(sock).sin_family=family 
#define SetAddr(sock,addr) \
	GetSockAddr(sock).sin_addr.s_addr=addr
#define SetPort(sock,portInt) \
	GetSockAddr(sock).sin_port=htons(portInt)


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
SOCK createTCPSocket(const uint32_t ipv4address,const int port);
int listenSocket(SOCK sock, int backlog);
int acceptSocket(SOCK serv_sock,SOCK clnt_sock);
//ssize_t readSocket(SOCK sock,void* buf,size_t byte);
//ssize_t writeSocket(SOCK sock,const void* buf,size_t byte);
//int closeSocket(SOCK sock);
//int shutdownSocket(SOCK sock,int how);


void error_handler(const char* msg);

int main(int argc, char* argv[])
{
	SOCK serv_sock, clnt_sock;

	serv_sock=createTCPSocket(INADDR_ANY,9196);
	if(GetError(serv_sock)!=0)
		error_handler("createTCPSocket() errro!");

	clnt_sock=createTCPSocket(NULL,NULL);
	if(GetError(clnt_sock)!=0)
		error_handler("createTCPSocket() errro!");

	if(listenSocket(serv_sock,5)==-1)
		error_handler("listenSocket() errro!");

	if(acceptSocket(serv_sock,clnt_sock)==-1)
		error_handler("acceptSocket() error!");

	printf("client conntted!\n");


/*
	int serv_sd, clnt_sd;
	char buf[BUF_SIZE];
	int read_cnt;
	pid_t pid;

	struct sockaddr_in serv_adr,clnt_adr;
	socklen_t clnt_adr_sz;

	if(argc!=3)
	{
		printf("Usage: %s <port> <file>\n",argv[0]);
		exit(1);
	}


	serv_sd=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sd==-1)
		error_handler("socket() error!");

	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_port=htons(atoi(argv[1]));
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(serv_sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
		error_handler("bind() error!");

	if(listen(serv_sd,5)==-1)
		error_handler("listen() error!");

	for(int connect_count=0; connect_count<5; connect_count++)
	{
		clnt_adr_sz=sizeof(clnt_adr);

		if((clnt_sd=accept(serv_sd,(struct sockaddr*)&clnt_adr,&clnt_adr_sz))==-1)
			error_handler("accept() error!");

		pid=fork();

		if(pid==0)
		{
			FILE *fp;

			fp=fopen(argv[2],"rb");
			if(fp==NULL)
				error_handler("fopen() error!");

			close(serv_sd);
			while(1)
			{
				read_cnt=fread(buf,1,BUF_SIZE,fp);
				if(read_cnt<BUF_SIZE)
				{
					if(write(clnt_sd,buf,read_cnt)==-1)
					{
						error_handler("write() error!");
					}
					break;
				}
				if(write(clnt_sd,buf,read_cnt)==-1)
					error_handler("write() error!");
			}
			shutdown(clnt_sd,SHUT_WR);
			read(clnt_sd,buf,BUF_SIZE);
			printf("Message from client: %s\n",buf);

			fclose(fp);
			close(clnt_sd);

			return 0;
		}
		else
		{
			close(clnt_sd);
		}
	}

	close(serv_sd);
	*/
}

void error_handler(const char* msg)
{
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}
/*
   for reference
typedef struct
{
	struct sockaddr_in addr;
	socklent_t addr_len;
	int sockfd;
	
}__SOCKV4;

typedef struct
{
	__SOCKV4* mySock;
	char error_no;
}SOCK;
*/

SOCK createTCPSocket(const uint32_t ipv4address,const int port)
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
//ssize_t readSocket(SOCK sock,void* buf,size_t byte);
