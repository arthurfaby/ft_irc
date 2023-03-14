## FT_IRC

### Usefule typedefs
	
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

### Useful structs

```c++
struct addrinfo {
	int		ai_flags;
	int		ai_family;
	int		ai_socktype;
	int		ai_protocol;
	size_t		ai_addrlen;
	struct sockaddr	*ai_addr;
	char		*ai_canonname;
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
    dev_t	st_dev;
    ino_t	st_ino;
    mode_t	st_mode;
    nlink_t	st_nlink;
    uid_t	st_uid;
    gid_t	st_gid;
    dev_t	st_rdev;
    off_t	st_size; 
    blksize_t	st_blksize;
    blkcnt_t	st_blocks;
    time_t	st_atime;
    time_t	st_mtime;
    time_t	st_ctime;
};

struct hostent {
	char	*h_name;
	char	**h_aliases;
	int	h_addr_type;
	int	h_length;
	char	**h_addr_list;
};

struct protoent {
	char	*p_name;
	char	**p_aliases;
	int	p_proto;
};

struct in_addr {
	unsigned long	s_addr;
};
```
	
### Allowed functions

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

**accept**
> extract request on queue of *sockfd*, creates a new connected socket and returns a new fd referring to that socket. *sockfd* is unaffected by this call.

**bind**
> assigned the *addr* to the socket referred by *sockfd*. *addrlen* specifies the size of the address structure pointed to by *addr*. 

### Sockets

#### What is a socket ?

Sockets allow communication between two different **processes** on the same or different machines. 
It use **Unix fds** (file descriptors) to communicate. Every I/O operations is done by **writing** or **reading** a fd.
Functions such as read() and write() work with sockets in the **same way** they do with files and pipes.

#### Where is it used ?

Unix sockets are used in a **client-server** application framework (set of structural software components that serves to create the foundations of software, i.e. an architecture).

#### Different socket types :
- **Stream sockets** : Delivery in a networked environment is **guaranteed**. If you send through the stream socket three items A, B and C, they will arrive in the **same order**. These sockets use [**TCP**](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) (Transmission Control Protocol) for data tranmission. If delivery is impossible, the sender receives an **error indicator**. Data records do not have any boundaries.

- **Datagram sockets** : Delivery in a networked environment is **not guaranteed**. They're connectionless because you don't need to have an open connection as in **stream sockets**. You build a packet with the destination informatin and send it  out. They use [**UDP**](https://en.wikipedia.org/wiki/User_Datagram_Protocol) (User Datagram Protocol). 

- **Raw sockets** : These provide users acess to the **underlying** communication protocols, which support socket [**abstractions**](https://en.wikipedia.org/wiki/Abstraction_(computer_science)). These sockets are normally **datagram oriented**, though their exact characteristics are dependent on the interface provided by the protocol. Raw sockets are not intended for the general user; they have been provided mainly for those interested in **developing new communication protocols**, or for **gaining access to some of the more cryptic facilities** of an existing protocol.

- **Sequences packet sockets** : They are similar to a **stream socket**, with the exception that record boundaries are **preserved**. This interface is provided only as a part of the Network Systems (NS) socket abstraction, and is very important in most serious NS applications. Sequenced-packet sockets allow the user to **manipulate** the Sequence Packet Protocol (SPP) or Internet Datagram Protocol (IDP) headers on a packet or a group of packets, either by **writing a prototype** header along with whatever data is to be **sent**, or by specifying a default header to be used with all outgoing data, and allows the user to receive the headers on incoming packets.

### Sources
	
https://www.tutorialspoint.com/unix_sockets/what_is_socket.htm

https://man7.org/linux/man-pages/man2/accept.2.html
https://man7.org/linux/man-pages/man2/bind.2.html

