#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAX_PORT 1024
typedef struct Port {
    int port;
    int status;
} Port_var;
typedef struct Ip{
    char ip_addr[16];
     Port_var *ports;
} Ip_var;


#endif