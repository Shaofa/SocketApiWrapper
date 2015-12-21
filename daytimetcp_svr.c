#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define die(msg)    do{perror(msg); exit(EXIT_FAILURE);}while(0)

int Socket(int domain, int type, int protocol){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
        die("SOCKET");
    return sock;
}
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    if(bind(sockfd,addr, addrlen) < 0)
        die("LISTEN");
    return 0;
}
int Listen(int sockfd, int backlog){
    if(listen(sockfd, backlog) < 0)
        die("LISTEN");
    return 0;
}
int Accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen){
     int sock_peer;
     sock_peer = accept(sockfd, addr, addrlen);
     if(sock_peer < 0)
         die("ACCEPT");
     return sock_peer;
}

int main(int argn, char* argv[]){
    int sock_listen;
    struct sockaddr_in addr;
    sock_listen = Socket(AF_INET, SOCK_STREAM, 10);

    bzero(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(sock_listen, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));

    Listen(sock_listen, 1);

    size_t client_cnt = 0;
    while(1){
        int sock_client = -1;
        struct sockaddr_in addr_peer;
        socklen_t addrlen = sizeof(struct sockaddr_in);
        sock_client = Accept(sock_listen, (struct sockaddr*)&addr_peer, &addrlen);
        char str_addr_peer[512];
        inet_ntop(AF_INET, (void*)&addr_peer.sin_addr, str_addr_peer, sizeof(struct in_addr));
        printf("%s:%d\n",str_addr_peer, ntohs(addr_peer.sin_port));
        close(sock_client);
    }


    return 0;
}
