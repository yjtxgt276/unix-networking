#include "sv_client.h"

int main(int argc, char** argv){
    char cmd[CMD_LEN];
/**create semaphore*/
    key_t key;
    int semid;
    /*TODO REMOVE if not needed
    struct sembuf sb;
    sb.sem_num = 0; // ops on the only sem[0]
    sb.sem_op = -1; //	try to -1 on semval of sem[0]
    sb.sem_flag = SEM_UNDO; // sem undo after termination
    */
    if((key = ftok("prj3.h",'X'))==-1){	// get key
	perror("ftok");
	exit(1);
    }
    if((semid = sv_sem_init(key,1))==-1){   //init the sem
	perror("sv_sem_init");
	exit(1);
    }
/*lock the semaphore*/
    sv_sem_lock(semid);
/*create shared memory seg*/


/*fork the server, server goes to wait*/
    int pid;
    if((pid=fork())==0){
    /**child*/
	execl("sv_server.exe","sv_server.exe",NULL); 
    }
    else{
    /*parent*/ 
	while(1){
/*get user cmd*/	
	    get_cmd(cmd);   //TODO implement func
/*check cmd*/
	    valid_cmd(cmd); //TODO implement func
/*write cmd to sham and goes waiting*/
	    write_sham(cmd,SHAMID); //TODO implement func, SHAMID
/*unlock the semaphore*/
	    sv_sem_unlock(semid);
/*wake up, lock semaphore and get result from server*/
	    sv_em_lock(semid);
	    read_sham(rslt,SHAMID); // TODO implement func, SHAMID
/*show result*/
	    display(rslt);
	}
    }
    return 0;
}


















