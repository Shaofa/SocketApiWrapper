#include "sockapi.h"
#include "const.h"

int main(int argc, const char* argv[])
{
    int sockfd;
    struct sockaddr_in addrsvr;
    if(argc != 2)
    {
        err_die("Usage: server <IP address>");
    }

    sockfd = _socket(AF_INET, SOCK_STREAM, 0);
    bzero(&addrsvr, sizeof(struct sockaddr_in));
    addrsvr.sin_family = AF_INET;
    addrsvr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, argv[1], &addrsvr.sin_addr);

    _connect(sockfd, (struct sockaddr*)&addrsvr, sizeof(struct sockaddr_in));

    char rdbuf[MAX_LINE_LEN] = {0};
    char wtbuf[MAX_LINE_LEN] = {0};
    while(1)
    {
        bzero(wtbuf,  MAX_LINE_LEN);
        size_t n = 0;
        if(NULL != fgets(wtbuf, MAX_LINE_LEN, stdin))
        {
            write(sockfd,wtbuf, strlen(wtbuf));
            n = read(sockfd, rdbuf, MAX_LINE_LEN);
            rdbuf[n] = '\0';
            if(n < 0)
            {
                errno_die("Socket read");
            }
            fputs(rdbuf, stdout);
        }
        else
        {
            fprintf(stdout, "Bye!\n");
            exit(0);
        }
    }
    return 0;
}