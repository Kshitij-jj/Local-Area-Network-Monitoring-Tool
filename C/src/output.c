#include"output.h"
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
void print(Target* targets, int count){
    int i,j,cur_port;
 for(i=0; i<count; i++)
    {
         int ip_count_tmp = (targets+i)->ip_count;
         int port_count_tmp = (targets+i)->port_count;  
         for(j=0; j < ip_count_tmp ; j++ )
            {   
                char *ipaddr = (targets+i)->ip_addrs[j].ip;
                printf("Scan Report For IP: %s\n",ipaddr);
                printf("\t\tPORT\t\tSTATUS\n");
                for(cur_port=0; cur_port<port_count_tmp; cur_port++)
                    {   
                      
                        PortStatus stat= targets[i].ports[cur_port].status;
                        if( stat == PORT_OPEN || stat == PORT_FILTERED )
                        print_status(targets[i].ports[cur_port].port,stat);
                        
                    }
            }
    
    
    } 
}

  
