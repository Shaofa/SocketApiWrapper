#include "sockapi_wrapper.h"


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

    sockfd = _socket(AF_INET, SOCK_STREAM, 0);

    bzero(&addr_svr, sizeof(struct sockaddr_in));
    addr_svr.sin_family = AF_INET;
    addr_svr.sin_port = htons(13);
    if((ret=inet_pton(AF_INET, argv[1], &addr_svr.sin_addr)) != 1)
    {
        printf("INET_PTON:%s\n",ret==0?"Net Address is invalid!" : "Address family is not supported!");
        _close(sockfd);
        return -1;
    }

    ret = _connect(sockfd, (struct sockaddr*)&addr_svr, sizeof(struct sockaddr_in));

    char recvBuf[512] = {0};
    int len = 0;
    if((len=read(sockfd, recvBuf, sizeof(recvBuf))) >0)
    {
        recvBuf[len] = 0;
        fputs(recvBuf, stdout);
    }
    _close(sockfd);

    return 0;
}
