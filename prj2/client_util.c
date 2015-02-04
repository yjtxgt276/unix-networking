#include "client_util.h"

void parent_handler(int sig){	//done
    got_usr1 = 1;
    return ;    
}

int parent_valid_input(char* input, char* cmd, char* arg, int* round){	//done
    //char str[MAX_LEN]; // prob not needed
    if( NULL == (cmd = strtok(input, " \n")) ){
	perror("PARENT: strtok cmd"); 
    }
    if( NULL == (arg = strtok(NULL," \n")) ){
	perror("PARENT: strtok arg");
    }
    printf("cmd: %s\targ: %s\n",cmd,arg);
    if( *round == FIRST){
/** command for 1st round must be switch or exit*/
	if( 0!=strcmp("switch",cmd) && 0!=strcmp("exit",cmd)){
	    printf("********CLIENT: The please choose an IPC mode\n"
		    "********CLIENT: Or type <exit> to exit");
	    return 0;
	}
	(*round)++;
    }
    else{
/**command for other rounds*/
	if( 0!=strcmp("read",cmd) && 0!=strcmp("delete",cmd)
	&& 0!=strcmp("exit",cmd) && 0!=strcmp("switch",cmd) ){  
	    printf("********CLIENT: Invalid command\n");
	    return 0;
	}	
    }
/**check switch command*/
    if( 0==strcmp("switch",cmd) ){
	if( 0!=strcmp("pipe",arg) && 0!=strcmp("fifo",arg)
	    && 0!=strcmp("svmq",cmd) && 0!=strcmp("pomq", cmd) ){
	    printf("********CLIENT: Invalid IPC mode\n");
	    return 0;
	} 
    }
/**exit command*/
    if(0==strcmp("exit",cmd) ){
	printf("********CLIENT: Exiting...\n");
	kill(0,SIGINT);	
	exit(0);
    }
    return 1;
}

int parent_pass_mesg(MESG* mesg, int pid, int mode,char* input){//done
	//pid prob not needed
/**prepare the mesg*/
    mesg->mesg_len = sizeof(MESG);
    mesg->mesg_type = mode;
    if(MAX_BUF >= (strlen(input)+1) )
	strncpy(mesg->mesg_data,input, strlen(input)+1);
/**pass mesg to according to ipc mode*/
    switch(mode){
	case 1:
	    /**pipe*/	
	    printf("********CLIENT: Writing to pipe...");
	    write(PIPE_P_W,mesg,sizeof(MESG)); 
	    break;
	case 2:
	    /**fifo*/
	    break;
	case 3:
	    /**svmq*/
	    break;
	case 4:
	    /**pomq*/
	    break;
	default:;
    }
    kill(pid,SIGUSR1); 
    return 0;
}

int parent_get_mesg(MESG *mesg, int mode){  //	done
    switch(mode){
	case 1:	// pipe
		printf("********CLIENT: Reading from pipe...");
		read(PIPE_P_R, &(mesg->mesg_len), sizeof(int));
		read(PIPE_P_R, &(mesg->mesg_type), sizeof(int));
		read(PIPE_P_R, &(mesg->mesg_data), sizeof(MESG)-2*sizeof(int));
		break;
	case 2:	// fifo
		break;
	case 3:	// svmq
		break;
	case 4:	// pomq
		break;
	default:
		;
    }

    return 0;
}

int parent_display_mesg(MESG* mesg){	//done

    printf("********CLIENT: Message from SERVER:********\n");
    printf("********CLIENT: mesg_len: %d\n",mesg->mesg_len);
    printf("********CLIENT: mesg_type: %d\n",mesg->mesg_type);
    printf("********CLIENT: mesg_data: %s\n",mesg->mesg_data);
    printf("********************************************\n");
    return 0;
}













