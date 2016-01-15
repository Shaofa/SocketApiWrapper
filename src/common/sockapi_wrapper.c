#include "sockapi_wrapper.h"


int _socket(int domain, int type, int protocol)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
        die("SOCKET");
    return sock;
}

int _bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if(bind(sockfd,addr, addrlen) < 0)
        die("LISTEN");
    return 0;
}


int _listen(int sockfd, int backlog)
{
    if(listen(sockfd, backlog) < 0)
        die("LISTEN");
    return 0;
}


int _connect(int sockfd, const struct sockaddr *addr, const socklen_t addrlen)
{
    if(connect(sockfd, addr, addrlen) < 0)
        die("CONNECT");
    return 0;
}

int _accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen)
{
    int sock_peer;
    sock_peer = accept(sockfd, addr, addrlen);
    if(sock_peer < 0)
        die("ACCEPT");
    return sock_peer;
}

void _close(int sockfd)
{
    if(sockfd < 0)
        die("CLOSE");
    close(sockfd);
}
