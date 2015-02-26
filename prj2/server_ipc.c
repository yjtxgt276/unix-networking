<<<<<<< HEAD
=======
/**server_ipc.c*/
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
#include "server_ipc.h"
int server_set_ipc(int* svmqid){
	    int key = ftok(SVMQ,KEY);
	    *svmqid = msgget(key,0666);
    return 0;
}





