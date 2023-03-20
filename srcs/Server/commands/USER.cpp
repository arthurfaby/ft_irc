#include "Server.hpp"

void	Server::_USER(Client* client, std::vector<std::string>& args)
{
	std::string	username;
	std::string	message;

	std::cout << LOG << "USER command called by " << client->getSockfd() << std::endl;
	if (args.size() != 5)
	{
		this->sendMessage(client, "[ERROR] : Usage : /user <user> <mode> <unused> <realname>\n");
		return ;
	}
	if (client->isRegister())
	{
		this->sendMessage(client, "You may not reregister.\n");
		return ;
	}
	username = args[1];	
	if (username.length() > 9)
	{
		this->sendMessage(client, "\e[91m[ERROR] : Your username is too long (max 9 characters).\n");
		return ;
	}
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->getName() == username)
		{
			this->sendMessage(client, "Username is already in use.\n");
			return ;
		}
	}
	client->setName(username);
	client->setRegister(true);
	this->sendMessage(client, "You are now connected as " + username + ".\n");
}
