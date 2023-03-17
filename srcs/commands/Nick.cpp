#include "Server.hpp"


void	Server::_NICK(Client* client, const std::vector<std::string> &args)
{
		if (args[0].length() > 9)
		{
			this->sendMessage(client, "your nickname is too long");
			return;
		}
		for (size_t i = 0; i != _clients.size(); i++)
		{
			if (args[0] == _clients[i]->getNickname())
			{
				this->sendMessage(client, "your nickname is already to use");
				return;
			}
		}
		client->setNickname(args[0]);
}
