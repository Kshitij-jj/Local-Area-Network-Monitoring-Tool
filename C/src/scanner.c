#include "scanner.h"

Port_var *scan_ports(const char *ip, Port_var *ports, int port_count) {
    int sockfd[port_count], maxfd = 0;
    fd_set writefds, copyfds;
    FD_ZERO(&writefds);

    struct timeval tv = {1, 0};
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    for (int i = 0; i < port_count; i++) {
        sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd[i] < 0) { perror("socket"); exit(EXIT_FAILURE); }

        if (sockfd[i] >= FD_SETSIZE) {
            close(sockfd[i]);
            ports[i].status = PORT_ERROR;
            continue;
        }

        fcntl(sockfd[i], F_SETFL, O_NONBLOCK);
        serv_addr.sin_port = htons(ports[i].port);
        connect(sockfd[i], (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        FD_SET(sockfd[i], &writefds);
        if (sockfd[i] > maxfd) maxfd = sockfd[i];
    }

    copyfds = writefds;
    select(maxfd + 1, NULL, &copyfds, NULL, &tv);

    int err;
    socklen_t len = sizeof(err);
    for (int i = 0; i < port_count; i++) {
        if (sockfd[i] >= FD_SETSIZE) continue;
        if (FD_ISSET(sockfd[i], &copyfds)) {
            getsockopt(sockfd[i], SOL_SOCKET, SO_ERROR, &err, &len);
            if (err == 0)                ports[i].status = PORT_OPEN;
            else if (err == ECONNREFUSED) ports[i].status = PORT_CLOSED;
            else                          ports[i].status = PORT_FILTERED;
        } else {
            ports[i].status = PORT_FILTERED;
        }
        close(sockfd[i]);
    }

    return ports;
}