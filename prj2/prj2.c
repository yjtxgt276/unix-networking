#include "prj2.h"
<<<<<<< HEAD

=======
/**prj2.c*/
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
void cleanup(){
    int key = ftok(SVMQ,KEY);
    int svmqid = msgget(key,0666);
    if( -1 == remove(FIFO1))
	perror("remove fifo1");
    if( -1 == remove(FIFO2))
	perror("remove fifo2");
    msgctl(svmqid, IPC_RMID,NULL);
    mq_unlink(POMQ_P);
    mq_unlink(POMQ_C);
}
