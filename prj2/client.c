#include "client.h"

volatile sig_atomic_t got_usr1 ;
int ptoc[2], ctop[2];
int fifo1_r,fifo1_w,fifo2_r,fifo2_w;
int mode_fd[2];

int main(int argc, char** argv){
/**vars*/
    int round = FIRST;
    int pid = 0, sv, mode = 0, old_mode;
    char input[MAX_LEN], cmd[CMD_LEN], arg[FNAME_LEN]; 
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
/**create one pipe for sending ipc mode**/
    pipe(mode_fd);  //	fd 3,4 for sending mode p -> c
    printf("dbg c.c mode_fd: %d %d\n", mode_fd[0], mode_fd[1]);
/**create IPCs for p <-> c*/
    parent_pipes_creat(ptoc,ctop); //	fd 5, 6 for pipe p <-> c, ci.c
    parent_fifos_creat(FIFO1, FIFO2);	// fd 7,8 for fifo p <-> c, ci.c
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
	perror("dbg CHILD FIFOW");
	FIFO_C_R = open(FIFO2,O_RDONLY,0);
	perror("dbg CHILD FIFOR");
	sprintf(server_arg[1],"%d",PIPE_C_R);
	sprintf(server_arg[2],"%d",PIPE_C_W);
	sprintf(server_arg[3],"%d",FIFO_C_R);
	sprintf(server_arg[4],"%d",FIFO_C_W);
	sprintf(server_arg[5],"%d",mode);//TODO
	sprintf(server_arg[6],"%d",mode);//TODO
	fprintf(stderr,"dbg cl.c mode: %d\n",mode); // for dbg
/** go to sleep */
	while(got_usr1 == 0)
	    sigsuspend(&zeromask);	
	got_usr1 = 0;
/**wake up */
	perror("CHILD:********CALLING SERVER...");
	////////
/**execute server program*/
	if( -1 == execl("server.exe","server.exe", server_arg[0],server_arg[1],
	    server_arg[2],server_arg[3],server_arg[4],NULL) )
	    perror("CHILD:exec server");
    }
    else{
/**parent, client*/
		parent_setup_ipc(cmd,arg,mode);	// ci.c
	    perror("dbg cl.c parent_setup_ipc");
	while(1){
/**display using msg*/
	    sigprocmask(SIG_BLOCK,&client_sa.sa_mask, &old_sa.sa_mask);	
	    parent_usage(); // cu.c
/**get user input and check*/
	    //fgets(input,MAX_LEN,stdin);
	    if( !parent_valid_input(input,cmd,arg,&round) )    
		continue;
/**handle the command, either pass it to the server or exit*/
	    parent_send_mode(cmd,arg,&mode);
	    perror("dbg cl.c parent_send_mode");
	    //if(round == FIRST)
	//	parent_setup_ipc(cmd,arg,mode);	// ci.c
	   // perror("dbg cl.c parent_setup_ipc");
	    parent_pass_mesg(&mesg_snd,mode_fd[1],mode, input,round,pid);//cu.c
	    perror("dbg cl.c parent_pass_mesg");
/**got to sleep*/
	    while(0 == got_usr1)
		sigsuspend(&zeromask);
	    got_usr1 = 0;
	    sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
	    parent_get_mesg(&mesg_rcv, mode);//cu.c
	    perror("dbg cl.c parent_get_mesg");
	    parent_display_mesg(&mesg_rcv);//cu.c
	    perror("dbg cl.c parent_display_mesg");
	}
    }
    return 0;
}







