#ifndef UTILS_H
#define UTILS_H // UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

typedef struct {
  int client_fd;
  char *buffer;
  size_t buffer_size;
} client_packet;

typedef struct {
  char ip[500];
  int port;
  int socket_fd;
  struct sockaddr_in socket_addr;
  struct hostent *host;
} client_sock_t;

void client_sock_t_destroy(client_sock_t *sock) {
  close(sock->socket_fd);
  free(sock);
}

int client_sock_t_connect(client_sock_t *sock) {
  if (connect(sock->socket_fd, (struct sockaddr *)&sock->socket_addr,
              sizeof(sock->socket_addr))) {
    return -1;
  }
  return 0;
}

/* bind server socket to port and ip */
int client_sock_t_initialize(client_sock_t *sock) {
  struct sockaddr_in address;
  int server = socket(AF_INET, SOCK_STREAM, 0);
  if (server < 0) {
    perror("socket() failed");
    return -1;
  } else {
    sock->host = gethostbyname(sock->ip); // resolve host
    address.sin_family = AF_INET;
    struct hostent *_host = sock->host;
    address.sin_addr.s_addr = *(unsigned int *)_host->h_addr;
    address.sin_port = htons((unsigned short)sock->port);
  }
  sock->socket_fd = server;
  sock->socket_addr = address;
  return 0;
}

/* continously reading data from server */
void client_sock_t_listen(client_sock_t *sock, void (*f)(int, char *, size_t)) {
  char buffer[BUFFER_SIZE];
  while (1) {
    memset(buffer, '\0', BUFFER_SIZE); // make sure buffer is empty
    if (recv(sock->socket_fd, buffer, BUFFER_SIZE - 1, 0) < 0) {
      perror("recv() failed");
    } else
      (*f)(sock->socket_fd, buffer,
           strlen(buffer)); // send buffer to callback function
  }
}

void tor_connect(client_sock_t *tor_client) {
  if (client_sock_t_initialize(tor_client) < 0) { // initialize tor connection
    perror("tor_connect::client_sock_t_initialize() failed");
    exit(EXIT_FAILURE);
  }
  if (client_sock_t_connect(tor_client) < 0) {
    perror("tor_connect:client_sock_t_connect() failed");
    exit(EXIT_FAILURE);
  }
  printf("tor_connect() connected to tor network\n");
}

void tor_authenticate(client_sock_t *tor_client) {
  send(tor_client->socket_fd, (void *)0x05, 3, 0);

  // check response if 0x0 then good
  char response_token[2];
  fprintf(stdout, "tor_authenticate() authenticating.....\n");
  recv(tor_client->socket_fd, response_token, 2, 0);
  if (response_token[1] != 0x0) {
    perror("tor_authenticate() failed");
    exit(EXIT_FAILURE);
  }
  printf("tor_authenticate() success\n");
}


#endif // UTILS_H
