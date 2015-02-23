/**client_ipc.h**/
#ifndef IPC_UTIL_H
#define IPC_UTIL_H
#include "prj2.h"
extern int ptoc[2], ctop[2];
extern int fifo1_r,fifo1_w,fifo2_r,fifo2_w;
extern int mode_fd[2];
extern int svmqid,pomqid_p,pomqid_c;
#define PIPE_P_W ptoc[1]
#define PIPE_P_R ctop[0]
#define PIPE_C_W ctop[1]
#define PIPE_C_R ptoc[0]
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FIFO_P_R fifo1_r
#define FIFO_P_W fifo2_w
#define FIFO_C_R fifo2_r
#define FIFO_C_W fifo1_w
#define PIPE_MODE_W mode_fd[1]
#define PIPE_MODE_R mode_fd[0]

int parent_fifos_creat(char*,char*);
int parent_pipes_creat(int*,int*);
int parent_setup_ipc(int* svmqid);
int parent_send_mode(char* cmd, char* arg, int* mode);







































#endif
