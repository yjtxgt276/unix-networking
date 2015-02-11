/**server_ipc.c*/
#include "server_ipc.h"
int server_set_ipc(int* svmqid){
	    int key = ftok(SVMQ,KEY);
	    *svmqid = msgget(key,0666);
    return 0;
}





