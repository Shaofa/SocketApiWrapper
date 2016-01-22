#ifndef     _SOCKAPI_WRAPPER_H_
#define     _SOCKAPI_WRAPPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define     STDOUT     stdout

#define     msg(m)          fprintf(STDOUT, "%s\n", m)
#define     msg_die(m)      do{ msg(m); exit(0);}while(0)
#define     msg_err(m)      do{ if(errno<0) perror(m); else fprintf(STDOUT,"error(L%d):%s\n", __LINE__, m); }while(0)
#define     msg_err_die(m)  do{ msg_err(m); exit(EXIT_FAILURE); }while(0)

#define  err_msg(m)     fprintf(STDOUT,"error(L%d):%s\n", __LINE__, m)
#define  err_die(m)     do{ if(errno<0) perror()err_msg(m); exit(EXIT_FAILURE);}while(0)
#define  errno_die(m)   do{ perror(m); exit(EXIT_FAILURE);}while(0)


extern int  _socket(int domain, int type, int protocol);
extern int  _bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
extern int  _listen(int sockfd, int backlog);
extern int  _connect(int sockfd, const struct sockaddr *addr, const socklen_t addrlen);
extern int  _accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen);
extern void _close(int sockfd);
extern size_t _write(int sockfd, const void* buf, size_t count);

extern void _server(int listenfd);
#endif  // #ifndef _SOCKAPI_WRAPPER_H_
