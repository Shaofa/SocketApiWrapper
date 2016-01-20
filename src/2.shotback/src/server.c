#include "sockapi.h"
#include "const.h"
#include <signal.h>

void sig_child(int signo)
{
    pid_t pid;
    int state;
    pid = wait(&state);
    if(WIFEXITED(state))
        fprintf(stdout, "Exit normally,code = %d\n", WEXITSTATUS(state));
    else if(WIFSIGNALED(state))
        fprintf(stdout, "Exit signaled,signo = %d\n", WTERMSIG(state));
    else if(WIFSTOPPED(state))
        fprintf(stdout, "Exit stopped,signo = %d\n", WSTOPSIG(state));
    return;
}
/*
void sig_int(int signo)
{
    pid_t pid;
    int stat;
    pid = wait(&stat);
    fprintf(stdout, "stat = %d\n", stat);
    if(WIFEXITED(stat) == 0)
        fprintf(stdout, "EXIT");
    else
    {
        int code = WEXITSTATUS(stat);
        fprintf(stdout, "Exit code = %d\n", code);;
    }
}
*/
int main(int argc, const char* argv[])
{
    int listenfd,connfd;
    struct sockaddr_in addrsvr, addrcli;
    uint32_t addrlen = sizeof(struct sockaddr_in);

    /* 1.socket */
    listenfd = _socket(AF_INET, SOCK_STREAM, 0);

    /* 2.bind */
    bzero(&addrsvr, sizeof(struct sockaddr_in));
    addrsvr.sin_family = AF_INET;
    addrsvr.sin_port = htons(SERVER_PORT);
    addrsvr.sin_addr.s_addr = htonl(INADDR_ANY);
    _bind(listenfd, (struct sockaddr*)&addrsvr, sizeof(struct sockaddr_in));

    /* 3.listen */
    _listen(listenfd, MAX_LISTEN_Q);

    signal(SIGCHLD, sig_child);
    //signal(SIGINT, sig_int);
    _server(listenfd);

    while(1)
    {
        /* 4.accept */
        connfd = _accept(listenfd, (struct sockaddr*)&addrcli, &addrlen);
        if(connfd < 0)
        {
            if(errno == EINTR)
                err_msg("EINTR");
            else
                err_msg("accept error");
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
                    errno_die("inet_ntop");

                fprintf(stdout, "client <%s:%d> connected!\n", ipstr, ntohs(addrcli.sin_port));
                while(1)
                {
                    memset(rdbuf, 0, MAX_LINE_LEN);
                    uint32_t n = read(connfd, rdbuf, MAX_LINE_LEN);
                    if(n > 0)
                    {
                        fprintf(stdout, "<%s:%d>%s", ipstr, ntohs(addrcli.sin_port), rdbuf);
                        write(connfd, rdbuf, n);
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
            else
            {
                close(connfd);
            }
        }
    }
    return 0;
}
