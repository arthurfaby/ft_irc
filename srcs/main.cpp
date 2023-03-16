#include "Server.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage error : " << argv[0] << " <port> <password>" << std::endl;
		return (1);
	}
	Server	server(argv[1], argv[2]);

	server.run();
	return (0);
}
