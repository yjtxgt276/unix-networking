#include "server_ipc.h"
int server_set_ipc(int mode){
    switch(mode){
	case 1: //pipe closed by child already 
	    printf("********SERVER:ipc mode: pipe");
	    /***  see if it works
	    if( -1 == close(STDIN_FILENO) )
		perror("CHILD:closing stdin");
	    if( -1 == dup2(PIPE_C_R,STDIN_FILENO) )
		perror("CHILD: dup2 pipe");
	    if( -1 == close(STDOUT_FILENO) )
		perror("CHILD:closing stdout");
	    if( -1 == dup2(PIPE_C_W,STDOUT_FILENO) )
		perror("CHILD: dup2 pipe");
		*/
	    break;
	case 2: //fifo
	    printf("********SERVER:ipc mode: fifo");
	    ///////// dbg: opened fifo in cl.c///////////
	    /////////
	    /*if( -1 == (FIFO_C_W = open("fifo1.o",O_WRONLY,0)))
		perror("dbg si.c FIFOW open");
	    if( -1 == (FIFO_C_R = open("fifo2.o",O_RDONLY,0)))
		perror("dbg si.c FIFOR open");
	    */
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

















