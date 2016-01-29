#ifndef _CONST_H_
#define _CONST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define     SERVER_PORT     (short)(8888)
#define     MAX_LINE_LEN    (uint32_t)(1024)
#define     MAX_BUF_SIZE    (uint32_t)(1024)
#define     MAX_LISTEN_Q    (uint32_t)(1)


#define \
    min(x, y)\
    ({\
        const typeof(x) _x = (x);\
        const typeof(y) _y = (y);\
        (void)(&_x==&_y);\
        _x < _y ? _x : _y;\
    })

#define \
    max(x, y)\
    ({\
        const typeof(x) _x = (x);\
        const typeof(y) _y = (y);\
        (void)(&_x==&_y);\
        _x > _y ? _x : _y;\
    })

#define     STDOUT     stdout
#define     msg(m)          fprintf(STDOUT, "%s\n", m)
#define     msg_die(m)      do{ msg(m); exit(0);}while(0)
#define     msg_err(m)      do{ if(errno>0) perror(m); else fprintf(STDOUT,"error(L%d):%s\n", __LINE__, m); }while(0)
#define     msg_err_die(m)  do{ msg_err(m); exit(EXIT_FAILURE); }while(0)


extern void server_info(int listenfd);

#endif//_COMMON_H_
