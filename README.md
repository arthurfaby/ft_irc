## ft_irc

### Allowed functions :

| Function | Prototype |
| -| -|
| accept | `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`|
| bind | `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);` |
| close | `int close(int fd);`|
| connect | `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);` |
| fcntl | `int fcntl(int fd, int cmd, ...);` |
| freeaddrinfo | `void freeaddrinfo(struct addrinfo *res);`|
| fstat | `int fstat(int fd, struct stat *statbuf);` |
| getaddrinfo | `int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);`|
| gethostbyname | `struct hostent *gethostbyname(const char *name);` |
| getprotobyname | `struct protoent *getprotobyname*(const char *name);` |
| getsockname | `int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);` |
| htonl | `uint32_t htonl(uint32_t hostlong);` |
| htons | `uint16_t htons(uint16_t hostshort);` |
| inet_addr | `in_addr_t inet_addr(const char *cp);` |
| inet_ntoa | `char *inet_ntoa(struct in_addr in);` |
| listen | `int listen(int sockfd, int backlog);`|
| lseek | `off_t lseek(int fd, off_t offset, int whence);` |
| ntonl | `uint32_t ntonl(uint32_t netlong);` |
| ntons | `uint16_t ntons(uint16_t netshort);` |
| poll | `int poll(struct pollfd *fds, nfds_t mfds, int timeout);` |
| recv | `ssize_t recv(int sockfd, void *buf, size_t len, int flags);` |
| send | `ssize_t send(int sockfd, const void *buf, size_t len, int flags);` |
| setsockopt | `int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);` |
| signal | `sighandler_t signal(int signum, sighandler_t handler);` |
| socket | `int socket(int domain, int type, int protocol);` |
