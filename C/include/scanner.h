
#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"


typedef enum {
     PORT_ERROR = -1,
    PORT_OPEN = 0,
    PORT_CLOSED,
    PORT_FILTERED
   
} PortStatus;
PortStatus scan_port(const char *ip, int port);

#endif