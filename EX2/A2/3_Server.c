/* Server Program */

#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<time.h>
#include<assert.h>
#include<string.h>
#define MAX 255
#define PORT 8081
#define SA struct sockaddr

int main()
{
	int sockfd,connfd,len;
	struct sockaddr_in serveraddr,cli;
	char buff[MAX];
	char counter[5];
	int n;
	char str[MAX];
	time_t tick;
	//socket create and verifiction
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("Socket creation failed");
		exit(0);
	}
	else
		printf("Socket id : %d \n",sockfd);
	
	bzero(&serveraddr,sizeof(serveraddr));
	
	//assign IP/PORT
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(PORT);
	
	//bind the client socket to server socket
	if(bind(sockfd,(SA*)&serveraddr,sizeof(serveraddr))!=0)
	{
		printf("Socket bind failed ...\n");
		exit(0);
	}
	else
		printf(" Binded \n ");
	
	if((listen(sockfd,5))!=0)
	{
		printf("Listen failed \n");
		exit(0);
	}
	else
		printf("Server listening \n");
	len = sizeof(cli);
	
	connfd = accept(sockfd,(SA*)&cli,&len);
	if(connfd<0)
	{
		printf("Server accept failed ... \n");
		exit(0);
	}
	else 
		printf("Server accepted the client\n");
	bzero(buff,sizeof(buff));
	
	for(int i=0;i<5;i++)
		counter[i]=0;
	
	printf(" Client says ... \n");
	do
	{
		read(connfd,buff,sizeof(buff));
		
		if(strcmp(buff,"exit")==0)
			break;
		
			printf("Client    : %s",buff);

			printf("\nYou       : ");			
			n=0;
			while((buff[n++]=getchar())!='\n');
			buff[--n]='\0';
			write(connfd,buff,sizeof(buff));
		if(strcmp(buff,"exit")==0)
			break;
		
	}while(1);
		
	printf("\nconvo ended ");

	close(sockfd);
	return 0;
}