#include "Server.hpp"


void	Server::_NICK(Client* client, const std::vector<std::string> &args)
{
		//modifier args[1] quand le parsing sera fais 
		if (args[1].length() > 9)
		{
			this->sendMessage(client, "your nickname is too long/n");
			return;
		}
		for (size_t i = 0; i != _clients.size(); i++)
		{
			std::cout << args[1] << std::endl;
			std::cout << _clients[i]->getNickname() << std::endl;
			if (args[1] == _clients[i]->getNickname())
			{
				this->sendMessage(client, "your nickname is already to use/n");
				return;
			}
		}
		client->setNickname(args[1]);
}
