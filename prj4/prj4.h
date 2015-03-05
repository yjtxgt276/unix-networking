#ifndef PRJ4_H
#define PRJ4_H
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define TCP_PORT "5000"
#define UDP_PORT "5001"
#define MAXDATASIZE 500
#define CMD_LEN 50
#define FN_LEN 150
#define MAX_LEN 200
#define ALL_EXIT 100
#define BACKLOG 10

#endif
