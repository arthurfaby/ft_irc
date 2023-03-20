#include "Server.hpp"

void	Server::_USER(Client* client, std::vector<std::string>& args)
{
	std::string	username;

	std::cout << LOG << "USER command called by " << client->getSockfd() << std::endl;
	if (client->isRegister())
	{
		this->sendMessage(client, "You may not reregister.\n");
		return ;
	}
	username = args[1];	
	if (username.length() > 9)
	{
		this->sendMessage(client, "Your username is too long (max 9 characters).\n");
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
	this->sendMessage(client, "You are now connected as ");
	this->sendMessage(client, username);
	this->sendMessage(client, ".\n");
}
