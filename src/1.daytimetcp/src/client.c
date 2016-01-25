#include "common.h"


int main(int argn, const char *argv[])
{
    if(argn != 2)
    {
        printf("Usage:\n");
        printf("%s  [host]\n", argv[0]);
        return -1;
    }
    int sockfd;
    struct sockaddr_in addr_svr;
    int ret = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
        msg_die("socket");

    bzero(&addr_svr, sizeof(struct sockaddr_in));
    addr_svr.sin_family = AF_INET;
    addr_svr.sin_port = htons(13);
    ret = inet_pton(AF_INET, argv[1], &addr_svr.sin_addr);
    if(ret != 1)
    {
        printf("INET_PTON:%s\n",ret==0?"Net Address is invalid!" : "Address family is not supported!");
        close(sockfd);
        return -1;
    }

    ret = connect(sockfd, (struct sockaddr*)&addr_svr, sizeof(struct sockaddr_in));
    if(ret == -1)
        msg_die("connect");

    char recvBuf[512] = {0};
    int len = 0;
    len = read(sockfd, recvBuf, sizeof(recvBuf));
    if(len > 0)
    {
        recvBuf[len] = 0;
        fputs(recvBuf, stdout);
    }
    close(sockfd);

    return 0;
}
