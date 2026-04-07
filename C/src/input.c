#include "input.h"
#include "scanner.h"

Ip_var* get_ip(const char* target, int *ip_count) {
    struct addrinfo hints, *res, *tmp;
    char ipstr[INET_ADDRSTRLEN];
    int status, count = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(target, NULL, &hints, &res);
    if (status != 0) {
        printf("Error: %s\n", gai_strerror(status));
        exit(1);
    }

   
    tmp = res;
    while (tmp != NULL) {
        count++;
        tmp = tmp->ai_next;
    }

    *ip_count = count;

    
    Ip_var* ip_list = malloc(count * sizeof(Ip_var));
    if (!ip_list) {
        perror("Malloc Err: ");
        freeaddrinfo(res);
        exit(1);
    }


    int i = 0;
    for (tmp = res; tmp != NULL; tmp = tmp->ai_next, i++) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)tmp->ai_addr;
        inet_ntop(AF_INET, &(ipv4->sin_addr), ip_list[i].ip_addr, INET_ADDRSTRLEN);
    }

    freeaddrinfo(res);
    return ip_list;
}
