#include "common.h"

void server_info(int listenfd)
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

