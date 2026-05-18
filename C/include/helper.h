#ifndef HELPER_H
#define HELPER_H

#include "common.h"

typedef struct {
    int *ports;
    int  count;
} PortRange;

int      find_flag(int, char **, const char *);
PortRange get_ports(int, char **);
void     init_ports(Ip_var *, PortRange);
void     cleanup(Target *, int);

#endif