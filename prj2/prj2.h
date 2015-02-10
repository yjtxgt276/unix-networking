#ifndef	PRJ2_H 
#define PRJ2_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#define CMD_LEN 20
#define MAX_LEN 200
#define FNAME_LEN 180
#define MAX_BUF 4096-2*sizeof(int) // sizeof int portable?
#define FIFO1 "fifo1.o"
#define FIFO2 "fifo2.o"
//#define PIPE_MODE_R 3
//#define PIPE_MODE_W 4


/**COMMAND struct is not used*/
typedef struct{
    char *cmd;
    char *arg;
    int cmdlen;
    int arglen;
    //int ipc_mode = -1;
}COMMAND;

typedef struct{
    int mesg_len; // length of what?
    int mesg_type;  // used for ipc mode
    char mesg_data[MAX_BUF];
}MESG;



#endif












