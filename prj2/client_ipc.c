#include "client_ipc.h"
int parent_fifos_creat(char* fifo1,char* fifo2){
    if( -1 == mkfifo(fifo1,FILE_MODE) )
	perror("mkfifo");
    if( -1 == mkfifo(fifo2,FILE_MODE) )
	perror("mkfifo");
    return 0;
}

int parent_pipes_creat(int* p1, int* p2){
    if(-1==pipe(p1))
	perror("pipe");
    if(-1==pipe(p2))
	perror("pipe");
    return 0;
}

int parent_setup_ipc(int* svmqid){
/**pipe was setup in main*/
/** open fifo*/
    FIFO_P_R = open(FIFO1,O_RDONLY,0);
    FIFO_P_W = open(FIFO2,O_WRONLY,0);
/**setup svmq*/
    int key;
    key = ftok(SVMQ,KEY);
    *svmqid = msgget(key, 0666 | IPC_CREAT);
    return 0;
}

int parent_send_mode(char* cmd, char* arg,int* mode){

    if( strcmp("switch",cmd)==0 ){
	   if( !strcmp("pipe",arg) ){
		*mode = 1 ; 
	    }
	    else if( !strcmp("fifo",arg) ){
		*mode = 2;
	    }
	    else if( !strcmp("svmq",arg) ){
		*mode = 3;
	    }
	    else if( !strcmp("pomq",arg) ){
		*mode = 4;
	    }
	    write(PIPE_MODE_W,mode,sizeof(int));
	}
    return 0;
}

