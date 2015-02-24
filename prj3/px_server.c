#include "px_server.h"

int px_server(sem_t *sem, int shmfd){
    char cmd[MAX_LEN], rslt[SHM_SIZE];
    while(1){
    /*lock sem*/
	px_sem_lock(sem);
    /*read cmd from shm*/
	px_read_shm(cmd,shmfd); 
    /*process cmd*/
	process_cmd(cmd,rslt);
    /*write rslt to shm*/
	px_write_shm(rslt,shmfd);
    /*unlock sem*/
	px_sem_unlock(sem);
    }
    return 0;
}
