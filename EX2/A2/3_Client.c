/* Client Program */

#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#define MAX 255
#define PORT 8081
#define SA struct sockaddr

int main()
{
	int sockfd;
	struct sockaddr_in serveraddr,cli;
	char buff[MAX];
	char counter[5];
	int n;
	//socket create and verifiction
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("Socket creation failed \n");
		exit(0);
	}
	else
		printf("Socket id : %d \n",sockfd);
	
	bzero(&serveraddr,sizeof(serveraddr));
	
	//assign IP/PORT
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(PORT);
	
	//connect the client socket to server socket
	if(connect(sockfd, (SA*)&serveraddr,sizeof(serveraddr))!=0)
	{
		printf("Connection with the server failed \n");
		exit(0);
	}
	else
		printf("Client has been connected \n");
	
	bzero(buff,sizeof(buff));
	printf("Chat : \n");
	int f=1;
	do
	{	
		if(f)
		{
			n=0;
			printf("You        : ");
			while((buff[n++]=getchar())!='\n');
			buff[--n]='\0';
			write(sockfd,buff,sizeof(buff));
		}
		else
		{
			FILE *fp = popen("ls","r");
			char Line[50];
			char FileStuff[255]="\0";
			while(fgets(Line, 50, (FILE*)fp)!=0)
			{
				strcpy(FileStuff,strcat(FileStuff,Line));
			}
			write(sockfd,FileStuff,sizeof(FileStuff));
			printf("You        : written \n");
			f=1;
		}
		
		
		if(strcmp(buff,"exit")==0)
			break;
		
		read(sockfd,buff,sizeof(buff));
		printf("Server     : %s",buff);
		printf("\n");
			
		if(strcmp(buff,"exit")==0)
			break;
		if(strcmp(buff,"ls")==0)
			f=0;
		
	}while(1);
	
	
	printf("\nconvo ended ");
	close(sockfd);
	return 0;
}
