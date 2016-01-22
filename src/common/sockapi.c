#include "sockapi.h"


int _socket(int domain, int type, int protocol)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
        msg_err_die("SOCKET");
    return sock;
}

int _bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if(bind(sockfd,addr, addrlen) < 0)
        msg_err_die("LISTEN");
    return 0;
}


int _listen(int sockfd, int backlog)
{
    if(listen(sockfd, backlog) < 0)
        msg_err_die("LISTEN");
    return 0;
}


int _connect(int sockfd, const struct sockaddr *addr, const socklen_t addrlen)
{
    if(connect(sockfd, addr, addrlen) < 0)
        msg_err_die("CONNECT");
    return 0;
}

int _accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen)
{
    int sock_peer;
    sock_peer = accept(sockfd, addr, addrlen);
    if(sock_peer < 0)
        msg_err_die("ACCEPT");
    return sock_peer;
}

void _close(int sockfd)
{
    if(sockfd < 0)
        msg_err_die("CLOSE");
    close(sockfd);
}

size_t _write(int sockfd, const void* buf, size_t count)
{
    if(buf == NULL)
        msg_err_die("null pointer!");
    size_t s = write(sockfd, buf, count);
    if(s ==  -1)
        msg_err_die("write");
    return s;
}

size_t _read(int sockfd, void* buf, size_t count)
{
    if(buf==NULL)
        msg_err_die("null porinter!");
    size_t s = read(sockfd, buf, count);
    if(s == -1)
        msg_err_die("read");
    return s;
}

void _server(int listenfd)
{
    struct sockaddr_storage addr;
    socklen_t len = sizeof(struct sockaddr_storage);
    if(-1 == getsockname(listenfd, (struct sockaddr*)&addr, &len))
        msg_err_die("getsockname");

    if(addr.ss_family == AF_INET)
    {
        struct sockaddr_in *addr4 = (struct sockaddr_in*)&addr;
        char ipstr[32] = {0};
        if(NULL == inet_ntop(AF_INET, &(addr4->sin_addr.s_addr), ipstr, sizeof(ipstr)))
            msg_err_die("inet_ntop");

        fprintf(stdout,
                "=====================================\n"
                "I am IPv4 server!\n"
                "IP address:%s\n"
                "Port:%d\n"
                "=====================================\n"
                "Listening...\n",
                ipstr, ntohs(addr4->sin_port));
    }
    else if(addr.ss_family == AF_INET6)
    {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6*)&addr;
        char ipstr[64] = {0};
        if(NULL == inet_ntop(AF_INET6, &(addr6->sin6_addr.s6_addr), ipstr, sizeof(ipstr)))
            msg_err_die("inet_ntop");

        fprintf(stdout,
                "=====================================\n"
                "I am IPv6 server!\n"
                "IP address:%s\n"
                "Port:%d\n"
                "=====================================\n"
                "Listening...\n",
                ipstr, ntohs(addr6->sin6_port));
    }
    sleep(1);
}

