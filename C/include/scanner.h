
#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"
#include <sys/socket.h>
#include <netinet/in.h>


PortStatus scan_port(const char *ip, int port);

#endif