#ifndef CLIENT_UTIL_H
#define CLIENT_UTIL_H

#define FIRST 0;

volatile sig_atomic_t got_usr1 = 0;
static void client_handler(int sig);
int valid_input(char* input, COMMAND*, int state);
int client_cmd(COMMAND*);
int get_mesg(MESG*);
int display_mesg(MESG*);






#endif
