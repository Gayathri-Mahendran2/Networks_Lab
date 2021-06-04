#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void chat(int sockfd)
{ 
	char buff[MAX]; 
	int n; 
	for (;;) 
	{ 
		bzero(buff, MAX);  
		read(sockfd, buff, sizeof(buff)); 
		printf("Message from client: %s\t Message to client : ", buff); 
		bzero(buff, MAX); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n') 
			; 
		write(sockfd, buff, sizeof(buff)); 
		if (strncmp("exit", buff, 4) == 0) 
		{ 
			printf("Server Exit\n"); 
			break; 
		} 
	} 
} 

int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed\n"); 
		exit(0); 
	} 
	else
		printf("Socket created\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind fail\n"); 
		exit(0); 
	} 
	else
		printf("Socket binded\n"); 

	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed\n"); 
		exit(0); 
	} 
	else
		printf("Server listening\n"); 
	len = sizeof(cli); 

	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client\n"); 
	 
	chat(connfd);
	close(sockfd); 
} 
