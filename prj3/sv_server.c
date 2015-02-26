#include "sv_server.h"
int sv_server(int semid, int shmid){
    char cmd[MAX_LEN], rslt[SHM_SIZE];
    while(1){
/*wakes up,try to lock sem, block here*/
	sv_sem_lock(semid);	    
/*get cmd from client*/
	sv_read_shm(cmd, shmid);//TODO
/*process cmd, writes result back*/
	process_cmd(cmd,rslt); 
	sv_write_shm(rslt,shmid);//TODO
/*release sem, go to sleep*/
	sv_sem_unlock(semid);
    }
    return 0;
}
