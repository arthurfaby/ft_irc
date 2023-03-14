## FT_IRC

### Useful typedefs
	
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
	int	fd;		// file descriptor
	short	events;		// requested events
	short	revents;	// returned events
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
	char	*p_name;	// the official name of the protocol
	char	**p_aliases;	// a NULL-terminated list of alternative names for the protocol
	int	p_proto;	// the protocol number
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
| poll | `int poll(struct pollfd *fds, nfds_t nfds, int timeout);` |
| recv | `ssize_t recv(int sockfd, void *buf, size_t len, int flags);` |
| send | `ssize_t send(int sockfd, const void *buf, size_t len, int flags);` |
| setsockopt | `int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);` |
| signal | `sighandler_t signal(int signum, sighandler_t handler);` |
| socket | `int socket(int domain, int type, int protocol);` |

**accept**
> extract request on queue of *sockfd*, creates a new connected socket and returns a new fd referring to that socket. *sockfd* is unaffected by this call.

**bind**
> assigned the *addr* to the socket referred by *sockfd*. *addrlen* specifies the size of the address structure pointed to by *addr*. 

**close**
> closes a file descriptor so that it no longer refers to any file and be reused


**connect**
> connects the socket referred by *sockfd* to the address specified by *addr*. *addrlen* specifies the size of the address structure pointed to by *addr*

**fcntl**
> performs a command (determined by *cmd*) on *fd*. See the [fcntl man](https://man7.org/linux/man-pages/man2/fcntl.2.html) for further details on commands.

**freeaddrinfo**
> free one or more **addrinfo** structures returned by **getaddrinfo()**. If *ai_next* field of the structure is not null, the entier list of structures shall be freed.

**fstat**
> obtain information abourt an open file associated with *fildes*, and write it to the area pointed to by *buf*.

**getaddrinfo**
> returns one or more **addrinfo** structures, each of which contains an Internet address that can be specified in a call to [bind(2)](https://man7.org/linux/man-pages/man2/bind.2.html) or [connect(2)](https://man7.org/linux/man-pages/man2/bind.2.html). **getaddrinfo()** combines the functionality provided by [gethostbyname(3)](https://man7.org/linux/man-pages/man3/gethostbyname.3.html) and [getservbyname(3)](https://man7.org/linux/man-pages/man3/getservbyname.3.html) into a single interface, but unline the latter functions, **getaddrinfo()** is reentrant and allows programs to eliminate IPv4-versus-IPv6 dependencies.

**gethostbyname**
> obsolete function. Applications should use [getaddrinfo(3)](https://man7.org/linux/man-pages/man3/getaddrinfo.3.html), [getnameinfo(3)](https://man7.org/linux/man-pages/man3/getnameinfo.3.html) and [gai_strerror(3)](https://man7.org/linux/man-pages/man3/gai_strerror.3.html) instead.

**getprotobyname**
> returns a **protoend** structure for the entry from the database that matches the protocol name *name*. A conncetion is opened to the database if necessary.

**getsockname**
> returns the current address to which the socket referred by *sockfd* is bound, un the buffer pointed to by *addr*. addrlen* specifies the size of the address structure pointed to by *addr*.

**htonl**
> converts *hostlong* from host byte order to network byte order.

**htons**
> converts *hostshort* from host byte order to network byte order.

**inet_addr**
> converts the internet host address *cp* from IPv4 numbers-and-dots notation into binary data in network byte order.

**inet_ntoa**
> converts the internet host address *in*, given in network byte order, to a string in IPv4 dotted-decimal notation.

**listen**
> marks the socket referred to by *sockfd* as a passive socket, that is, as a socket that will be used to accept incoming connection requests using [accept(2)](https://man7.org/linux/man-pages/man2/accept.2.html).

**lseek**
> repositions the file offset of *fd* to the argument *offset* according to the directive *whence* (see [lseek man](https://man7.org/linux/man-pages/man2/lseek.2.html) for further details).

**ntohl**
> converts *netlong* from network byte order to hsot byte order.

**ntohs**
> converts *netshort* from network byte order to hsot byte order.

**poll**
> 

**recv**

**send**

**setsockopt**

**signal**

**socket**


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

https://man7.org/linux/man-pages/man2/close.2.html

https://man7.org/linux/man-pages/man2/connect.2.html

https://man7.org/linux/man-pages/man2/fcntl.2.html

https://man7.org/linux/man-pages/man3/freeaddrinfo.3p.html

https://man7.org/linux/man-pages/man3/fstat.3p.html

https://man7.org/linux/man-pages/man3/getaddrinfo.3.html

https://man7.org/linux/man-pages/man3/gethostbyname.3.html

https://linux.die.net/man/3/getprotobyname

https://man7.org/linux/man-pages/man2/getsockname.2.html

https://linux.die.net/man/3/htonl (for htonl, htons, ntolh and ntols)

https://linux.die.net/man/3/inet_addr (for inet_addr and inet_ntoa)

https://man7.org/linux/man-pages/man2/listen.2.html

https://man7.org/linux/man-pages/man2/lseek.2.html

https://man7.org/linux/man-pages/man2/poll.2.html
