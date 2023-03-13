## FT_IRC


### Useful typedefs :
| Name |  Equivalent | Use case |
| :-: | :-: | :-: |
| blkcnt_t | `int` | Count of bytes |
| blksize_t | `int` | File block size |
| dev_t | `unsigned int` | Hold device numbers |
| gid_t | `unsigned int` | Hold group IDs |
| in_addr_t | `unsigned int` | Hold addresses |
| ino_t | `unsigned int` | Inode type |
| mode_t | `unsigned int`| File attributes |
| nfds_t | `unsigned int` | Number of file descriptors |
| nlink_t | `unsigned int`| Link counts |
| off_t | `int` | File sizes |
| size_t | `unsigned int` | Size of objects |
| sighandler_t | `void (*sighandler_t)(int)` | Signal processing function |
| socklen_t| `int` | Length and size values used by socket related parameters |
| ssize_t | `int `| Count of bytes or an error indication |
| time_t | `long` | Hold time in seconds |
| uid_t | `unsigned int` | Hold user IDs |
| uint16_t | `unsigned short` | :question: |
| uint32_t | `unsigned int` | :question: |
| ushort | `unsigned short` | :question:|

### Useful structs :

```c++
struct addrinfo {
	int				ai_flags;
	int				ai_family;
	int				ai_socktype;
	int				ai_protocol;
	size_t			ai_addrlen;
	struct sockaddr	*ai_addr;
	char			*ai_canonname;
	struct addrinfo	*ai_next;
};

struct sockaddr {
	ushort	sa_family;
	char	sa_data[14];
};

struct pollfd {
	int		fd;
	short	events;
	short	revents;
};

struct stat {
    dev_t		st_dev;
    ino_t		st_ino;
    mode_t		st_mode;
    nlink_t		st_nlink;
    uid_t		st_uid;
    gid_t		st_gid;
    dev_t		st_rdev;
    off_t		st_size; 
    blksize_t	st_blksize;
    blkcnt_t	st_blocks;
    time_t		st_atime;
    time_t		st_mtime;
    time_t		st_ctime;
};

struct hostent {
	char	*h_name;
	char	**h_aliases;
	int		h_addr_type;
	int		h_length;
	char	**h_addr_list;
};

struct protoent {
	char	*p_name;
	char	**p_aliases;
	int		p_proto;
};

struct in_addr {
	unsigned long	s_addr;
};
```


### Allowed functions :

| Function | Prototype |
| :-:| -|
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
