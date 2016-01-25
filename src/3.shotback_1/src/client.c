#include "common.h"

int main(int argc, const char* argv[])
{
    int sockfd;
    int ret = 0;
    struct sockaddr_in addrsvr;
    if(argc != 2)
    {
        msg_die("Usage: server <IP address>");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
        msg_err_die("socket");

    bzero(&addrsvr, sizeof(struct sockaddr_in));
    addrsvr.sin_family = AF_INET;
    addrsvr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, argv[1], &addrsvr.sin_addr);

    ret = connect(sockfd, (struct sockaddr*)&addrsvr, sizeof(struct sockaddr_in));
    if(ret == -1)
        msg_err_die("connect");

    char rdbuf[MAX_LINE_LEN] = {0};
    char wtbuf[MAX_LINE_LEN] = {0};
    while(1)
    {
        bzero(wtbuf,  MAX_LINE_LEN);
        size_t n = 0;
        if(NULL != fgets(wtbuf, MAX_LINE_LEN, stdin))
        {
            ret = write(sockfd,wtbuf, strlen(wtbuf));
            bzero(rdbuf, MAX_LINE_LEN);
            ret = read(sockfd, rdbuf, MAX_LINE_LEN);
            if(ret == 0 )
            {
                msg_err_die("server terminated!");
            }
            fputs(rdbuf, stdout);
        }
        else
        {
            msg_die("Bye!");
        }
    }
    return 0;
}
