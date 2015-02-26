#include "prj3_util.h"
int valid_cmd(char* str){
// for client
    char *token,input[MAX_LEN], cmd[CMD_LEN]; 
    strncpy(input,str,MAX_LEN);
    if(NULL == (token = strtok(input," \n"))){
	printf("valid_cmd:empty cmd\n"); 
	return -1;
    }
    else
	strcpy(cmd, token);
    if( 0==strcmp("read",cmd) ){}
    else if( 0==strcmp("delete",cmd) ){}
    else if( 0==strcmp("switch",cmd) ){
	//TODO 
	//sv_cleanup();
	kill(0,SIGINT);
	exit(SW_PX);    
    }
    else if( 0==strcmp("exit",cmd) ){
	printf("exiting..."); 
	//TODO
	//sv_cleanup();
	kill(0,SIGINT);
	exit(ALL_EXIT);    
    }
    else{
	printf("valid_cmd: invalid command\n"); 
	return -1;
    }
    return 0;
}

int display(char* data){
    printf("Display: result from server:\n");
    printf("%s\n",data);
    return 0;
}

int process_cmd(char* str, char* rslt){
//for server
    char *token,input[MAX_LEN], cmd[CMD_LEN],fname[FN_LEN]; 
    strncpy(input,str,MAX_LEN);
    if(NULL == (token = strtok(input," \n"))){
	printf("Process_cmd:empty cmd\n"); 
	return -1;
    }
    else
	strcpy(cmd, token);
    if(NULL == (token = strtok(NULL, " \n"))){
	printf("Process_cmd:empty file name\n"); 
	strcpy(rslt, "from server: please input a file name\n");
	return -1;
    }
    else
	strcpy(fname, token);
    if( 0==strcmp("read",cmd) ){
	printf("Process_cmd: reading file content...\n");
	read_file(rslt,fname);
    }
    else if( 0==strcmp("delete",cmd) ){
	printf("Process_cmd: deleting file ...\n");
	if(remove(fname)==-1){
	    perror("Server:delete file");	
	    strcpy(rslt, "from server: couldnot delete the file\n");
	}
	else

	    strcpy(rslt,"from server: file deleted successfully\n");
    }
    else{
	printf("Process_cmd: invalid command\n"); 
	return -1;
    }
    return 0;
}

int read_file(char* dest, char* fname){
    FILE* fp;
    char c;
    if(NULL == (fp = fopen(fname,"r"))){
	perror("server: open file"); 
	strcpy(dest,"from server: couldnot open the file\n");
	return -1;
    }
    int i =0;
    while(EOF != (c=fgetc(fp))){
	if(i == SHM_SIZE){
	    printf("server: file too large\n");
	    strcpy(dest, "from server: file too large\n");
	    return -1;
	} 
	dest[i] = c;
	i++;
    }
    fclose(fp);
    return 0;
}


