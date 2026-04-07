#include "scanner.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

PortStatus scan_port(const char *ip, int port){
    PortStatus status = PORT_ERROR;

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    // Socket creation
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Socket failed");
        return status;
    }

    // Set timeout for connect
    struct timeval tv;
    tv.tv_sec = 1;     
    tv.tv_usec = 0;
    if(setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0){
        perror("Setsockopt failed");
        close(sockfd);
        return status;
    }

    // Connect
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == 0){
        status = PORT_OPEN;
    } else {
        if(errno == ECONNREFUSED){
            status = PORT_CLOSED;
        } else if(errno == ETIMEDOUT ||errno == EINPROGRESS || errno == EHOSTUNREACH || errno == ENETUNREACH){
            status = PORT_FILTERED;
        } else {
		printf("%d: %s\n",errno,strerror(errno));
            perror("Connect failed");
            status = PORT_ERROR;
        }
    }

    close(sockfd);
    return status;
}
