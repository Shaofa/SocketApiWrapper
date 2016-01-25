/*
 * this program performs a tcp server,which shot back what
 * client sent.this program accept clients' connect
 * require and fork a child process to communicate with client, and
 * the parent process continue to wait for other clients' require.
 *
 * server IP: local ip
 * server port: 8888
 *
 * e-mail:  laishaofa@gmail.com
 * date:    2016-01-20
 * where:   NJUST
 */
#include "common.h"
#include <signal.h>


void sig_child(int signo)
{
    pid_t pid;
    int stat;
    while((pid = waitpid(-1,&stat, WNOHANG)) > 0)
    {
        fprintf(stdout, "child %d terminated!\n", pid);
        if(WIFEXITED(stat))
            fprintf(stdout, "Exit normally,code=%d\n", WEXITSTATUS(stat));
        else if(WIFSIGNALED(stat))
            fprintf(stdout, "Exit signaled,signo=%d\n", WTERMSIG(stat));
        else if(WIFSTOPPED(stat))
            fprintf(stdout, "Exit stopped,signo=%d\n", WSTOPSIG(stat));
    }
    return;
}


int main(int argc, const char* argv[])
{
    int listenfd,connfd;
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

    signal(SIGCHLD, sig_child);
    /*signal(SIGINT, sig_int);*/
    server_info(listenfd);

    while(1)
    {
        /* 4.accept */
        connfd = accept(listenfd, (struct sockaddr*)&addrcli, &addrlen);
        if(connfd < 0)
        {
            msg_err("accept");
            continue;
        }
        else
        {
            uint32_t pid = fork();
            // child process
            if(pid==0)
            {
                close(listenfd);
                char *str = "this is server!";
                char rdbuf[MAX_LINE_LEN] = {0};
                char wtbuf[MAX_LINE_LEN] = {0};
                char ipstr[32] = {0};
                if (inet_ntop(AF_INET, &addrcli.sin_addr, ipstr, sizeof(ipstr)) == NULL)
                    msg_err_die("inet_ntop");

                fprintf(stdout, "client <%s:%d> connected!\n", ipstr, ntohs(addrcli.sin_port));
                while(1)
                {
                    memset(rdbuf, 0, MAX_LINE_LEN);
                    ret = read(connfd, rdbuf, MAX_LINE_LEN);
                    if(ret > 0)
                    {
                        fprintf(stdout, "<%s:%d>%s", ipstr, ntohs(addrcli.sin_port), rdbuf);
                        write(connfd, rdbuf, ret);
                    }
                    else
                    {
                        close(connfd);
                        fprintf(stdout, "client <%s:%d> disconnected!\n", ipstr, ntohs(addrcli.sin_port));
                        exit(5);
                    }
                }
            }
            // parent process
            else if(pid>0)
                close(connfd);
            else
                msg_err_die("fork");
        }
    }
    return 0;
}
