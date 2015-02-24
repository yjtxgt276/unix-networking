#include "px_util.h"

int px_shm_init(char* name){
    int fd;
    if((fd = shm_open(name, O_CREAT|O_RDWR|O_EXCL, 0666)) == -1){
	perror("shm_open");
	return(-1);
    }
    ftruncate(fd,SHM_SIZE);
    return fd;
}
int px_sem_lock(sem_t* sem){
    printf("px_sem_lock: trying to lock...\n");
    if(sem_wait(sem) == -1){
	perror("px_sem_lock"); 
	return(-1);
    }
    printf("px_sem_lock: sem locked\n");
    return 0;
}

int px_sem_unlock(sem_t* sem){
    printf("px_sem_unlock: trying to unlock...\n");
    if(sem_post(sem) == -1){
	perror("px_sem_unlock"); 
	return(-1);
    }
    printf("px_sem_unlock: sem unlocked\n");
    return 0;
}

int px_read_shm(char* dest, int fd){
    char* data = (char*) mmap(NULL,SHM_SIZE,PROT_READ|PROT_WRITE,
		    MAP_SHARED,fd,0); 
    if(data == MAP_FAILED){
	perror("mmap");
	return -1;
    }
    printf("px_read_shm:reading from shm...\n");
    memcpy(dest, data,SHM_SIZE);
    if(munmap(data, SHM_SIZE) == -1){
	perror("munmap");
	return -1;
    }
    return 0;
}
int px_write_shm(char* data, int fd){
    char* shmp = (char*)mmap(NULL,SHM_SIZE,PROT_READ|PROT_WRITE,
		    MAP_SHARED,fd,0); 
    if( shmp == MAP_FAILED){
	perror("mmap");
	return -1;
    }
    printf("px_write_shm:writing to shm...\n");
    strncpy(shmp,data,SHM_SIZE);
    //memcpy(shmp, data,SHM_SIZE);
    if(munmap(shmp, SHM_SIZE) == -1){
	perror("munmap");
	return -1;
    }
    return 0;

}



















