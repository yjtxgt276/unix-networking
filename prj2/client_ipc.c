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
    printf("dbg ci.c pipefd: %d %d\n", *p1, *p2);
    return 0;
}

int child_setup_ipc(int mode, int rpipe,int wpipe, int rfifo, int wfifo){

	    FIFO_P_W = open(FIFO1,O_WRONLY ,0); // TODO: for dbg only
		perror("dbg ci.c FIFOW open");
	    FIFO_P_R = open(FIFO2,O_RDONLY ,0); //TODO: for dbg only
		perror("dbg ci.c FIFOR open");

    return 0;
}

int parent_setup_ipc(char* cmd, char* arg, int mode){
    //static int old_mode = 0;
		FIFO_P_R = open(FIFO1,O_RDONLY,0);
		    perror("dbg ci.c CLIENT: OPEN FIFOR");
		FIFO_P_W = open(FIFO2,O_WRONLY,0);
		    perror("dbg ci.c CLIENT: OPEN FIFOW");
    return 0;
}

int parent_send_mode(char* cmd, char* arg,int* mode){

    if( strcmp("switch",cmd)==0 ){
	    printf("dbg ci.c arg: %s\n",arg);
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
	    printf("dbg ci.c mode: %d\n",*mode);
	    write(PIPE_MODE_W,mode,sizeof(int));	//TODO: define 4
	}
    return 0;
}















