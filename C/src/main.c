#include "common.h"
#include "scanner.h"
#include "input.h"

void init_port(Ip_var *ip){
	(*ip).ports = (Port_var*) malloc(sizeof(Port_var)*MAX_PORT);
}
void free_port(Ip_var *ip){
    free(ip->ports);
    ip->ports = NULL;
}
void free_ip_list(Ip_var *ip){
    free(ip);
}
void print_status(int port, PortStatus status){
    switch (status)
        {
        case PORT_OPEN:
            printf("\t\t%d\t\tOpen\n",port);
            break;
        case PORT_CLOSED:
            printf("\t\t%d\t\tCLOSED\n",port);
            break;
        case PORT_FILTERED:
            printf("\t\t%d\t\tFILTERED\n",port);
            break;
        default:
            printf("\t\t%d\t\tERROR\n",port);
            break;
        
        }
    
}
// void test_scanning(const char *ip, int ports[], int port_size){
//     int i;
//     PortStatus status;
//     printf("Ports\tStatus\n");
//     for(i=0;i<port_size;i++){
//         status = scan_port(ip,ports[i]);
//         print_status(ports[i],status);
//     }
// } 
int main(int argc, char* argv[]){
if(argc<2){
    fputs("Usage: scan <target>",stderr);
    exit(EXIT_FAILURE);
    }
char *target = argv[1];
int count=0,i;
Ip_var *ip_list = get_ip(target, &count);

for(i=0;i<count;i++){
    printf("IP Adress: %s\n",ip_list[i].ip_addr);
}
/*
int curnt_port;
for( curnt_port=1; curnt_port<=MAX_PORT; curnt_port++){
    ip.ports[curnt_port-1].port=curnt_port;
    ip.ports[curnt_port-1].status = scan_port(ip.ip_addr, curnt_port);
}

// output module
printf("\t\tPorts\t\tStatus\n");
for(curnt_port=0 ;curnt_port<MAX_PORT; curnt_port++){
    PortStatus stat = ip.ports[curnt_port].status;
    
        print_status(curnt_port+1,stat);
    

}*/
for(i=0;i<count;i++){
init_port(&ip_list[i]);
}
for(i=0;i<count;i++){
free_port(&ip_list[i]);
}
free_ip_list(ip_list);
printf("Program Exited\n");
return 0;
 }
