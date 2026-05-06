#ifndef CLEANUP_H
#define CLEANUP_H
 
#include "common.h"
typedef struct {
    int *ports;
    int count;
} PortRange;
PortRange get_ports(int , char **);
int find_flag(int , char **, const char *);
void init_ports(Target*, PortRange);
void cleanup(Target*,int);
#endif
