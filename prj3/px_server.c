#include "px_server.h"

int px_server(sem_t* sem, int shmfd){
    /*lock sem*/
	px_sem_lock(sem);
    printf("px_server: started\n");
    char cmd[MAX_LEN], rslt[SHM_SIZE];
    //sem_t* sem;
    while(1){
    /*read cmd from shm*/
	px_read_shm(cmd,shmfd); 
    /*process cmd*/
	process_cmd(cmd,rslt);
    /*write rslt to shm*/
	px_write_shm(rslt,shmfd);
    /*unlock sem*/
	px_sem_unlock(sem);
	sleep(1);
    /*lock sem*/
	px_sem_lock(sem);
    }
    return 0;
}
