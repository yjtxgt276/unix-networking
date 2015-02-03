#ifndef CLIENT_UTIL_H
#define CLIENT_UTIL_H
#include "prj2.h"
#define FIRST 0;
//#define PIPE_P_W ptoc[1] /**MACROs about pipes are defined in prj2.h*/
//#define PIPE_P_R ctop[0]
//#define PIPE_C_W ctop[1]
//#define PIPE_C_R ptoc[0]

volatile sig_atomic_t got_usr1 = 0;
//int ptoc[2], ctop[2]; // should def in client.c
static void client_handler(int sig);
int valid_input(char* input, COMMAND*, int state);
int client_cmd(COMMAND*);
int get_mesg(MESG*);
int display_mesg(MESG*);






#endif
