#ifndef SV_UTIL_H 
#define SV_UTIL_H
#include "prj3_util.h"
union semun{	//
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int sv_sem_init(key_t key, int nsems);
int sv_sem_lock(int semid);
int sv_sem_unlock(int semid);




#endif



























