/**include headers*/
#include "client.h"

volatile sig_atomic_t got_usr1 ; // defined in header
int ptoc[2], ctop[2];
int fifo1_r,fifo1_w,fifo2_r,fifo2_w;

int main(int argc, char** argv){
/**vars*/
    int round = FIRST;
    int pid = 0, sv, mode = 0, old_mode;
    FILE* fp; // not needed at client side
    char input[MAX_LEN], cmd[CMD_LEN], arg[FNAME_LEN]; //use mesg_rcv
    struct sigaction client_sa, old_sa;
    MESG mesg_snd, mesg_rcv;
    char child_arg[CMD_LEN];
/**setup signal handlers*/
    client_sa.sa_handler = parent_handler;
    client_sa.sa_flags = 0;
    sigset_t zeromask;
    sigemptyset(&client_sa.sa_mask);
    sigemptyset(&zeromask);
    sigaddset(&client_sa.sa_mask,SIGUSR1);
    if(-1 == sigaction(SIGUSR1, &client_sa, NULL))
	perror("sigaction()");
/**create IPCs for p <-> c*/
    pipes_creat(ptoc,ctop);
    fifos_creat("fifo1.o","fifo2.o");
/**create one pipe to send the very first ipc mode**/
    int mode_fd[2];
    pipe(mode_fd);
/** fork the server prcs*/
    if( -1 == ( pid = fork() ) ){
	perror("PARENT: fork()");
	return 0;
    }
/** child, server*/
    else if( 0 == pid){ 
	while(got_usr1 == 0)
	    sigsuspend(&zeromask);	
	got_usr1 = 0;
/** get the first ipc mode for the server*/
	read(mode_fd[0],&mode,sizeof(int));
	printf("dbg cl.c mode: %d\n",mode);
	char server_arg[10];
	sprintf(server_arg,"%d",mode);
/**wake up, setup ipc */
	printf("********CALLING SERVER...\n");
	child_setup_ipc(mode); // TODO: set ipc inside the server
	////////
/**execute server program*/
	if( -1 == execl("server.exe","server.exe", server_arg,NULL) )
	    perror("CHILD:exec server");
    }
    else{
/**parent, client*/
	while(1){
/**display using msg*/
	    sigprocmask(SIG_BLOCK,&client_sa.sa_mask, &old_sa.sa_mask);	
	    parent_usage();
/**get user input and check*/
	    //fgets(input,MAX_LEN,stdin);
	    if( !parent_valid_input(input,cmd,arg,&round) )    
		continue;
/**handle the command, either pass it to the server or exit*/
	    parent_setup_ipc(cmd,arg,&mode);
	    parent_pass_mesg(&mesg_snd,mode_fd[1],mode, input,round,pid);
/**got to sleep*/
	    while(0 == got_usr1)
		sigsuspend(&zeromask);
	    got_usr1 = 0;
	    sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
	    parent_get_mesg(&mesg_rcv, mode);
	    parent_display_mesg(&mesg_rcv);
	}
    }
    return 0;
}







