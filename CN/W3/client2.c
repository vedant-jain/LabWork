#include "common.h"
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#define PORTNO 10200

int createClientSocket(int sockfd, struct sockaddr_in address){
	int len, result;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(PORTNO);

	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1){
		perror("\nCLIENT ERROR");
		exit(1);
	}
	return sockfd;
}

void performClientTask(int sockfd){
	int n = 1;
	char ch[]="GET /home.html HTTP/1.1\nAccept-Language: en-US\nHost: developer.mozilla.org\nAccept: text/html,application/xhtml+xml\nAccept-Encoding: gzip, deflate, br\n";
	char hello[256];

	ch[strlen(ch)] = '\0';
	write(sockfd, ch, strlen(ch));
	printf("Server sent: \n");
	
		n = read(sockfd, hello, sizeof(hello));
		puts(hello);
	
	exit(0);
}

void terminateSocket(int sockfd){
	close(sockfd);
}

int main(){
	int sockfd, n=1;
	struct sockaddr_in address;

	sockfd = createClientSocket(sockfd, address);
	performClientTask(sockfd);
	terminateSocket(sockfd);
}
