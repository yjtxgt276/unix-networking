<<<<<<< HEAD
=======
/**server_util.h*/
>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H
#include "prj2.h"
#include "server_ipc.h"
extern volatile sig_atomic_t got_usr1;
void server_handler(int sig);
int child_get_mesg(MESG*, int mode);
int child_send_mesg(MESG*, int mode);
int child_handle_mesg(MESG*, int mode);
int child_read_file(MESG* mesg, char* fname);



#endif
