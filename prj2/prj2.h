/**prj2.h*/
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
#include <sys/msg.h>
#include <mqueue.h>
#include <fcntl.h>

#define CMD_LEN 20
#define MAX_LEN 200
#define FNAME_LEN 180
#define MAX_BUF 8192-2*sizeof(int) 
#define FIFO1 "fifo1.o"
#define FIFO2 "fifo2.o"
#define SVMQ "prj2.h"
#define KEY 'Z'
#define POMQ_P "/pomq_p.o"
#define POMQ_C "/pomq_c.o"

typedef struct{
    int mesg_len; 
    int mesg_type;  // used for ipc mode
    char mesg_data[MAX_BUF];
}MESG;

typedef struct{
    long mytype;
    MESG mesg;
}SVMESG;

void cleanup();

#endif

