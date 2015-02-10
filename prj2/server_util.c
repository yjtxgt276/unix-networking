#include "server_util.h"

void server_handler(int sig){	// done
    got_usr1 = 1;
    return;
}

int child_get_mesg(MESG* mesg, int mode){
    memset(mesg,0,sizeof(MESG));
    perror("dbg su.c reading mesg");
    SVMESG svmesg;
    unsigned poprio = 4;
    switch(mode){
	case 1:	//  pipe done
	   read(PIPE_C_R,&(mesg->mesg_len),sizeof(int));
	   read(PIPE_C_R,&(mesg->mesg_type),sizeof(int));
	   read(PIPE_C_R,mesg->mesg_data,MAX_BUF);
	   break;
	case 2:	// fifo
    perror("dbg su.c reading fifo");
	   read(FIFO_C_R,&(mesg->mesg_len),sizeof(int));
	   perror("dbg su.c read fifo");
	   read(FIFO_C_R,&(mesg->mesg_type),sizeof(int));
	   read(FIFO_C_R,mesg->mesg_data,MAX_BUF);
	   break;
	case 3: //svmq
	   msgrcv(svmqid,&svmesg,sizeof(MESG),3,0);
	   memcpy(mesg,&(svmesg.mesg),sizeof(MESG));
    perror("dbg su.c reading svmq");
	   break;
	case 4:	//pomq
	   mq_receive(pomqid_c,(char*)mesg,sizeof(MESG),NULL);
	   printf("dbg su.c buf size: %d\n",sizeof(MESG));
	   perror("dbg su.c mq_receive");
	   break;
	default:;
    }
	   //for test/////////////////////////////
	   fprintf(stderr, "dbg su.c mesg_len: %d\n", mesg->mesg_len);
	   fprintf(stderr, "dbg su.c mesg_type: %d\n", mesg->mesg_type);
	   fprintf(stderr, "dbg su.c mesg_data: %s\n", mesg->mesg_data);
	   //////////////////////////////////////////
    return 0;
}

int child_send_mesg(MESG* mesg, int mode){
    SVMESG svmesg;
    switch(mode){
	case 1:	//  pipe done
	   write(PIPE_C_W,mesg,sizeof(MESG));
	   break;
	case 2:	// fifo
	   write(FIFO_C_W,mesg,sizeof(MESG));
	   break;
	case 3: //svmq
	   svmesg.mytype = 3;
	   memcpy(&(svmesg.mesg),mesg,sizeof(MESG));
	   msgsnd(svmqid,&svmesg,sizeof(MESG),0);
	   break;
	case 4:	//pomq
	   mq_send(pomqid_p,(char*)mesg,sizeof(MESG),0);
	   break;
	default:;
    }
    return 0;
}

int child_handle_mesg(MESG* mesg, int mode){ // done
/**get the command and filename*/
    char cmd[CMD_LEN],fname[FNAME_LEN], *token, input[MAX_BUF];
    memset(cmd,0,CMD_LEN);
    memset(fname,0,FNAME_LEN);
    fprintf(stderr,"dbg su.c cmd, fname: %s %s\n",cmd,fname); 
    strncpy(input,mesg->mesg_data,MAX_BUF);
    fprintf(stderr,"dbg su.c input: %s \n",input); 
    if( NULL == (token = strtok(input," \n"))){
	perror("SERVER: empty cmd"); 
	return 1;
    }
    strcpy(cmd,token);
    if( NULL == ( token = strtok(NULL," \n"))){
	perror("SERVER: empty arg"); 
	fname == NULL;
	//return 1;
    }else
	strcpy(fname,token);
    ///////////////////for dbg //////////////////
    fprintf(stderr,"dbg su.c : %s %s\n",cmd,fname); 
/**read the file content into mesg_data*/
    if( strcmp("read",cmd) == 0){
	child_read_file(mesg,fname) ;
    }
/**delete the file*/
    else if(strcmp("delete",cmd) == 0 ){
	if( remove(fname) == -1){
	    perror("SERVER: delete file");
	    strcpy(mesg->mesg_data,"the server couldn't delete the file\n");
	}
	else{
	    strcpy(mesg->mesg_data,"the server deleted the file succesfully\n");	
	}
    }
    else if(strcmp("switch",cmd) == 0){
//	*mode = mesg->mesg_type; 
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
	strcpy(mesg->mesg_data,"the server couldn't open the file\n");
	return 1;
    }
    int i = 0;
    while(( c = fgetc(fp)) != EOF){
	 if( i == MAX_BUF){
	    perror("SERVER: file too large");
	    strcpy(mesg->mesg_data,"file too large\n");
	    //prbly need to clean first
	    return 1;
	 }
	 (mesg->mesg_data)[i] = c;
	 i++;
    }
    fclose(fp);
    return 0;
}































