#include "client.h"

volatile sig_atomic_t got_usr1 = 0;
int main(int argc, char** argv){
    int pid = 0;
    int ppid, cpid; // pid for parent and child
    int sv;
    FILE* fp;
    char input[MAX_LEN];//, cmd[CMD_LEN], fname[FNAME_LEN];
    char *cmd, *fname;
    struct sigaction client_sa, old_sa;
    
    //setup sig handler
    client_sa.sa_handler = client_handler;
    client_sa.sa_flags = 0;
    sigset_t zeromask;
    sigemptyset(&client_sa.sa_mask);
    sigemptyset(&zeromask);
    sigaddset(&client_sa.sa_mask,SIGUSR1);
    if(-1 == sigaction(SIGUSR1, &client_sa,NULL))
	perror("CLIENT: sigaction");

    // fork 
    if((pid=fork()) == -1){	//  fork err
	perror("fork");
    }
    else if(pid == 0){	//  child
	while(got_usr1 == 0)	// go to sleep
	    sigsuspend(&zeromask);
	got_usr1 = 0;
	printf("****CALLING SERVER...\n");
        // wake up, exec server
        if( -1 == execl("server.exe","server.exe",NULL) )
	    perror("exec server");
    }
    else{   // parent
	while(1){
	/*get user input and check it*/
	    sigprocmask(SIG_BLOCK,&client_sa.sa_mask, &old_sa.sa_mask);
	    printf("****CLIENT: Please enter: [command] [filename]\n"
		"****CLIENT: Commands are: [read], [delete]\n"
		"****CLIENT: Or type [exit] to exit\n");
	    fgets(input,MAX_LEN, stdin);
	    if( (cmd=strtok_r(input, " \n", &fname)) == NULL)
		printf("****CLIENT: INVALID COMMAND\n");
	    fname = strtok_r(fname," \n",&fname);
	    if(strcmp("read",cmd)!=0 && strcmp("delete",cmd)!=0 
		&& strcmp("exit",cmd)!=0){  // invalid command
		printf("****CLIENT: INVALID COMMAND\n");
		continue;
	    }
	    else if(strcmp("exit",cmd)==0){ //	exit command
		printf("****CLIENT: EXITING...\n");
		kill(0, SIGINT);    // clean up 
		exit(0);
	    }
	    else{//valid command, write request to the shared file signal server
		fp = fopen("ipc_file.o","w");
		fprintf(fp,"%s,%s",cmd,fname);
		fclose(fp);
		kill(pid,SIGUSR1); // signal server
	    }
	    while(got_usr1 == 0)	// go to sleep
	        sigsuspend(&zeromask);
	    got_usr1 = 0;
	    sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
	}
    }
    return 0;
}

static void client_handler(int sig){
   got_usr1 = 1; 
   return ;
}
