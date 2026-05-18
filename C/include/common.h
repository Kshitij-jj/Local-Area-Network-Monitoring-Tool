#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX_PORT     1024
#define MAX_HOSTNAME 254

typedef enum {
    PORT_ERROR   = -1,
    PORT_OPEN    = 0,
    PORT_CLOSED,
    PORT_FILTERED
} PortStatus;

typedef struct {
    int       port;
    PortStatus status;
} Port_var;

typedef struct {
    char      ip[INET_ADDRSTRLEN];
    Port_var *ports;
    int       port_count;
} Ip_var;

typedef struct {
    char    hostname[MAX_HOSTNAME];
    Ip_var *ip_addrs;
    int     ip_count;
} Target;

#endif
