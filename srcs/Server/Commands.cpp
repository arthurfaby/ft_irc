#include "Server.hpp"

void	Server::_JOIN(Client* client, std::vector<std::string> & command)
{
		for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		if (command[1] == (*it)->getName())
		{
			(*it)->addMember(client);
			//msg a tous les membre du channel;
			return;
		}
	_channels.push_back(new Channel(command[1], client));
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		std::cout << (*it)->getName() << std::endl;
}

void	Server::_INVITE(Client* client, std::vector<std::string> & command)
{
	std::vector<Client *>::const_iterator itsOperator;
	std::vector<Client *>::const_iterator iteOperator;
	std::vector<Client *>::iterator itsClient = _clients.begin();
	std::vector<Channel *>::iterator it = _channels.begin();
	std::string	invit;


	for (; it != _channels.end(); it++)
		if (command[1] == (*it)->getName())
		{
			itsOperator = (*it)->getOperators().begin();
			iteOperator = (*it)->getOperators().end();
			break;
		}
	if (it == _channels.end())
		this->sendMessage(client, "Channel not found\n");
	for (; itsClient != _clients.end(); itsClient++) 
		if (command[2] == (*itsClient)->getName())
			break;
	if (itsClient == _clients.end())
		this->sendMessage(client, "Client not found\n");
	for (; itsOperator != iteOperator; itsOperator++)
		if (client->getName() == (*itsOperator)->getName())
		{
			invit = client->getName();
			invit += " invites you in the channel ";
			invit += command[1];	
			invit += " /join ";
			invit += command[1];	
			this->sendMessage((*itsClient), invit);
			return ;
		}
	this->sendMessage(client, "you are not operator of this channel\n");
}

void	Server::_NICK(Client* client, std::vector<std::string> &args)
{
		std::cout << args[1] << std::endl;
		/*std::cout << args[1].length() << std::endl;*/
		if (args[1].length() > 9)
		{
			this->sendMessage(client, "your nickname is too long\n");
			return;
		}
		for (size_t i = 0; i != _clients.size(); i++)
		{
			if (args[1] == _clients[i]->getNickname())
			{
				this->sendMessage(client, "your nickname is already to use\n");
				return;
			}
		}
		client->setNickname(args[1]);
}

void	Server::_PASS(Client* client, std::vector<std::string> & args)
{
	if(args[1] == _password)
		client->setPass(true);
}
