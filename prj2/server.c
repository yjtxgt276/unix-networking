#include "server.h"
volatile sig_atomic_t got_usr1 = 1;
int fifo1_r,fifo1_w,fifo2_r,fifo2_w, ctop[2], ptoc[2];

int main(int argc, char** argv){
/**SERVER is exec'd by the child who has setup ipc in advance*/
/**vars*********************/
    MESG mesg;
    int mode = 0;
    int pipe_mode_r = atoi(argv[1]);
    PIPE_C_R = atoi(argv[2]);
    PIPE_C_W = atoi(argv[3]);
    FIFO_C_R = atoi(argv[4]);
    FIFO_C_W = atoi(argv[5]);
    printf("dbg sv.c");
    
    printf("dbg sv.c mode: %d\n",mode);
/**setup signal handling*/
    struct sigaction server_sa, old_sa;
    server_sa.sa_handler = server_handler;
    server_sa.sa_flags = 0;
    sigset_t zeromask;
    sigemptyset(&server_sa.sa_mask);
    sigemptyset(&zeromask);
    sigaddset(&server_sa.sa_mask,SIGUSR1);
    if( -1 == sigaction(SIGUSR1,&server_sa,NULL) ){
	perror("SERVER:sigaction");
	return 1;
    }
    /////////////////for dbg/////////////
    int i = 0;
    ///////////////////for dbg//////////////
    while(1){
/**suspend the server**/
	sigprocmask(SIG_BLOCK,&server_sa.sa_mask,&old_sa.sa_mask);
	printf("dbg sv.c while(%d)\n",i);
	while(got_usr1==0)
	    sigsuspend(&zeromask);
	got_usr1 = 0;
/**read the message from ipc*/
	/**read the mode non-blocking*/
	int flags = fcntl(pipe_mode_r,F_GETFL,0);
	fcntl(pipe_mode_r,F_SETFL,flags|O_NONBLOCK);
	read(pipe_mode_r,&mode,sizeof(int)); // TODO:dbg only
	fprintf(stderr,"dbg sv.c mode: %d\n",mode);
	child_get_mesg(&mesg, mode);
    perror("dbg s.c get_mesg");
/**process the message to handle file option*/
	child_handle_mesg(&mesg, mode);
    perror("dbg s.c handle_mesg");
/**write the result back to the ipc*/
	child_send_mesg(&mesg,mode);
    perror("dbg s.c send mesg");
/**signal client and goto sleep*/
	kill(getppid(),SIGUSR1);
    //perror("dbg s.c 4");
	sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
	i++;
    }
    perror("dbg s.c 5");
    return 0;
}
