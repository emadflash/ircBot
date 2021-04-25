#include "./parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PRINT_PARSED_CONTENT(BUFF_CONTENT *b) {
  printf("%s\n", b->nick);
  printf("%s\n", b->user);
  printf("%s\n", b->host);
  printf("%s\n", b->header_state);
  printf("%s\n", b->channel);
  printf("%s\n", b->message);
  printf("---------------------------------------------------------\n");
}

void TEST_READ_FROM_FILE_AND_PARSE() {
  FILE *fp = fopen("./note.txt", "r");
  char *buffer = (char *)malloc(2000 * sizeof(char));
  while (fgets(buffer, 2000, fp) != NULL) {
    if (is_string_vaild_for_parse(buffer, strlen(buffer)) < 0)
      continue;
    else {
      BUFF_CONTENT *b = BUFF_CONTENT_NEW(buffer, strlen(buffer));
      b = getBufContent(buffer, sizeof(buffer));
      PRINT_PARSED_CONTENT(b);
      free(b);
    }
  }
  free(buffer);
  fclose(fp);
}

void TEST_PRINT_CONTENT(char *msg) {
  BUFF_CONTENT *b;
  if (is_string_vaild_for_parse(msg, strlen(msg)) == 0) {
    b = BUFF_CONTENT_NEW(msg, sizeof(msg));
    b = getBufContent(msg, sizeof(msg));
    PRINT_PARSED_CONTENT(b);
    free(b);
  }
}

void TEST_VAILD_MESSAGE(char *p) {
  BUFF_CONTENT *b = BUFF_CONTENT_NEW(p, strlen(p));
  int d = is_string_vaild_for_parse(p, strlen(p));
  if (d < 0)
    printf("TEST_VAILD_MESSAGE() not vaild\n");
  else
    printf("TEST_VAILD_MESSAGE() vaild\n");
  free(b);
}

int main() {
  char *msg = ":drmessano!drmessano@pdpc/supporter/active/drmessano PRIVMSG "
              "##networking :I think they had 8086 CPUs in them, because when "
              "you enabled";
  // TEST_VAILD_MESSAGE(msg);
  // TEST_READ_FROM_FILE_AND_PARSE();
  TEST_PRINT_CONTENT(msg);
  return 0;
}
