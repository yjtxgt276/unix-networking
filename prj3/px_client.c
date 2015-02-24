#include "px_client.h"

int main(int argc, char** argv){
    char cmd[MAX_LEN], data[SHM_SIZE];
    sem_t *sem;
    int shmfd;
    char* shm_name = "px_shm.o";
    char* sem_name= "px_sem.o";
/*create semaphore*/    
    if(( sem = sem_open(sem_name,O_CREAT|O_EXCL, 0666, 0)) == SEM_FAILED){
	perror("sem_open");
	exit(-1);
    }
    //sem_unlink(sem_name);
/*create shm*/
    if((shmfd = px_shm_init(shm_name)) == -1)
	exit(-1);
/*lock sem*/
    //px_sem_lock(sem);
/*fork to call server*/
    if( fork() == 0){
	px_server(sem, shmfd);
    }
    else{
	while(1){
    /*get user cmd*/
	    printf("px_client: enter your command:\n");
	    if(read(STDIN_FILENO,cmd, MAX_LEN) == -1)
		perror("px_client:get cmd"); 
    /*valid cmd*/
	    if(valid_cmd(cmd) == -1);
		//continue;   
    /*write cmd to shm*/
	    px_write_shm(cmd,shmfd);
    /*unlock sem*/
	    px_sem_unlock(sem);
	//    sleep(1);
    /*lock sem*/
	    px_sem_lock(sem);
    /*read shm*/
	    px_read_shm(data, shmfd);
    /*display rslt*/
	    display(data);
	}
    }
    return 0;
}

    
    
    
   
    
