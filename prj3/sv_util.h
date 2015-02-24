#ifndef SV_UTIL_H 
#define SV_UTIL_H
#include "prj3.h"
#define SHM_SIZE 4096
union semun{	//
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int sv_sem_init(key_t key, int nsems);
int sv_sem_lock(int semid);
int sv_sem_unlock(int semid);




#endif



























