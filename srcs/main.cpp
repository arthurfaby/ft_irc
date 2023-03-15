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
#include <netinet/in.h>

int	main(int argc, char **argv)
{
	int					socket_;
	int					new_socket;
	int					opt = 42;
	struct sockaddr_in	address;
	int					addrlen = sizeof(address);
	char				buffer[1024];

	if (argc != 3)
	{
		std::cout << "Invalid args. Usage : " << argv[0] << " <port> <password>"<<  std::endl;
		return (-1);
	}
	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_ == -1)
	{
		std::cerr << "Socket creation failed" << std::endl;
		return (-1);
	}
	if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		std::cerr << "Setsockopt failed" << std::endl;
		return (-1);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(std::atoi(argv[1]));
	if (bind(socket_, (struct sockaddr*)&address, sizeof(address)) == -1)
	{
		std::cerr << "Bind failed" << std::endl;
		return (-1);
	}
	if (listen(socket_, 5) == -1)
	{
		std::cerr << "Listen failed" << std::endl;
		return (-1);
	}
	while (1)
	{
		new_socket = accept(socket_, (struct sockaddr*)&address, (socklen_t*)&addrlen);
		if (new_socket == -1)
		{
			std::cerr << "Accept failed" << std::endl;
			return (-1);
		}
		if (recv(new_socket, buffer, 1024, 0) == -1)
			std::cerr << "Recv failed" << std::endl;
		else 
		{
			if (send(new_socket, "Message received\n", 17, 0) == -1)
			{
				std::cerr << "Send failed" << std::endl;
				return (-1);
			}
		}
		std::cout << buffer;
		buffer[0] = '\0';
		close(new_socket);
	}
	close(socket_);
	return (0);
}
