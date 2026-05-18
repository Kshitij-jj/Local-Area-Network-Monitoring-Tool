#include "output.h"

void print_status(int port, PortStatus status) {
    switch (status) {
        case PORT_OPEN:     printf("\t%-6d\tOPEN\n",     port); break;
        case PORT_FILTERED: printf("\t%-6d\tFILTERED\n", port); break;
        default: break;
    }
}

void print(Target *targets, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < targets[i].ip_count; j++) {
            Ip_var *ip = &targets[i].ip_addrs[j];
            printf("\nScan Report For: %s (%s)\n", targets[i].hostname, ip->ip);
            printf("\t%-6s\t%s\n", "PORT", "STATUS");
            for (int k = 0; k < ip->port_count; k++) {
                if (ip->ports[k].status == PORT_OPEN || ip->ports[k].status == PORT_FILTERED)
                    print_status(ip->ports[k].port, ip->ports[k].status);
            }
        }
    }
}