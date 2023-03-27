#include "Server.hpp"

void	Server::_CMDUSER(Client* client, std::vector<std::string>& args)
{
	std::string	username;
	std::string	message;

	if (args.size() != 2)
	{
		this->sendMessage(client, "[ERROR] : Usage : cmduser <user>\n");
		return ;
	}
	std::cout << LOG << "CMDUSER command called by " << client->getSockfd() << std::endl;
	if (client->isRegister())
	{
		this->sendMessage(client, "[ERROR] : You may not reregister.\n");
		return ;
	}
	username = args[1];	
	if (username.length() > 9)
	{
		this->sendMessage(client, "[ERROR] : This username is too long (max 9 characters).\n");
		return ;
	}
	if (username[0] == '#' || username[0] == ':')
	{
		this->sendMessage(client, "[ERROR] : Your username can't begin with '#' or ':'.\n");
		return ;
	}
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->getName() == username || _clients[i]->getNickname() == username)
		{
			this->sendMessage(client, "[ERROR] : This username is already used.\n");
			return ;
		}
	}
	client->setNickname(username);
	client->setName(username);
	client->setRegister(true);
	this->sendMessage(client, "You are now connected as " + username + ".\n");
}
