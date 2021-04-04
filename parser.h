#ifndef PARSER_H
#define PARSER_H   // PARSE_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

#define PARSE_BUFFSIZE 1024

typedef struct {
	char nick[PARSE_BUFFSIZE];
	char user[PARSE_BUFFSIZE];
	char host[PARSE_BUFFSIZE];
	char header_state[PARSE_BUFFSIZE];
	char channel[PARSE_BUFFSIZE];
	char message[PARSE_BUFFSIZE];
} BUFF_CONTENT;

int getLength(char* msg);
int is_string_vaild_for_parse(char* p, size_t len);
BUFF_CONTENT* BUFF_CONTENT_NEW();
char* parse_nick_usr_host(BUFF_CONTENT* content, char* p, char* char_start, int* is_parsed);
BUFF_CONTENT* getBufContent(char* p, size_t n);


#endif // PARSER_H	
