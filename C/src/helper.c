#include "helper.h"
int find_flag(int argc, char *argv[], const char *flag){
    int i;
    for( i=1; i<argc; i++ ){
        if(strcmp(flag, argv[i])==0)
        return i;
    }
return -1;
}
PortRange get_ports(int p_index, char *argv[]){
    ++p_index;
    PortRange Port = {NULL, MAX_PORT};

    if (argv[p_index] == NULL)
        return Port;

    char *index = strchr(argv[p_index], '-');

    if(index == NULL){
        int tmp_count = 0, i = p_index;

        while(argv[i] != NULL && argv[i][0] != '-') {
            tmp_count++;
            i++;
        }

        Port.count = tmp_count;
        Port.ports = malloc(tmp_count * sizeof(int));

        for(i = 0; i < tmp_count; i++){
            Port.ports[i] = (int)strtol(argv[p_index + i], NULL, 10);
        }
    }
    else{
        int start, end;

        if (sscanf(argv[p_index], "%d-%d", &start, &end) != 2 || start > end)
            return Port;

        Port.count = end - start + 1;
        Port.ports = malloc(Port.count * sizeof(int));

        for(int i = 0; i < Port.count; i++){
            Port.ports[i] = start + i;
        }
    }

    return Port;
}
void init_ports(Target* target, PortRange Port){
   int i;
   if(Port.ports==NULL){
    for(i=0; i<Port.count; i++){
        target->ports[i].port=i+1;
    }
   }
   else{
    for(i=0;i<Port.count; ++i){
        target->ports[i].port=Port.ports[i];
    }
   }


}
void cleanup(Target *targets, int count){
    int i;
    for(i=0; i<count; i++){
        free(targets[i].ip_addrs);
        free(targets[i].ports);
        
    }
    free(targets);
}
