#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#define MAX_PORT 1024
typedef enum {
     PORT_ERROR = -1,
    PORT_OPEN = 0,
    PORT_CLOSED,
    PORT_FILTERED
   
} PortStatus;

typedef struct Port {
    int port;
    PortStatus status;
} Port_var;

typedef struct {
    char ip[INET_ADDRSTRLEN];
} Ip_var;

typedef struct {
    char hostname[254];
    Ip_var *ip_addrs;       
    int ip_count;
    Port_var *ports;
    int port_count;
} Target;


#endif
