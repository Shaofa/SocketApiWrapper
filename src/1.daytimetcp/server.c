#include "sockapi_wrapper.h"
#include <time.h>

int main(int argn, char* argv[]){
    int sock_listen;
    struct sockaddr_in addr;
    sock_listen = _socket(AF_INET, SOCK_STREAM, 10);

    bzero(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _bind(sock_listen, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));

    _listen(sock_listen, 1);

    size_t client_cnt = 0;
    while(1){
        int sock_client = -1;
        struct sockaddr_in addr_peer;
        time_t t = time(NULL);
        char buf[512] = {0};

        socklen_t addrlen = sizeof(struct sockaddr_in);
        sock_client = _accept(sock_listen, (struct sockaddr*)&addr_peer, &addrlen);
        inet_ntop(AF_INET, &(addr_peer.sin_addr), buf, sizeof(buf));
        printf("connect from %s, port %d\n", buf, ntohs(addr_peer.sin_port));
        bzero(buf, sizeof(buf));
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&t));
        write(sock_client, buf, strlen(buf));
        sleep(1);
        _close(sock_client);
    }

    return 0;
}
