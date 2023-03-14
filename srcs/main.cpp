#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "User.hpp"
#include "Operator.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Invalid args. Usage : " << argv[0] << " <port> <password>"<<  std::endl;
		return (-1);
	}
	return (0);
}
