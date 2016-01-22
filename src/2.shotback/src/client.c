#include "sockapi.h"
#include "const.h"

int main(int argc, const char* argv[])
{
    int sockfd;
    struct sockaddr_in addrsvr;
    if(argc != 2)
    {
        msg_die("Usage: server <IP address>");
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
            _write(sockfd,wtbuf, strlen(wtbuf));
            bzero(rdbuf, MAX_LINE_LEN);
            n = _read(sockfd, rdbuf, MAX_LINE_LEN);
            if(n == 0 )
            {
                msg_die("server terminated!");
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
