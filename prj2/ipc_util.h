#ifndef IPC_UTIL_H
#define IPC_UTIL_H
#include "prj2.h"


extern int ptoc[2], ctop[2];
#define PIPE_P_W ptoc[1]
#define PIPE_P_R ctop[0]
#define PIPE_C_W ctop[1]
#define PIPE_C_R ptoc[0]








































#endif
