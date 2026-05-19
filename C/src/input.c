#include "input.h"
#include "helper.h"
char get_format(int argc, char *argv[]){
	int p_idx = find_flag(argc, argv, "-o");
	if(p_idx == -1) return DEFAULT_FORMAT;
	else return argv[p_idx+1][0];
}
Target *get_targets(int argc, char *argv[], int *target_count) {
    PortRange Port;
    int p_idx = find_flag(argc, argv, "-p");
    int o_idx = find_flag(argc, argv, "-o");
    if (p_idx != -1 && o_idx == -1) {
        *target_count = p_idx - 1;
        Port = get_ports(p_idx, argv);
    }else if(p_idx !=-1 && o_idx !=-1){
        *target_count = (p_idx < o_idx)? p_idx - 1: o_idx - 1;
        Port = get_ports(p_idx, argv);
    }
    else if(p_idx == -1 && o_idx != -1){
        *target_count = o_idx - 1;
        Port.ports = NULL;
        Port.count = MAX_PORT;
    }
    else {
        *target_count = argc - 1;
        Port.ports = NULL;
        Port.count = MAX_PORT;
    }

    Target *targets = malloc(*target_count * sizeof(Target));
    if (!targets) { perror("malloc"); exit(EXIT_FAILURE); }

    for (int i = 0; i < *target_count; i++) {
        targets[i].ip_addrs = get_ip(argv[i + 1], &targets[i].ip_count);
        strncpy(targets[i].hostname, argv[i + 1], MAX_HOSTNAME - 1);
        targets[i].hostname[MAX_HOSTNAME - 1] = '\0';

        for (int k = 0; k < targets[i].ip_count; k++) {
            targets[i].ip_addrs[k].port_count = Port.count;
            targets[i].ip_addrs[k].ports = malloc(Port.count * sizeof(Port_var));
            if (!targets[i].ip_addrs[k].ports) { perror("malloc"); exit(EXIT_FAILURE); }
            init_ports(&targets[i].ip_addrs[k], Port);
        }
    }

    free(Port.ports);
    return targets;
}

Ip_var *get_ip(const char *target, int *ip_count) {
    struct addrinfo hints, *res, *tmp;
    int status, count = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(target, NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (tmp = res; tmp != NULL; tmp = tmp->ai_next) count++;
    *ip_count = count;

    Ip_var *ip_list = malloc(count * sizeof(Ip_var));
    if (!ip_list) { perror("malloc"); freeaddrinfo(res); exit(EXIT_FAILURE); }

    int i = 0;
    for (tmp = res; tmp != NULL; tmp = tmp->ai_next, i++) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)tmp->ai_addr;
        inet_ntop(AF_INET, &ipv4->sin_addr, ip_list[i].ip, INET_ADDRSTRLEN);
    }

    freeaddrinfo(res);
    return ip_list;
}
