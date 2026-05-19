#ifndef INPUT_H
#define INPUT_H
#define DEFAULT_FORMAT 'h'
#include "common.h"

char get_format(int, char**);
Target* get_targets(int , char** , int* );
Ip_var* get_ip(const char*, int* ); 

#endif
