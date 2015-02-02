#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define LINE_LEN 200
#define MAX_LEN 200

int server();
static void server_handler(int);
void read_file(char* );
#endif
