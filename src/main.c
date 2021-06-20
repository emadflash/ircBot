#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECV_BUFSIZE 4096

#include "client.h"
#include "config.h"
#include "irc.h"

void callback(int socket_fd, char *buffer, size_t len) {
    /* if receive ping request then send authentication token
     */
    if (is_pong_request(buffer) == 0) {
        if (irc_pong(socket_fd, buffer, RECV_BUFSIZE) < 0) {
            perror("irc_pong() failed");
        }
    }
    printf("%s", buffer);
}

int main() {
    client_sock_t *client = (client_sock_t *)calloc(1, sizeof(client_sock_t));
    strcpy(client->ip, node);
    client->port = port;

    if (client_sock_t_initialize(client) < 0) {
        perror("client_sock_t_initialize() failed");
        exit(EXIT_FAILURE);
    }
    // connect to server
    if (client_sock_t_connect(client)) {
        perror("client_sock_t_connect() failed");
        exit(EXIT_FAILURE);
    }

    LOGIN_INFO *c = LOGIN_INFO_NEW();

    if ((irc_login(client->socket_fd, c)) < 0) {
        perror("irc_login() failed");
        exit(EXIT_FAILURE);
    }

    LOGIN_INFO_DESTROY(c);

    if ((irc_join(client->socket_fd, CHANNEL)) < 0) {
        perror("irc_join() failed");
    }

    client_sock_t_listen(client, callback);
    client_sock_t_destroy(client);
    return 0;
}
