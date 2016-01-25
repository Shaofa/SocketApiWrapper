#include "common.h"
#include <time.h>

int main(int argn, char* argv[]){
    int sock_listen;
    int rtn = 0;
    struct sockaddr_in addr;
    sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_listen == -1)
        msg_err_die("socket");

    bzero(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    rtn = bind(sock_listen, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if(rtn == -1)
        msg_err_die("bind");

    rtn = listen(sock_listen, 1);
    if(rtn == -1)
        msg_err_die("listen");

    size_t client_cnt = 0;
    while(1){
        int sock_client = -1;
        struct sockaddr_in addr_peer;
        time_t t = time(NULL);
        char buf[512] = {0};

        socklen_t addrlen = sizeof(struct sockaddr_in);
        sock_client = accept(sock_listen, (struct sockaddr*)&addr_peer, &addrlen);
        if(sock_client == -1)
            msg_err_die("accept");

        inet_ntop(AF_INET, &(addr_peer.sin_addr), buf, sizeof(buf));
        printf("connect from %s, port %d\n", buf, ntohs(addr_peer.sin_port));
        bzero(buf, sizeof(buf));
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&t));
        write(sock_client, buf, strlen(buf));
        sleep(1);
        close(sock_client);
    }

    return 0;
}
