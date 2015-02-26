#include "px_server.h"

<<<<<<< HEAD
int px_server(sem_t* sem_c,sem_t* sem_p, int shmfd){
=======
int px_server(sem_t* sem, int shmfd){
    /*lock sem*/
	px_sem_lock(sem);
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
    printf("px_server: started\n");
    char cmd[MAX_LEN], rslt[SHM_SIZE];
    //sem_t* sem;
    while(1){
<<<<<<< HEAD
    /*lock sem*/
	px_sem_lock(sem_c);
=======
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
    /*read cmd from shm*/
	px_read_shm(cmd,shmfd); 
    /*process cmd*/
	process_cmd(cmd,rslt);
    /*write rslt to shm*/
	px_write_shm(rslt,shmfd);
    /*unlock sem*/
<<<<<<< HEAD
	px_sem_unlock(sem_p);
	//sleep(1);
=======
	px_sem_unlock(sem);
	sleep(1);
    /*lock sem*/
	px_sem_lock(sem);
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
    }
    return 0;
}
