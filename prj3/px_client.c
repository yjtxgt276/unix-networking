#include "px_client.h"

int main(int argc, char** argv){
    char cmd[MAX_LEN], data[SHM_SIZE];
    sem_t *sem_p;
    sem_t *sem_c;
    int shmfd;
    char* shm_name = "px_shm.o";
    char* sem_name_p= "px_sem_p.o";
    char* sem_name_c= "px_sem_c.o";
/*create semaphore*/    
    if(( sem_p = sem_open(sem_name_p,O_CREAT|O_EXCL, 0666, 0)) == SEM_FAILED){
	perror("sem_open");
	exit(-1);
    }
    if(( sem_c = sem_open(sem_name_c,O_CREAT|O_EXCL, 0666, 0)) == SEM_FAILED){
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
	px_server(sem_c,sem_p, shmfd);
    }
    else{
	while(1){
    /*get user cmd*/
	    printf("px_client: enter your command:\n");
	    if(read(STDIN_FILENO,cmd, MAX_LEN) == -1)
		perror("px_client:get cmd"); 
    /*valid cmd*/
<<<<<<< HEAD
	    int rev = 0;
	    if((rev = valid_cmd(cmd)) == -1)
		continue;   
	    else if(rev == ALL_EXIT){
		printf("exiting...\n");
		px_cleanup(sem_p,sem_c,sem_name_p,sem_name_c,shm_name);
		kill(0,SIGINT);
		exit(1);
	    }
    /*write cmd to shm*/
	    px_write_shm(cmd,shmfd);
    /*unlock sem*/
	    px_sem_unlock(sem_c);
=======
	    if(valid_cmd(cmd) == -1);
		//continue;   
    /*write cmd to shm*/
	    px_write_shm(cmd,shmfd);
    /*unlock sem*/
	    px_sem_unlock(sem);
	//    sleep(1);
>>>>>>> parent of 571fda7... px sem race, put a sleep to solve it temply
    /*lock sem*/
	    px_sem_lock(sem_p);
    /*read shm*/
	    px_read_shm(data, shmfd);
    /*display rslt*/
	    display(data);
	}
    }
    return 0;
}

    
    
    
   
    
