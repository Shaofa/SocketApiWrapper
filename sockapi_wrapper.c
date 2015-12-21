
#define die(msg)    do{perror(msg); exit(EXIT_FAILURE);}while(0)

int Socket(int domain, int type, int protocol){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
        die("SOCKET");
    return sock;
}
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    if(bind(sockfd,addr, addrlen) < 0)
        die("LISTEN");
    return 0;
}
int Listen(int sockfd, int backlog){
    if(listen(sockfd, backlog) < 0)
        die("LISTEN");
    return 0;
}
int Accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen){
     int sock_peer;
     sock_peer = accept(sockfd, addr, addrlen);
     if(sock_peer < 0)
         die("ACCEPT");
     return sock_peer;
}
