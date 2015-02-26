#include "sv_util.h"

int sv_sem_init(key_t key, int nsems){
// for client
    int i, semid;
    union semun arg;
    struct semid_ds buf;
    struct sembuf sb;

    semid = semget(key,nsems,IPC_CREAT|IPC_EXCL|0666);
    if(semid>=0){   // create the sem
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
	//exist, simply connect to it
	int ready =0;
	semid=semget(key,0,0);	
	if(semid<0)
	    return semid;
	arg.buf = &buf;
	if(!ready){
	    semctl(semid,nsems-1,IPC_STAT,0);
	    if(arg.buf->sem_otime!=0)
		ready = 1;
	    else
		return -1;
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
// for both
    struct sembuf sbop;
    sbop.sem_num=0;
    sbop.sem_op = -1;
    sbop.sem_flg = SEM_UNDO;
    printf("sv_sem_lock: trying to lock the sem\n");
    if(semop(semid,&sbop,1)==-1){
	perror("semop"); 
	return(1);
    }
    printf("sv_sem_lock: sem locked\n");
    return 0;
}

int sv_sem_unlock(int semid){
//for both
    struct sembuf sbop;
    sbop.sem_num=0;
    sbop.sem_op = 1;
    sbop.sem_flg = SEM_UNDO;
    printf("sv_sem_unlock: trying to unlock the sem\n");
    if(semop(semid,&sbop,1)==-1){
	perror("semop"); 
	return(1);
    }
    printf("sv_sem_unlock: sem unlocked\n");
    return 0;
}

int sv_write_shm(char *str, int shmid){
    char *shmp; 
    shmp = (char*) shmat(shmid,(void*)0,0);
    if(shmp==(char*)(-1)){
	perror("shmat"); 
	return (-1);
    }
    printf("sv_write_shm: writing to shm...\n");
    //strncpy(data, str, SHM_SIZE);
    memcpy(shmp, str,SHM_SIZE);
    if(shmdt(shmp)==-1){
	perror("shmdt"); 
	return (-1);
    }

    return 0;
}

int sv_read_shm(char *dest, int shmid){
    char* data; 
    if((data=shmat(shmid,(void*)0,0))==(char*)(-1)){
	perror("shmat"); 
	return (-1);
    }
    printf("sv_read_shm: reading from shm...\n");
    strncpy(dest, data, SHM_SIZE);
    if(shmdt(data)==-1){
	perror("shmdt"); 
	return (-1);
    }
    return 0;
}



