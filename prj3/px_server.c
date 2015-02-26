#include "px_server.h"

int px_server(sem_t* sem_c,sem_t* sem_p, int shmfd){
    printf("px_server: started\n");
    char cmd[MAX_LEN], rslt[SHM_SIZE];
    //sem_t* sem;
//    sem = sem_open("px_sem.o",0);
    while(1){
    /*lock sem*/
	px_sem_lock(sem_c);
    /*read cmd from shm*/
	px_read_shm(cmd,shmfd); 
    /*process cmd*/
	process_cmd(cmd,rslt);
    /*write rslt to shm*/
	px_write_shm(rslt,shmfd);
    /*unlock sem*/
	px_sem_unlock(sem_p);
	//sleep(1);
    }
    return 0;
}
