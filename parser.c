#include "./parser.h"

/* why need this ? */
int getLength(char *s) {
  int count = 0;
  for (int i = 0; *(s + i) != '\0'; ++i) {
    count++;
  }
  return count;
}

BUFF_CONTENT *BUFF_CONTENT_NEW() {
  BUFF_CONTENT *b = (BUFF_CONTENT *)calloc(1, sizeof(BUFF_CONTENT));
  return b;
}

int is_string_vaild_for_parse(char *p, size_t len) {
  char tmp[len];
  memcpy(tmp, p, len);
  char *is_at_present = strchr(tmp, '@');
  char *is_exclaim_present = strchr(tmp, '!');
  if (is_at_present != NULL && is_exclaim_present != NULL) {
    return 0;
  }
  return -1;
}

char *parse_nick_usr_host(BUFF_CONTENT *content, char *p, char *char_start,
                          int *is_parsed) {
  int len = p - char_start;
  switch (*p) {
  case '!':
    memcpy(content->nick, char_start, len);
    char_start = p + 1;
    break;
  case '@':
    memcpy(content->user, char_start, len);
    // copy host
    char *token_space = strchr(p, ' ');
    memcpy(content->host, p + 1, token_space - p);
    char_start = token_space + 1;
    *is_parsed = TRUE;
    break;
  }
  return char_start;
}

BUFF_CONTENT *getBufContent(char *p, size_t n) {
  BUFF_CONTENT *content = BUFF_CONTENT_NEW();

  const char *last_ptr = p + getLength(p); // create copy of buffer
  char *char_start = p + 1;
  int have_parsed_nick_usr_host = FALSE;
  while (*p++ != '\0') {
    // ---SxxxxxxEI---
    if (have_parsed_nick_usr_host == FALSE) {
      char_start = parse_nick_usr_host(content, p, char_start,
                                       &have_parsed_nick_usr_host);
    } else {
      char *token_space = strchr(char_start, ' ');
      memcpy(content->header_state, char_start, token_space - char_start);

      char_start = token_space + 1;
      if (strchr(char_start, ':') == NULL) {
        // recv buffer contains no message body
        memcpy(content->channel, char_start, last_ptr - char_start);
        memset(content->message, '\0', 120);
        goto DONE_PARSE;
      } else {
        // recv buffer contains some message, parse that too
        char *token_colon = strchr(char_start, ':');
        memcpy(content->channel, char_start, token_colon - char_start);
        memcpy(content->message, token_colon + 1, last_ptr - token_colon);
        goto DONE_PARSE;
      }
    }
  }

DONE_PARSE:
  return content;
}
