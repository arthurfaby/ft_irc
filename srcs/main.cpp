#include "Server.hpp"
#include "common.hpp"

int	verif_args(int argc, char **argv)
{
	int	i;
	int	port;

	if (argc != 3)
	{
		std::cerr << ERROR << "Usage : " << argv[0] << " <port> <password>" << std::endl;
		return (1);
	}
	i = 0;
	while (argv[1][i])
	{
		if (!std::isdigit(argv[1][i]))
		{
			std::cerr << ERROR << "Usage : " << argv[0] << " <port> <password>" << std::endl;
			return (1);
		}
		++i;
	}
	port = std::atoi(argv[1]);
	if (i != 4 || port > 6669 || port < 6660)
	{
		std::cerr << ERROR << "Please enter a port between 6660 and 6669." << std::endl;
		return (1);
	}
	if (!argv[2][0] || std::string(argv[2]).find(' ') != std::string::npos)
	{
		std::cerr << ERROR << "Please enter a valid password (at least one character and no spaces)." << std::endl;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (verif_args(argc, argv))
		return (1);
	handle_signal();
	srand(time(NULL));
	Server	server(argv[1], argv[2]);

	std::cout << LOG << "Server started" << std::endl;
	server.run();
	std::cout << LOG << "Server stopped" << std::endl;
	return (0);
}
