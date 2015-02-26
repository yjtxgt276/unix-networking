#include "server.h"
volatile sig_atomic_t got_usr1 = 1;

int main(){
    char str[MAX_LEN];
    char *cmd;
    char *fname;
    FILE* fp; 
    struct sigaction server_sa, old_sa;

    //set up sig handler    
    server_sa.sa_handler = server_handler;
    server_sa.sa_flags = 0;
    sigset_t zeromask;
    sigemptyset(&server_sa.sa_mask);
    sigemptyset(&zeromask);
    sigaddset(&server_sa.sa_mask,SIGUSR1);
    if(-1 == sigaction(SIGUSR1, &server_sa, NULL))
	perror("SERVER: sigaction");

    //get command from file
    while(1){
	sigprocmask(SIG_BLOCK, &server_sa.sa_mask, &old_sa.sa_mask);

	//suspend server
	while(got_usr1 == 0)
	    sigsuspend(&zeromask);
	got_usr1 = 0;
	fp = fopen("ipc_file.o","r");
	fscanf(fp," %s",str);
	fclose(fp);
	cmd = strtok_r(str,", ",&fname);
	fname = strtok_r(fname," ,",&fname);
        printf("\tSERVER: THE REQUEST IS: %s \n",cmd);
	if(strcmp(cmd,"read") == 0){	// read file
	    read_file(fname);
	}
	if(strcmp(cmd,"delete") == 0){
	    if( remove(fname) == -1){
		perror("\tSERVER: removing file");
	    }
	}
        kill(getppid(),SIGUSR1);
	sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
    }

    return 0;
}

static void server_handler(int sig){
    got_usr1 = 1;
    return ;
}

void read_file(char *filename){
    FILE *fp; 
    char c;
    if(( fp= fopen(filename, "r") ) == NULL) {
	perror("\tSERVER: opening file");
	return;
    }
    printf("************ [%s] ***************\n",filename);
    while( (c = fgetc(fp))!= EOF){
	putchar(c);
    }
    printf("************ [%s] ***************\n",filename);
<<<<<<< HEAD
=======
    //free(line);
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
    return;
}
