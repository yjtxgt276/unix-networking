#ifndef CLIENT_UTIL_H
#define CLIENT_UTIL_H
#include "client_ipc.h"
#define FIRST 0
/**client_util.h*/
extern volatile sig_atomic_t got_usr1;
void parent_handler(int sig);
int parent_valid_input(char* input, char* cmd, char* arg, int *round);
int parent_pass_mesg(MESG* mesg_snd, int mode, char* input);
int parent_get_mesg(MESG* mesg_rcv, int mode);
int parent_display_mesg(MESG*);
void parent_usage();






#endif
