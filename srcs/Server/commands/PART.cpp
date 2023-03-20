#include "Server.hpp"

void	Server:_PART(Client* client, std::vector<std::string>& args)
{
	if (args.size() < 3) return;

	std::vector<std::string>	copy(args);
	std::vector<std::string>	channels;
	size_t						pos(0);

	std::cout << args << std::endl;
}
