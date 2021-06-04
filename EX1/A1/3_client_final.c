#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8081
#define SA struct sockaddr 

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	char buff[MAX];
	int n;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) 
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!= 0) 
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	bzero(buff, sizeof(buff));
	printf("Enter the string : ");
	n = 0;
	while ((buff[n++] = getchar()) != '\t');
	write(sockfd, buff, sizeof(buff));
	close(sockfd);
}