#include "common.h"
#include "scanner.h"
#include "input.h"
#include "helper.h"
#include "output.h"
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
int count,i;
Target * targets = get_targets(argc, argv, &count);

//Scanning
int j,cur_port;
printf("Proceding to scanning: \n");
for(i=0; i<count; i++)
    {
         int ip_count_tmp = (targets+i)->ip_count;
         int port_count_tmp = (targets+i)->port_count;  
         for(j=0; j < ip_count_tmp ; j++ )
            {   
                char *ipaddr = (targets+i)->ip_addrs[j].ip;
                
                for(cur_port=1; cur_port<=port_count_tmp; cur_port++)
                    {   
                        int index = cur_port - 1;
                        PortStatus stat;
                        (targets+i)->ports[index].port = cur_port; // seems not worth in this case but later
                        stat = scan_port(ipaddr, cur_port);
                        (targets+i)->ports[index].status=stat;
                        float progress = (float)cur_port / (float)port_count_tmp * 100;
                        printf("Done: %.0f%\r",progress);
                        fflush(stdout);
                    }
            }
    }
print(targets, count);
cleanup(targets,count);
printf("Program Exited\n");
return 0;
 }
