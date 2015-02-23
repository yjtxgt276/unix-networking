#include "sv_server.h"

int main(int argc, char** argv){
    char cmd[CMD_LEN];
/*connect to semaphore or block*/
    key_t key;
    int semid;
    if((key = ftok("prj3.h",'X'))==-1){
	perror("ftok"); 
	exit(1);
    }
    while(1){
	if((semid = semget(key,0,0)) >0)
	    break;
    }
/**/
/*attach to sham*/
    

/*loop*/
    while(1){
/*wakes up, lock sem*/ 
	sv_sem_lock(semid);	    
/*get cmd from client*/
	read_sham(cmd, SHAMID);//TODO
/*process cmd, writes result back*/
	process_cmd(cmd,rslt);//TODO
	write_sham(rslt,SHAMID);//TODO
/*release sem, go to sleep*/
	sv_sem_unlock(semid);
	 
    }
    return 0;
}
