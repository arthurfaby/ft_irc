#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "User.hpp"
#include "Operator.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

//doit creer une socket d'ecoute et l'assigner a l'attribut _listening_socket
int	create_listening_socket(void)
{
	int	listen_fd;
	int	opt = 1;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0)
	if (listen_fd == -1)
	{
		std::cerr << "Socket failed" << std::endl;
		return (-1);
	}
	if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
        std::cerr<< "Setsockopt failed" << std::endl;
        return (-1);
    }
	return (listen_fd);
}

//sert a initialiser la structure address qui contient toutes les infos sur le type avec lequel le serveur va communiquer et le port.
struct sockaddr_in init_address (struct sockaddr_in address, char *port)
{
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(std::atoi(/*this->*/port));
	return (address);
}

int	main(int argc, char **argv)
{
	int					listen_fd;
	struct sockaddr_in	address;

	if (argc != 3)
	{
		std::cerr << "Invalid args. Usage : " << argv[1] << ", <port> <password>" << std::endl;
		return (-1);
	}
	listen_fd = create_listening_socket();
	if (listen_fd == -1)
		return (-1);
	address = init_address(address, argv[1]);
	return (0);
}
