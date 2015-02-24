#include "sv_client.h"

int main(int argc, char** argv){
    char cmd[CMD_LEN];
/**create semaphore*/
    key_t key;
    int semid,shmid;
    char data[SHM_SIZE];

    if((key = ftok("prj3.h",'X'))==-1){	// get key
	perror("ftok");
	return(1);
    }
    if((semid = sv_sem_init(key,1))==-1){   //init the sem
	perror("sv_sem_init");
	return(1);
    }
/*create shared memory seg*/
    if((shmid=shmget(key,SHM_SIZE,IPC_CREAT|0644))==-1){
	perror("shmget"); 
	return(1);
    }
/*lock the semaphore*/
    sv_sem_lock(semid);
/*fork the server, server goes to wait cuz the lock above TODO*/
//    int pid;
    if((fork())==0){
    /**child*/
//	execl("sv_server.exe","sv_server.exe",NULL); 
	sv_server(semid, shmid);
    }
    else{
    /*parent*/ 
	while(1){
/*get user cmd*/	
	    printf("sv_client: enter your command:\n");
	    //if(fgets(cmd,MAX_LEN,stdin)==NULL)
	    if(read(STDIN_FILENO,cmd,MAX_LEN)==-1)
		perror("fgets");   
/*check cmd*/
	    if(sv_valid_cmd(cmd) == -1)
		continue; 
/*write cmd to sham and goes waiting*/
	    sv_write_shm(cmd,shmid); //
/*unlock the semaphore*/
	    sv_sem_unlock(semid);
/*wake up, lock semaphore and get result from server*/
	    sv_sem_lock(semid);
	    sv_read_shm(data,shmid); // 
/*show result*/
	    sv_display(data);
	}
    }
    return 0;
}


















