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
    else if( 0==strcmp("switch",cmd) ){}
    else if( 0==strcmp("exit",cmd) )
	return ALL_EXIT; 
    else{
	printf("valid_cmd: invalid command\n"); 
	return -1;
    }
    return 0;
}

int display(char* data){
<<<<<<< HEAD
    printf("Display: result from server:\n");
=======
    printf("sv_display: result from server:\n");
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
    printf("%s\n",data);
    return 0;
}

int process_cmd(char* str, char* rslt){
//for server
    char *token,input[MAX_LEN], cmd[CMD_LEN],fname[FN_LEN]; 
    strncpy(input,str,MAX_LEN);
    if(NULL == (token = strtok(input," \n"))){
<<<<<<< HEAD
	printf("Process_cmd:empty cmd\n"); 
=======
	printf("sv_process_cmd:empty cmd\n"); 
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
	return -1;
    }
    else
	strcpy(cmd, token);
    if(NULL == (token = strtok(NULL, " \n"))){
<<<<<<< HEAD
	printf("Process_cmd:empty file name\n"); 
=======
	printf("sv_process_cmd:empty file name\n"); 
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
	strcpy(rslt, "from server: please input a file name\n");
	return -1;
    }
    else
	strcpy(fname, token);
    if( 0==strcmp("read",cmd) ){
<<<<<<< HEAD
	printf("Process_cmd: reading file content...\n");
	read_file(rslt,fname);
    }
    else if( 0==strcmp("delete",cmd) ){
	printf("Process_cmd: deleting file ...\n");
	if(remove(fname)==-1){
	    perror("Server:delete file");	
=======
	printf("sv_process_cmd: reading file content...\n");
	read_file(rslt,fname);
    }
    else if( 0==strcmp("delete",cmd) ){
	printf("sv_process_cmd: deleting file ...\n");
	if(remove(fname)==-1){
	    perror("sv_server:delete file");	
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
	    strcpy(rslt, "from server: couldnot delete the file\n");
	}
	else

	    strcpy(rslt,"from server: file deleted successfully\n");
    }
    else{
<<<<<<< HEAD
	printf("Process_cmd: invalid command\n"); 
=======
	printf("sv_process_cmd: invalid command\n"); 
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
	return -1;
    }
    return 0;
}

int read_file(char* dest, char* fname){
    FILE* fp;
    char c;
    if(NULL == (fp = fopen(fname,"r"))){
<<<<<<< HEAD
	perror("server: open file"); 
=======
	perror("sv_server: open file"); 
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
	strcpy(dest,"from server: couldnot open the file\n");
	return -1;
    }
    int i =0;
    while(EOF != (c=fgetc(fp))){
	if(i == SHM_SIZE){
<<<<<<< HEAD
	    printf("server: file too large\n");
=======
	    printf("sv_server: file too large\n");
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
	    strcpy(dest, "from server: file too large\n");
	    return -1;
	} 
	dest[i] = c;
	i++;
    }
    fclose(fp);
    return 0;
}


