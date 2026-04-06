#include "common.h"
#include "scanner.h"
void test_scanning(const char *ip, int ports[], int port_size){
    int i;
    PortStatus status;
    printf("Ports\tStatus\n");
    for(i=0;i<port_size;i++){
        status = scan_port(ip,ports[i]);
        switch (status)
        {
        case PORT_OPEN:
            printf("%d\tOpen\n",ports[i]);
            break;
        case PORT_CLOSED:
            printf("%d\tCLOSED\n",ports[i]);
            break;
        case PORT_FILTERED:
            printf("%d\tFILTERED\n",ports[i]);
            break;
        case PORT_ERROR:
            printf("%d\tERROR\n",ports[i]);
            break;
            default:
            break;
        }
    }
} 
int main(){
int ports[10]={22,80,432,500,531,632,780,840,956,1023};
test_scanning("127.0.0.1",ports,10);
printf("Program Exited\n");
return 0;
 }