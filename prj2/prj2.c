#include "prj2.h"

void cleanup(){
    int key = ftok(SVMQ,KEY);
    int svmqid = msgget(key,0666);
    if( -1 == remove(FIFO1))
	perror("remove fifo1");
    if( -1 == remove(FIFO2))
	perror("remove fifo2");
    msgctl(svmqid, IPC_RMID,NULL);
}
