/**include headers*/
#include "client.h"

volatile sig_atomic_t got_usr1 ; // defined in header
int ptoc[2], ctop[2];

int main(int argc, char** argv){
/**vars*/
    int round = FIRST;
    int pid = 0, sv, mode = 0;
    FILE* fp; // not needed at client side
    char input[MAX_LEN], *cmd, *arg, buffer[sizeof(MESG)];
    struct sigaction client_sa, old_sa;
    //COMMAND command;
    MESG mesg;
/**setup signal handlers*/
    client_sa.sa_handler = client_handler;
    client_sa.sa_flags = 0;
    sigset_t zeromask;
    sigemptyset(&client_sa.sa_mask);
    sigemptyset(&zeromask);
    sigaddset(&client_sa.sa_mask,SIGUSR1);
    if(-1 == sigaction(SIGUSR1, &client_sa, NULL))
	perror("sigaction()");
/**create two pipes for p <-> c*/
    pipes_creat(ptoc,ctop);
    /** if the func above works, this block is wiped.
    if(-1 == pipe(ptoc) )
	perror("pipe parent to child");
    if(-1 == pipe(ctop) )
	perror("pipe child to parent");
   */ 
/** fork the server prcs*/
    if( -1 == ( pid = fork() ) ){
	perror("PARENT: fork()");
	return 0;
    }
    else if( 0 == pid){ // child, server
	while(got_usr1 == 0)
	    sigsuspend(&zeromask);	
	got_usr1 = 0;
/**set up ipc mode here*/
	child_setup_ipc(mode);
/**execute server program*/
	printf("********CALLING SERVER...\n");
	if( -1 == execl("server.exe","server.exe", NULL) )
	    perror("CHILD:exec server");
    }
    else{
/**parent, client*/
	while(1){
/**display using msg*/
	    sigpromask(SIG_BLOCK,&client_sa.sa_mask, &old_sa.sa_mask);	
	    printf("********CLIENT: please enter <command> <filename>\n"
		"********CLIENT: commands are <switch>, <read>, <delete>\n "
		"********CLIENT: or type <exit> to exit\n");
/**get user input and check*/
	    fgets(input,MAX_LEN,stdin);
	    if( !valid_input(input,cmd,arg,round) )    
		continue;
/**handle the command, either pass it to the server or exit*/
	    parent_setup_ipc(cmd,arg,&mode);
	    parent_pass_mesg(&mesg,pid,mode);
/**got to sleep*/
	    while(0 == got_usr1)
		sigsuspend(&zeromask);
	    got_usr1 = 0;
	    sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
	    parent_get_mesg(&mesg);
	    parent_display_mesg(&mesg);
	}
    }
    return 0;
}







