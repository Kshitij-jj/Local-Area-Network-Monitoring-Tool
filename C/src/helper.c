#include "helper.h"
void cleanup(Target *targets, int count){
    int i;
    for(i=0; i<count; i++){
        free(targets[i].ip_addrs);
        free(targets[i].ports);
        
    }
    free(targets);
}
