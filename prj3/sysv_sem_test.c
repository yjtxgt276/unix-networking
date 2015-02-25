#include "ipc_util.h" 
int main(){

    key_t key;
    int semid;
    struct sembuf sb;

    sb.sem_num=0; sb.sem_op = -1; sb.sem_flg = SEM_UNDO;

    if((key = ftok("prj3.h",'X'))==-1){
	perror("ftok"); 
	exit(1);
    }

    if((semid = initsem(key,1))==-1){
	perror("initsem"); 
	exit(1);
    }

    printf("Press return to lock: ");
    getchar();
    printf("trying to lock...\n");

    if(semop(semid,&sb,1)==-1){
	perror("semop"); 
	exit(1);
    }

    printf("locked.\n");
    printf("Press return to unlock: ");
    getchar();

    sb.sem_op=1;
    if(semop(semid, &sb, 1)== -1){
	perror("semop");
	exit(1);
    }

    printf("Unlocked\n");
    return 0;
}




























