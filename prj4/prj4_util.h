#ifndef PRJ4_UTIL_H 
#define PRJ4_UTIL_H
#include "prj4.h"

int valid_cmd(char* cmd);
int display(char* data);
int process_cmd(char* str,char* dest);
int read_file(char* dest, char* fname);
void* get_in_addr(struct sockaddr* sa);



#endif



























