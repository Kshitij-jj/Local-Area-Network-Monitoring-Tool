#include "input.h"
#include "scanner.h"
Target* get_targets(int argc, char *argv[], int *target_count){
    
    *target_count = argc - 1;
    int i = *target_count;

    Target *tmp = malloc( i *sizeof(Target) );
    if(tmp==NULL){
        perror("Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    int j=0;
   while(j<i){
    (tmp+j)->ip_addrs = get_ip(argv[j+1],&((tmp+j)->ip_count));
    strcpy(((tmp+j)->hostname),argv[j+1]);
    (tmp+j)->port_count = MAX_PORT; //for now
    (tmp+j)->ports = malloc( ((tmp+j)->port_count) * sizeof(Port_var));
    
    if((tmp+j)->ports==NULL){
        perror("Allocation Failed: \n");
    }
    ++j;
   }
    return tmp;
}

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
        inet_ntop(AF_INET, &(ipv4->sin_addr), ip_list[i].ip, INET_ADDRSTRLEN);
    }

    freeaddrinfo(res);
    return ip_list;
}
