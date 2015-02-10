#include "client_util.h"

void parent_handler(int sig){	//done
    got_usr1 = 1;
    return ;    
}

int parent_valid_input(char* input_global, char* cmd,char* arg, int* round){
	//done
    fgets(input_global,MAX_LEN,stdin);
    char *token, input[MAX_LEN];
    strncpy(input,input_global,MAX_LEN);
    if( NULL == (token = strtok(input, " \n")) ){
	perror("PARENT: strtok cmd"); 
    }
    strcpy(cmd,token);
    if( *round == FIRST){
/** command for 1st round must be switch or exit*/
	if( 0!=strcmp("switch",cmd) && 0!=strcmp("exit",cmd)){
	    printf("********CLIENT: Please choose an IPC mode\n"
			    "********CLIENT: Or type <exit> to exit\n");
	    return 0;
	}
	(*round)++;
	printf("dbg cu.c %d\n",*round);
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
	if( NULL == (token = strtok(NULL," \n")) ){
	    printf("********CLIENT: No IPC mode selected\n");
	    return 0;
	}
	strcpy(arg,token);
	printf("dbg cu.c arg: %s\n",arg);
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

int parent_pass_mesg(MESG* mesg, int modepipe, 
		int mode,char* input,int round,int pid){
/**prepare the mesg*/
    mesg->mesg_len = sizeof(MESG);
    mesg->mesg_type = mode;
    if(MAX_BUF > (strlen(input)+1) )
	strncpy(mesg->mesg_data,input, strlen(input)+1);
    printf("dbg cu.c input: %s\n",input);
/**pass mesg to according to ipc mode*/
    printf("dbg cu.c write to ipc mode: %d\n",mode);
    switch(mode){
	case 1:
	    /**pipe*/	
	    printf("********CLIENT: Writing to pipe...\n");
	    write(PIPE_P_W,mesg,sizeof(MESG)); 
	    break;
	case 2:
	    /**fifo*/
	    printf("********CLIENT: Writing to fifo...\n");
	    /** write the actual mesg to ipc*/
	    if( -1 == write(FIFO_P_W,mesg,sizeof(MESG)))
		perror("PARENT: WRTmesg FIFO");	//TODO: fix bad fd
	    break;
	case 3:
	    /**svmq*/
	    printf("********CLIENT: Writing to svmq...\n");
	    /** tell the server which ipc to go*/
	    write(PIPE_P_W,&mode,sizeof(int));
	    /** write the actual mesg to ipc*/
	    break;
	case 4:
	    /**pomq*/
	    printf("********CLIENT: Writing to pomq...\n");
	    /** tell the server which ipc to go*/
	    write(PIPE_P_W,&mode,sizeof(int));
	    /** write the actual mesg to ipc*/
	    break;
	default:;
    }
    if(round != FIRST+1)
	    printf("dbg cu.c round %d mode: %d\n",round, mode);
    kill(pid,SIGUSR1); 
    return 0;
}

int parent_get_mesg(MESG *mesg, int mode){  //	done
    switch(mode){
	case 1:	// pipe
		printf("********CLIENT: Reading from pipe...\n");
		read(PIPE_P_R, &(mesg->mesg_len), sizeof(int));
		read(PIPE_P_R, &(mesg->mesg_type), sizeof(int));
		read(PIPE_P_R, &(mesg->mesg_data), MAX_BUF);
		break;
	case 2:	// fifo
		printf("********CLIENT: Reading from fifo...\n");
		read(FIFO_P_R, &(mesg->mesg_len), sizeof(int));
		read(FIFO_P_R, &(mesg->mesg_type), sizeof(int));
		read(FIFO_P_R, &(mesg->mesg_data), MAX_BUF);
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
    printf("********CLIENT: mesg_data: %s",mesg->mesg_data);
    printf("********************************************\n");
    return 0;
}

void parent_usage(){
    printf("********CLIENT: Usage********\n");
    printf("********CLIENT: <switch> <IPC>\n");
    printf("********CLIENT: <delete/read> <file>\n");
    printf("********CLIENT: <exit>\n");
}







