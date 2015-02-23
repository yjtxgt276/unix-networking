#ifndef SV_UTIL_H 
#define SV_UTIL_H
#include "prj3.h"
union semnum{	//
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int sv_sem_init(key_t key, int nsems);
int sv_sem_lock(int semid);
int sv_sem_unlock(int semid);




#endif



























