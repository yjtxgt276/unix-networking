#include "server.h"
volatile sig_atomic_t got_usr1 = 1;

int main(int argc, char** argv){
/**SERVER is exec'd by the child who has setup ipc in advance*/
/**vars*********************/
    MESG mesg;
    //////////for dbg /////////////////
    int mode = 1;// = atoi(argv[1]);
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
    while(1){
/**suspend the server**/
	sigprocmask(SIG_BLOCK,&server_sa.sa_mask,&old_sa.sa_mask);
	while(got_usr1==0)
	    sigsuspend(&zeromask);
	got_usr1 = 0;
/**read the message from ipc*/
	child_get_mesg(&mesg, mode);


/**process the message to handle file option*/
	child_handle_mesg(&mesg, &mode);
    //perror("dbg s.c 2");


/**write the result back to the ipc*/
	child_send_mesg(&mesg,mode);
    //perror("dbg s.c 3");


/**signal client and goto sleep*/
	kill(getppid(),SIGUSR1);
    //perror("dbg s.c 4");
	sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
    }
    perror("dbg s.c 5");
    return 0;
}
