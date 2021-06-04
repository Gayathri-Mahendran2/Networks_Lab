#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8081
#define SA struct sockaddr 

int main()
{
	int sockfd, connfd, len;
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) !=0)
	{
		printf("socket bind failed...\n");
		exit(0); 
	}
	else
		printf("Socket successfully binded..\n");
	if ((listen(sockfd, 5)) != 0) 
	{
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli); 
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) 
	{
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");
	bzero(buff, MAX); 
	read(connfd, buff, sizeof(buff));
	printf("From client: %s\n", buff);
	int t=0;
	int vowels = 0, alphabet = 0, digit = 0,specialChar=0; 
 	
    while(buff[t]!='\0') 
    { 
           
        char ch = buff[t]; 
  		ch = tolower(ch);

        if ( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ) 
        { 
        	alphabet++;
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') 
            	vowels++; 
        } 
        else if (ch >= '0' && ch <= '9') 
            digit++; 
        else if(ch=='\n'|| ch=='\t')
        	;
        else
            specialChar++; 

        t++;
    } 

    printf("The number of digits is %d\n",digit);
    printf("The number of alphabets is %d\n",alphabet);
    printf("The number of vowels is %d\n",vowels);
    printf("The number of special characters is %d\n",specialChar);

	//write(connfd, buff, sizeof(buff));
	close(sockfd);
}