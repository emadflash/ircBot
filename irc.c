#include "./irc.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

LOGIN_INFO *LOGIN_INFO_NEW() {
  LOGIN_INFO *c = (LOGIN_INFO *)malloc(sizeof(LOGIN_INFO));

  strcpy(c->userName, DEFAULT_USER_NAME);
  strcpy(c->nickName, DEFAULT_NICK_NAME);
  strcpy(c->realName, DEFAULT_REAL_NAME);
  strcpy(c->serverName, "localhost");
  memset(c->password, 0, sizeof(c->password));

  return c;
}

void LOGIN_INFO_DESTROY(LOGIN_INFO *c) { free(c); }

int is_pong_request(char *msg) {
  char tmp[5];
  if (memcpy(tmp, msg, 4) == NULL || strlen(msg) <= 0) {
    return -1;
  }
  tmp[4] = '\0';
  return strcmp(tmp, "PING");
}

int irc_send(int server, char *msg, size_t len) {
  if (send(server, msg, len, 0) < 0)
    return -1;
  return 0;
}

int irc_recv(int server, char *msg, size_t len) {
  if ((recv(server, msg, len, 0)) < 0) {
    perror("recv() failed");
    return -1;
  }
  return 0;
}

int irc_login(int server, LOGIN_INFO *info) {
  char cmd_user[COMMAND_BUFSIZE];
  char cmd_nick[COMMAND_BUFSIZE];

  // make login info command
  sprintf(cmd_user, "USER %s localhost %s :%s\r\n", info->userName,
          info->serverName, info->realName);
  sprintf(cmd_nick, "NICK %s\r\n", info->nickName);

  if (irc_send(server, cmd_user, strlen(cmd_user)) < 0)
    return -1;
  if (irc_send(server, cmd_nick, strlen(cmd_nick)) < 0)
    return -1;

  return 0;
}

int irc_join(int server, char *channel) {
  char cmd_join[COMMAND_BUFSIZE];
  sprintf(cmd_join, "JOIN %s\r\n", channel);
  if (irc_send(server, cmd_join, strlen(cmd_join)) < 0)
    return -1;
  return 0;
}

int irc_pong(int server, char *msg, size_t len) {
  char cmd_pong[len];
  char *p = strchr(msg, ':');
  p = p + 1;
  sprintf(cmd_pong, "PONG %s\r\n", p);

  if (irc_send(server, cmd_pong, strlen(cmd_pong)) < 0)
    return -1;
  return 0;
}
