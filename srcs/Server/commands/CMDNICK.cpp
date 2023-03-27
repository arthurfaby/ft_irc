#include "Server.hpp"

void	Server::_CMDNICK(Client* client, std::vector<std::string> &args)
{
	if (args.size() != 2)
	{
		this->sendMessage(client, "[ERROR] : Usage: CMDNICK <nick>\n");
		return ;
	}
	std::cout << LOG << "CMDNICK command called by " << client->getName() << std::endl;
	if (args[1].length() > 9)
	{
		this->sendMessage(client, "[ERROR] : This nickname is too long (max 9 characters).\n");
		return;
	}
	if (args[1][0] == '#')
	{
		this->sendMessage(client, "[ERROR] : Your nickname can't begin with '#'.\n");
		return ;
	}
	for (size_t i = 0; i != _clients.size(); i++)
	{
		if (args[1] == _clients[i]->getNickname())
		{
			this->sendMessage(client, "[ERROR] : This nickname is already used\n");
			return;
		}
	}
	this->sendMessage(client, "Your nickname is now : " + args[1] + ".\n");
	client->setNickname(args[1]);
}
