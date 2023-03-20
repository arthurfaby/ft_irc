#include "Server.hpp"


void	Server::_NICK(Client* client, const std::vector<std::string> &args)
{
		std::cout << args[1] << std::endl;
		/*std::cout << args[1].length() << std::endl;*/
		if (args[1].length() > 9)
		{
			this->sendMessage(client, "your nickname is too long/n");
			return;
		}
		for (size_t i = 0; i != _clients.size(); i++)
		{
			if (args[1] == _clients[i]->getNickname())
			{
				this->sendMessage(client, "your nickname is already to use/n");
				return;
			}
		}
		client->setNickname(args[1]);
}
