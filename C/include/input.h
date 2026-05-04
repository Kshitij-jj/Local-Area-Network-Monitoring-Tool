#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include <netdb.h>

Target* get_targets(int , char** , int* );
Ip_var* get_ip(const char*, int *); 

#endif
