#include "server_util.h"

void server_handler(){
    got_usr1 = 1;
    return;
}

int child_get_message(MESG* mesg, int mode){
    switch(mode){
	case 1:	//  pipe done
	   read(STDIN_FILENO,mesg->mesg_len,sizeof(int));
	   read(STDIN_FILENO,mesg->mesg_type,sizeof(int));
	   read(STDIN_FILENO,mesg->mesg_data,MAX_BUF);
	   break;
	case 2:	// fifo
	   break;
	case 3: //svmq
	   break;
	case 4:	//pomq
	   break;
	default:;
    }
    return 0;
}

int child_send_message(MESG* mesg, int mode){
    switch(mode){
	case 1:	//  pipe done
	   write(STDOUT_FILENO,mesg,sizeof(MESG));
	   break;
	case 2:	// fifo
	   break;
	case 3: //svmq
	   break;
	case 4:	//pomq
	   break;
	default:;
    }
    return 0;
}

int child_handle_mesg(MESG* mesg){ // done
/**get the command and filename*/
    char cmd[CMD_LEN],fname[FNAME_LEN], *token;
    token = strtok(mesg->mesg_data," \n"); 
    strcpy(cmd,token);
    token = strtok(NULL," \n");
    strcpy(fname,token);
    
/**read the file content into mesg_data*/
    if( strcmp("read",cmd) == 0){
	child_read_file(mesg,fname) 
    }
/**delete the file*/
    else if(strcmp("delete",cmd) == 0 ){
	if( remove(fname) == -1){
	    perror("SERVER: delete file");
	    strcpy(mesg->mesg_data,"the server couldn't delete the file");
	}
	else{
	    strcpy(mesg->mesg_data,"the server deleted the file succesfully");	
	}
    }
    else
	perror("SERVER: Bad command/filename");
    return 0;
}

int child_read_file(MESG* mesg,char *fname){   // done
    FILE* fp;
    char c;
    if( NULL == (fp=fopen(fname,"r")) ){
	perror("SERVER: Open file.");
	strcpy(mesg->mesg_data,"the server couldn't open the file");
	return 1;
    }
    int i = 0;
    while(( c = fgetc(fp)) != EOF){
	 if( i == MAX_BUF){
	    perror("SERVER: file too large");
	    strcpy(mesg->mesg_data,"file too large");//prbly need to clean first
	    return 1;
	 }
	 (mesg->mesg_data)[i] = c;
	 i++;
    }
    return 0;
}































