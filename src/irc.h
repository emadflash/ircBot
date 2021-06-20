#ifndef IRC_H
#define IRC_H // IRC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#define COMMAND_BUFSIZE 1024
#define INFO_BUFSIZE 120

typedef struct {
    char nickName[INFO_BUFSIZE];
    char userName[INFO_BUFSIZE];
    char realName[INFO_BUFSIZE];
    char serverName[INFO_BUFSIZE];
    char password[INFO_BUFSIZE];
} LOGIN_INFO;

int is_pong_request(char *msg);

LOGIN_INFO *LOGIN_INFO_NEW();
void LOGIN_INFO_DESTROY(LOGIN_INFO *c);
int irc_send(int server, char *msg, size_t len);
int irc_recv(int server, char *msg, size_t len);
int irc_join(int server, const char *channel);
int irc_login(int server, LOGIN_INFO *info);
int irc_pong(int server, char *msg, size_t len);

#endif // IRC_H
