#include "client_ipc.h"

int fifos_creat(char* fifo1,char* fifo2){
    if( -1 == mkfifo(fifo1,FILE_MODE) )
	perror("mkfifo");
    if( -1 == mkfifo(fifo2,FILE_MODE) )
	perror("mkfifo");
    return 0;
}

int pipes_creat(int* p1, int* p2){
    if(-1==pipe(p1))
	perror("pipe");
    if(-1==pipe(p2))
	perror("pipe");
    return 0;
}

int child_setup_ipc(int mode){
    //////for dbg//////////
    //mode = 1;// FOR TEST
    //////////////////////
    switch(mode){
	case 1: //pipe done
	    printf("********SERVER:ipc mode: pipe");
	    if( -1 == close(STDIN_FILENO) )
		perror("CHILD:closing stdin");
	    if( -1 == dup2(PIPE_C_R,STDIN_FILENO) )
		perror("CHILD: dup2 pipe");
	    if( -1 == close(STDOUT_FILENO) )
		perror("CHILD:closing stdout");
	    if( -1 == dup2(PIPE_C_W,STDOUT_FILENO) )
		perror("CHILD: dup2 pipe");
	    break;
	case 2: //fifo
	    printf("********SERVER:ipc mode: fifo");
	    FIFO_C_R = open("fifo2.o",O_RDONLY | O_NONBLOCK,0);
	    FIFO_C_W = open("fifo1.o",O_WRONLY | O_NONBLOCK,0);
	    break;
	case 3: //svmq
	    printf("********SERVER:ipc mode: svmq");
	    break;
	case 4: //pomq
	    printf("********SERVER:ipc mode: pomq");
	    break;
	default:;
    }    
    return 0;
}

int parent_setup_ipc(char* cmd, char* arg, int *mode){
    static int old_mode = 0;
    if( strcmp("switch",cmd)==0 ){
	    printf("dbg ci.c arg: %s\n",arg);
	   if( !strcmp("pipe",arg) ){
		*mode = 1 ; 
		printf("dbg ci.c mode: %d\n",*mode);
	    }
	    else if( !strcmp("fifo",arg) ){
		*mode = 2;
	    printf("dbg ci.c mode: %d\n",*mode);
		if(-1 == (FIFO_P_R = open("fifo1.o",O_RDONLY|O_NONBLOCK,0)))
		    perror("CLIENT: OPEN FIFO");;
		if(-1 == (FIFO_P_W = open("fifo2.o",O_RDONLY|O_NONBLOCK,0)))
		    perror("CLIENT: OPEN FIFO");;
		printf("dbg ci.c mode: %d\n",*mode);
	    }
	    else if( !strcmp("svmq",arg) ){
		*mode = 3;
	    }
	    else if( !strcmp("pomq",arg) ){
		*mode = 4;
	    }
	    printf("dbg ci.c oldmode: %d\tcurmode:%d\n",old_mode, *mode);
	    printf("********CLIENT: ipc mode chosen: %s\n",arg);
	
	if( *mode == old_mode && *mode != 0){
	    printf("********CLIENT: ipc mode unchanged\n");
	}
	else{
	    old_mode = *mode;
	    printf("********CLIENT: IPC mode changed\n");
	}
	    
    }
    return 0;
}
/**
int server_set_ipc(int mode){
    switch(mode){
	case 1: //pipe closed by child already 
	    printf("********SERVER:ipc mode: pipe");
	    ***  see if it works
	    if( -1 == close(STDIN_FILENO) )
		perror("CHILD:closing stdin");
	    if( -1 == dup2(PIPE_C_R,STDIN_FILENO) )
		perror("CHILD: dup2 pipe");
	    if( -1 == close(STDOUT_FILENO) )
		perror("CHILD:closing stdout");
	    if( -1 == dup2(PIPE_C_W,STDOUT_FILENO) )
		perror("CHILD: dup2 pipe");
		*
	    break;
	case 2: //fifo
	    printf("********SERVER:ipc mode: fifo");
	    FIFO_C_W = open("fifo1.o",O_WRONLY,0);
	    FIFO_C_R = open("fifo2.o",O_RDONLY,0);
	    break;
	case 3: //svmq
	    printf("********SERVER:ipc mode: svmq");
	    break;
	case 4: //pomq
	    printf("********SERVER:ipc mode: pomq");
	    break;
	default:;
    }
    return 0;
}
*/
















