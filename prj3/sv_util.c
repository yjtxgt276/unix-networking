#include "sv_util.h"

int sv_sem_init(key_t key, int nsems){
// for client
    int i, semid;
    union semun arg;
    struct semid_ds buf;
    struct sembuf sb;

    semid = semget(key,nsems,IPC_CREAT|IPC_EXCL|0666);
    if(semid>=0){   // create the sem
	sb.sem_op=1;
	arg.val=1;
	for(sb.sem_num=0;sb.sem_num<nsems;sb.sem_num++){
	    if(semop(semid,&sb,1)==-1){
		int e = errno;
		semctl(semid,0,IPC_RMID);	
		errno = e;
		return -1;
	    }	
	}	
    }else if(errno==EEXIST){	
	//exist, simply connect to it
	int ready =0;
	semid=semget(key,0,0);	
	if(semid<0)
	    return semid;
	arg.buf = &buf;
	if(!ready){
	    semctl(semid,nsems-1,IPC_STAT,0);
	    if(arg.buf->sem_otime!=0)
		ready = 1;
	    else
		return -1;
	}
	if(!ready){
	    errno = ETIME;	
	    return -1;
	}
    }else
	return semid;
    return semid;
}

int sv_sem_lock(int semid){
// for both
    struct sembuf sbop;
    sbop.sem_num=0;
    sbop.sem_op = -1;
    sbop.sem_flg = SEM_UNDO;
    printf("sv_sem_lock: trying to lock the sem\n");
    if(semop(semid,&sbop,1)==-1){
	perror("semop"); 
	return(1);
    }
    printf("sv_sem_lock: sem locked\n");
    return 0;
}

int sv_sem_unlock(int semid){
//for both
    struct sembuf sbop;
    sbop.sem_num=0;
    sbop.sem_op = 1;
    sbop.sem_flg = SEM_UNDO;
    printf("sv_sem_unlock: trying to unlock the sem\n");
    if(semop(semid,&sbop,1)==-1){
	perror("semop"); 
	return(1);
    }
    printf("sv_sem_unlock: sem unlocked\n");
    return 0;
}

int sv_valid_cmd(char* str){
// for client
    char *token,input[MAX_LEN], cmd[CMD_LEN]; 
    strncpy(input,str,MAX_LEN);
    if(NULL == (token = strtok(input," \n"))){
	printf("valid_cmd:empty cmd\n"); 
	return -1;
    }
    else
	strcpy(cmd, token);
    if( 0==strcmp("read",cmd) ){}
    else if( 0==strcmp("delete",cmd) ){}
    else if( 0==strcmp("switch",cmd) ){
	//TODO 
	//sv_cleanup();
	kill(0,SIGINT);
	exit(SW_PX);    
    }
    else if( 0==strcmp("exit",cmd) ){
	printf("exiting..."); 
	//TODO
	//sv_cleanup();
	kill(0,SIGINT);
	exit(ALL_EXIT);    
    }
    else{
	printf("valid_cmd: invalid command\n"); 
	return -1;
    }
    return 0;
}

int sv_write_shm(char *str, int shmid){
    char *data; 
    data = (char*) shmat(shmid,(void*)0,0);
    if(data==(char*)(-1)){
	perror("shmat"); 
	return (-1);
    }
    printf("sv_write_shm: writing to shm...\n");
    //strncpy(data, str, SHM_SIZE);
    memcpy(data, str,SHM_SIZE);
    if(shmdt(data)==-1){
	perror("shmdt"); 
	return (-1);
    }

    return 0;
}

int sv_read_shm(char *dest, int shmid){
    char* data; 
    if((data=shmat(shmid,(void*)0,0))==(char*)(-1)){
	perror("shmat"); 
	return (-1);
    }
    printf("sv_read_shm: reading from shm...\n");
    strncpy(dest, data, SHM_SIZE);
    if(shmdt(data)==-1){
	perror("shmdt"); 
	return (-1);
    }
    return 0;
}

int sv_display(char* data){
    printf("sv_display: result from server:\n");
    printf("%s\n",data);
    return 0;
}

int sv_process_cmd(char* str, char* rslt){
//for server
    char *token,input[MAX_LEN], cmd[CMD_LEN],fname[FN_LEN]; 
    strncpy(input,str,MAX_LEN);
    if(NULL == (token = strtok(input," \n"))){
	printf("sv_process_cmd:empty cmd\n"); 
	return -1;
    }
    else
	strcpy(cmd, token);
    if(NULL == (token = strtok(NULL, " \n"))){
	printf("sv_process_cmd:empty file name\n"); 
	strcpy(rslt, "from server: please input a file name\n");
	return -1;
    }
    else
	strcpy(fname, token);
    if( 0==strcmp("read",cmd) ){
	printf("sv_process_cmd: reading file content...\n");
	sv_read_file(rslt,fname);
    }
    else if( 0==strcmp("delete",cmd) ){
	printf("sv_process_cmd: deleting file ...\n");
	if(remove(fname)==-1){
	    perror("sv_server:delete file");	
	    strcpy(rslt, "from server: couldnot delete the file\n");
	}
	else

	    strcpy(rslt,"from server: file deleted successfully\n");
    }
    else{
	printf("sv_process_cmd: invalid command\n"); 
	return -1;
    }
    return 0;
}

int sv_read_file(char* dest, char* fname){
    FILE* fp;
    char c;
    if(NULL == (fp = fopen(fname,"r"))){
	perror("sv_server: open file"); 
	strcpy(dest,"from server: couldnot open the file\n");
	return -1;
    }
    int i =0;
    while(EOF != (c=fgetc(fp))){
	if(i == SHM_SIZE){
	    printf("sv_server: file too large\n");
	    strcpy(dest, "from server: file too large\n");
	    return -1;
	} 
	dest[i] = c;
	i++;
    }
    fclose(fp);
    return 0;
}


