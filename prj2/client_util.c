#include "client_util.h"

static void client_handler(int sig){
    got_usr1 = 1;
    return ;    
}
int valid_input(char* input, COMMAND* command, int round){
    char str[MAX_LEN];
    command->cmd = strtok_r(input, " \n", &(command->arg) ); 
    command->arg = strtok_r(command->arg," \n", &(command->arg) );
    if( round == FIRST){
	if( strcmp("switch",command->cmd) && strcmp("exit",command->cmd)){
/** command for 1st round must be switch or exit*/
	    printf("********CLIENT: The please choose an IPC mode\n"
		    "********CLIENT: Or type <exit> to exit");
	    return 0;
	}
    }
    else{
	if( strcmp("read",command->cmd) && strcmp("delete",command->cmd)
	&& strcmp("exit",command->cmd) && strcmp("switch",command->cmd) ){  
/**command for other rounds*/
	    printf("****CLIENT: Invalid command\n");
	    return 0;
	}	
    }
/**check switch command*/
    if( 0==strcmp("switch",command->cmd) ){
	if( strcmp("pipe",command->arg) && strcmp("fifo",command->arg)
	    && strcmp("svmq",command->cmd) && strcmp("pomq", command->cmd) ){
/**invalid ipc mode*/
	    printf("****CLIENT: Invalid IPC mode\n");
	    return 0;
	} 
    }
    return 1;
}
int client_cmd(COMMAND* command, int pid){
 

    kill(pid,SIGUSR1);
    return 0;
}
int get_mesg(MESG*){

}
int display_mesg(MESG*){

}

int display_help(){

}
