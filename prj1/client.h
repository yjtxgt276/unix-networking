#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define CMD_LEN 20
#define MAX_LEN 200
#define FNAME_LEN 180

static void client_handler(int);
#endif
