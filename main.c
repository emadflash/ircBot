#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>

#define RECV_BUFSIZE 4096

#include "./irc.h"
#include "./parse.h"

const int port = 6667;
char *node = "irc.freenode.net";

int main() {
	struct sockaddr_in addr;
	struct hostent *host;
	
	// create socket:
    	int server = socket(AF_INET, SOCK_STREAM, 0);
	if(server < 0){
        	perror("socket() failed");
		exit(EXIT_FAILURE);
    	}
	
	host = gethostbyname(node);
	printf("[*] connecting to %s\n", host->h_name);
	
	// set ip and port
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = *(unsigned int*)host->h_addr;
	addr.sin_port = htons((unsigned short)port);

	// connect to server
	if (connect(server, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect() failed");
		exit(EXIT_FAILURE);
	}
	
	LOGIN_INFO* c = LOGIN_INFO_NEW();
	
	if ((irc_login(server, c)) < 0) {
		perror("irc_login() failed");
		exit(EXIT_FAILURE);
	}
	
	LOGIN_INFO_DESTROY(c);
	
	if ((irc_join(server, "#networking")) < 0) {
		perror("irc_join() failed");
	}

	char buffer[RECV_BUFSIZE];
	while(1) {
		memset(buffer, '\0', RECV_BUFSIZE);	// make sure buffer[] is empty
		irc_recv(server, buffer, RECV_BUFSIZE);
		if (is_pong_request(buffer) == 0) {     // check if auth request is sent
			if (irc_pong(server, buffer, RECV_BUFSIZE) < 0) {
				perror("irc_pong failed");
			}
		}
		printf("%s", buffer);
	}
	close(server);	
	
	return 0;
}
