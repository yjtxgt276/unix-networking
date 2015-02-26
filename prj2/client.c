#include "client.h"
<<<<<<< HEAD

=======
/**client.c*/
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
volatile sig_atomic_t got_usr1 ;
int ptoc[2], ctop[2];
int fifo1_r,fifo1_w,fifo2_r,fifo2_w;
int mode_fd[2],svmqid;
int svmqid,pomqid_p,pomqid_c;

int main(int argc, char** argv){
/**vars*/
    int round = FIRST;
    int pid = 0, sv, mode = 0, old_mode;
    char input[MAX_LEN], cmd[CMD_LEN], arg[FNAME_LEN]; 
    struct sigaction client_sa, old_sa;
    MESG mesg_snd, mesg_rcv;
    memset(&mesg_rcv,0,sizeof(MESG));
    memset(&mesg_snd,0,sizeof(MESG));
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
/**create one pipe for sending ipc mode**/
    pipe(mode_fd);  
/**create IPCs for p <-> c*/
    parent_pipes_creat(ptoc,ctop); 
    parent_fifos_creat(FIFO1, FIFO2);
/** fork */
    if( -1 == ( pid = fork() ) ){
	perror("PARENT: fork()");
	return 0;
    }
/** child*/
    else if( 0 == pid){ 
/**get ipc fds for server*/
	char server_arg[10][10];	
	sprintf(server_arg[0],"%d",PIPE_MODE_R);
/** open pipes*/
	FIFO_C_W = open(FIFO1,O_WRONLY,0);
	FIFO_C_R = open(FIFO2,O_RDONLY,0);
	sprintf(server_arg[1],"%d",PIPE_C_R);
	sprintf(server_arg[2],"%d",PIPE_C_W);
	sprintf(server_arg[3],"%d",FIFO_C_R);
	sprintf(server_arg[4],"%d",FIFO_C_W);
/** go to sleep */
	while(got_usr1 == 0)
	    sigsuspend(&zeromask);	
	got_usr1 = 0;
/**wake up */
	printf("CHILD:********CALLING SERVER...");
/**execute server program*/
	if( -1 == execl("server.exe","server.exe", server_arg[0],server_arg[1],
	    server_arg[2],server_arg[3],server_arg[4],NULL) )
	    perror("CHILD:exec server");
    }
    else{
/**parent, client*/
    /**pomq*/
    struct mq_attr attr_c,attr_p;
    pomqid_p = mq_open(POMQ_P,O_RDONLY | O_CREAT, 0666, NULL);
    mq_getattr(pomqid_p,&attr_p);
    pomqid_c = mq_open(POMQ_C,O_WRONLY|O_CREAT,0666,NULL);
    mq_getattr(pomqid_c,&attr_c);
	parent_setup_ipc(&svmqid);
	while(1){
/**display using msg*/
	    sigprocmask(SIG_BLOCK,&client_sa.sa_mask, &old_sa.sa_mask);	
	    parent_usage();
/**get user input and check*/
	    if( !parent_valid_input(input,cmd,arg,&round) )    
		continue;
/**handle the command, either pass it to the server or exit*/
	    parent_send_mode(cmd,arg,&mode);
	    parent_pass_mesg(&mesg_snd,mode, input);
	    kill(pid,SIGUSR1);
/**got to sleep*/
	    while(0 == got_usr1)
		sigsuspend(&zeromask);
	    got_usr1 = 0;
	    sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
	    parent_get_mesg(&mesg_rcv, mode);
	    parent_display_mesg(&mesg_rcv);
	}
    }
    cleanup();
    return 0;
}







