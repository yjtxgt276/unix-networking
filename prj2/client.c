/**include headers*/
#include "client.h"

extern volatile sig_atomic_t got_usr1 ; // defined in header
int main(int argc, char** argv){
/**vars*/
    int round = FIRST;
    int pid = 0, sv;
    FILE* fp; // not needed at client side
    char input[MAX_LEN];
    struct sigaction client_sa, old_sa;
    COMMAND command;
    MESG mesg;
/**setup signal handlers*/
    client_sa.sa_handler = client_handler;
    client_sa.sa_flags = 0;
    sigset_t zeromask;
    sigemptyset(&client_sa.sa_mask);
    sigemptyset(&zeromask);
    sigaddset(&client_sa.sa_mask,SIGUSR1);
    if(-1 == sigaction(SIGUSR1, &client_sa, NULL))
	perror("CLIENT: sigaction()");
/** fork the server prcs*/
    if( -1 == ( pid = fork() ) )
	perror("CLIENT: fork()");
    else if( 0 == pid){ // child, server
	while(got_usr1 == 0)
	    sigsuspend(&zeromask);	
	got_usr1 = 0;
	printf("********CALLING SERVER...\n");
	if( -1 == execl("server.exe","server.exe", NULL) )
	    perror("exec server");
    }
    else{
/**parent, client, infi loop*/
	while(1){
/**display using msg*/
	    sigpromask(SIG_BLOCK,&client_sa.sa_mask, &old_sa.sa_mask);	
	    printf("********CLIENT: please enter <command> <filename>\n"
		"********CLIENT: commands are <switch>, <read>, <delete>\n "
		"********CLIENT: or type <exit> to exit\n");
/**get user input and check*/
/**first input must be switch*/
/**follow-up inputs can be other than switch*/
	    fgets(input,MAX_LEN,stdin);
	    if( !valid_input(input,&command,round) )    
		continue;
/**handle the command, either pass it to the server or exit*/
	    client_cmd(&command);
/**got to sleep*/
	    while(0==got_usr1)
		sigsuspend(&zeromask);
	    got_usr1 = 0;
	    sigprocmask(SIG_SETMASK,&old_sa.sa_mask,NULL);
	    get_mesg(&mesg);
	    display_mesg(&mesg);
	}
    }
    return 0;
}








