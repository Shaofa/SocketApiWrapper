#include "common.h"

int main(int argc, const char* argv[])
{
    int sockfd;
    int ret = 0;
    struct sockaddr_in addrsvr;
    char rdwrbuf[MAX_LINE_LEN] = {0};

    if(argc != 2)
    {
        msg_die("Usage: server <IP address>");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        msg_err_die("socket");
    }

    bzero(&addrsvr, sizeof(struct sockaddr_in));
    addrsvr.sin_family = AF_INET;
    addrsvr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, argv[1], &addrsvr.sin_addr);

    ret = connect(sockfd, (struct sockaddr*)&addrsvr, sizeof(struct sockaddr_in));
    if(ret == -1)
    {
        msg_err_die("connect");
    }

    fd_set fdset;
    uint32_t maxfd;
    size_t n = 0;
    char *pt = NULL;
    uint32_t isStdinEof = 0;

    while(1)
    {
        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);
        if(isStdinEof != 1)
        {
            FD_SET(fileno(stdin), &fdset);
            maxfd = max(fileno(stdin), sockfd) + 1;
        }
        else
        {
            maxfd = sockfd + 1;
        }
        ret = select(maxfd, &fdset, NULL, NULL, NULL);
        if(ret == -1)
        {
            msg_err_die("select");
        }
        else if(ret == 0)
            continue;

        /*stdin is ready*/
        if( FD_ISSET(fileno(stdin), &fdset) )
        {
            bzero(rdwrbuf,  MAX_LINE_LEN);
            pt = fgets(rdwrbuf, MAX_LINE_LEN, stdin);
            if(NULL == pt)
            {
                msg("input stopped!");
                isStdinEof = 1;
                ret = shutdown(sockfd, SHUT_WR);
                if(ret == -1)
                {
                    msg_err_die("shutdown");
                }
                continue;
            }
            ret = write(sockfd, rdwrbuf, strlen(rdwrbuf));
            if(ret == -1)
            {
                msg_err_die("write");
            }
        }

        /*sockfd is ready*/
        if( FD_ISSET(sockfd, &fdset) )
        {
            bzero(rdwrbuf, MAX_LINE_LEN);
            ret = read(sockfd, rdwrbuf, MAX_LINE_LEN);
            if(ret == -1)
            {
                msg_err_die("read");
            }
            else if(ret == 0)
            {
                msg_die("server terminated!");
            }
            fputs(rdwrbuf, stdout);
        }
    } //while(1)

    return 0;
} // end of main

// end of file
