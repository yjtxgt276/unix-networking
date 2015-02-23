#include "sv_util.h"

int sv_sem_init(key_t key, int nsems){
    int i;
    union semnum arg;
    struct semid_ds buf;
    struct sembuf sb;
    int semid;

    semid = semget(key,nsems,IPC_CREAT|IPC_EXCL|0666);
    if(semid>=0){
	sb.sem_op=1;
	arg.val=1;
	for(sb.sem_num=0;sb.sem_num<nsems;sb.sem_num++){
	    if(semop(semid,&sb,1)==-1){
		int e = errno;
		semctl(semid,0,IPC_RMID);	
		errno = e;
		return -1;
	    }	
	}	
    }else if(errno==EEXIST){
	int ready =0;
	semid=semget(key,nsems,0);	
	if(semid<0)
	    return semid;
	arg.buf = &buf;
	for(i=0;i<MAX_RETRIES && !readdy; i++){
	    semctl(semid,nsems-1,IPC_STATC,0);
	    if(arg.buf->sem_otime!=0)
		ready = 1;
	    else
		sleep(1);
	}
	if(!ready){
	    errno = ETIME;	
	    return -1;
	}
    }else
	return semid;
    return semid;
}

int sv_sem_lock(int semid){
    struct sembuf sbop;
    sbop.sem_num=0;
    sbop.sem_op = -1;
    sbop.sem_flag = SEM_UNDO;
    printf("sv_client: trying to lock the sem\n");
    if(semop(semid,&sbop,1)==-1){
	perror("semop"); 
	exit(1);
    }
    printf("sv_client: sem locked\n");
    return 0;
}

int sv_sem_unlock(int semid){
    struct sembuf sbop;
    sbop.sem_num=0;
    sbop.sem_op = 1;
    sbop.sem_flag = SEM_UNDO;
    printf("sv_client: trying to unlock the sem\n");
    if(semop(semid,&sbop,1)==-1){
	perror("semop"); 
	exit(1);
    }
    printf("sv_client: sem unlocked\n");
    return 0;
}

































