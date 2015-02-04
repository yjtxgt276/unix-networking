#include "ipc_util.h"


int pipes_creat(int* p1, int* p2){
    if(-1==pipe(p1))
	perror("pipe");
    if(-1==pipe(p2))
	perror("pipe");
    return 0;
}

int child_setup_ipc(int mode){
    mode = 1;// FOR TEST
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
    printf("dbg iu.c 40, cmd: %s\n", cmd);
    static int old_mode = 0;
    if( strcmp("switch",cmd)==0 ){
	printf("oldmode: %d\tcurmode:%d\n",old_mode, *mode);
	if( *mode == old_mode && *mode != 0){
	    printf("********CLIENT: ipc mode unchanged\n");
	    return 0;
	}
	if( !strcmp("pipe",arg) ){
	    *mode = 1;
	    old_mode = *mode ; 
	    printf("********CLIENT: ipc mode chosen: pipe\n");
	}
	else if( !strcmp("fifo",arg) ){
	    old_mode = *mode = 2;
	    printf("********CLIENT: ipc mode chosen: fifo\n");
	}
	else if( !strcmp("svmq",arg) ){
	    old_mode = *mode = 3;
	    printf("********CLIENT: ipc mode chosen: svmq\n");
	}
	else if( !strcmp("pomq",arg) ){
	    old_mode = *mode = 4;
	    printf("********CLIENT: ipc mode chosen: pomq\n");
	}
    }
    return 0;
}
