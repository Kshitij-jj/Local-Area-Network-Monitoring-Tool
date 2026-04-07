#include "common.h"
#include "scanner.h"


void init_data_structure(Ip_var *ip){

strcpy((*ip).ip_addr,"127.0.0.1"); // input handling module
(*ip).ports = (Port_var*) malloc(sizeof(Port_var)*MAX_PORT);

}
void free_data_structure(Ip_var *ip){
    free(ip->ports);
    ip->ports = NULL;
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
void test_scanning(const char *ip, int ports[], int port_size){
    int i;
    PortStatus status;
    printf("Ports\tStatus\n");
    for(i=0;i<port_size;i++){
        status = scan_port(ip,ports[i]);
        print_status(ports[i],status);
    }
} 
int main(){
//int ports[10]={22,80,432,500,531,632,780,840,956,1023};
//test_scanning("127.0.0.1",ports,10);
Ip_var ip;
init_data_structure(&ip);

//scanning
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
    

}
free_data_structure(&ip);

printf("Program Exited\n");
return 0;
 }
