/*
 * this program performs a tcp server,which shot back what
 * client sent.this program accept clients' connect
 * require and record the socket descriptor.IO select wake up
 * when at least one of the communication socket is readably.
 *
 * server IP: local ip
 * server port: 8888
 *
 * e-mail:  laishaofa@gmail.com
 * date:    2016-01-28
 * where:   NJUST
 */
#include "../../common/common.h"
#include <signal.h>


int main(int argc, const char* argv[])
{
    int listenfd;
    int ret = 0;
    struct sockaddr_in addrsvr, addrcli;
    uint32_t addrlen = sizeof(struct sockaddr_in);

    /*1.socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        msg_err_die("socket");

    /* 2.bind */
    bzero(&addrsvr, sizeof(struct sockaddr_in));
    addrsvr.sin_family = AF_INET;
    addrsvr.sin_port = htons(SERVER_PORT);
    addrsvr.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(listenfd, (struct sockaddr*)&addrsvr, sizeof(struct sockaddr_in));
    if(ret == -1)
        msg_err_die("bind");

    /* 3.listen */
    ret = listen(listenfd, MAX_LISTEN_Q);
    if(ret == -1)
        msg_err_die("listen");

    server_info(listenfd);

    int connfd[FD_SETSIZE] = {-1};
    fd_set fdset, bkset;
    int maxfd = -1;
    int maxIdx = 0;
    int i = 0;
    char rdbuf[MAX_LINE_LEN] = {0};
    memset(connfd, -1, sizeof(connfd));
    FD_ZERO(&fdset);
    FD_SET(listenfd, &fdset);
    bkset = fdset;
    maxfd = listenfd;
    while(1)
    {
        int curr_fd_num = 0;
        fdset = bkset;
        curr_fd_num = select(maxfd+1, &fdset, NULL, NULL, NULL);
        if(curr_fd_num == -1)
        {
            msg_err_die("select");
        }

        /*listen socket readable*/
        if(FD_ISSET(listenfd, &fdset))
        {
            ret = accept(listenfd, (struct sockaddr*)&addrcli, &addrlen);
            if(ret == -1)
            {
                msg_err_die("accept");
            }
            for(i=0; i<FD_SETSIZE; i++)
            {
                if(connfd[i] < 0)
                {
                    connfd[i] = ret;
                    FD_SET(ret, &bkset);
                    fprintf(stdout, "%d connected!\n", ret);
                    break;
                }
            }
            if(i == FD_SETSIZE)
            {
                msg_err_die("too many clients!");
            }
            maxfd = ret>maxfd ? ret : maxfd;
            maxIdx = i>maxIdx ? i : maxIdx;
            if(--curr_fd_num <=0 )
                continue;
        }

        /*connected socket is readable*/
        for(i=0; (i<FD_SETSIZE) && (curr_fd_num>0); i++)
        {
            curr_fd_num--;
            if(connfd[i] < 0)
                continue;
            if(FD_ISSET(connfd[i], &fdset))
            {
                memset(rdbuf, 0, MAX_LINE_LEN);
                ret = read(connfd[i], rdbuf, MAX_LINE_LEN);
                if(ret == -1)   // error
                {
                    msg_err_die("read");
                }
                if(ret == 0)    // EOF
                {
                    fprintf(stdout, "%d disconnected!\n", connfd[i]);
                    FD_CLR(connfd[i], &bkset);
                    close(connfd[i]);
                    connfd[i] = -1;
                }
                else
                {
                    fprintf(stdout, "%d: %s", connfd[i], rdbuf);
                    ret = write(connfd[i], rdbuf, ret);
                    if(ret == -1)
                    {
                        msg_err_die("write");
                    }
                }
            }
        }
    } // while(1)

    return 0;
}
