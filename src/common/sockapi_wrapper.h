#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>

#define  die(msg)    do{ perror(msg); exit(EXIT_FAILURE); }while(0)

extern int  _socket(int domain, int type, int protocol);

extern int  _bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);

extern int  _listen(int sockfd, int backlog);

extern int  _connect(int sockfd, const struct sockaddr *addr, const socklen_t addrlen);

extern int  _accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen);

extern void _close(int sockfd);
