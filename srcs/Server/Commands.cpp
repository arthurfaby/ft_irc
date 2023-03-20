#include "Server.hpp"

void	Server::_JOIN(Client* client, std::vector<std::string> & command)
{
	std::vector<std::string>	copy(command);
	std::vector<std::string>	channels;
	size_t						pos;

	if(command.size() != 2)
			this->sendMessage(client, "No channel joined. Try /join #<channel>\n");
	pos = copy[1].find(',');
	while (pos != std::string::npos)
	{
		channels.push_back(copy[1].substr(0, pos));
		copy[1].erase(0, pos + 1);
		pos = copy[1].find(',');
	}
	channels.push_back(copy[1]);

	
	for (size_t i = 0; i < channels.size(); ++i)
	{
		for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		{
			if (channels[i] == (*it)->getName())
			{
				(*it)->addMember(client);
				//msg a tous les membre du channel;
				return;
			}
			if(channels[i][0] != '#')
				this->sendMessage(client, "No channel joined. Try /join #<channel>\n");
		}
			
		_channels.push_back(new Channel(command[1], client));
	}
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

	std::cout << command.size() << std::endl;
	if (command.size() != 3)
	{
		this->sendMessage(client, "usage: INVITE <nick> <channel>");
	}
	for (; itsClient != _clients.end(); itsClient++) 
		if (command[1] == (*itsClient)->getNickname())
			break;
	if (itsClient == _clients.end())
	{
		this->sendMessage(client, "Client not found\n");
		return;
	}

	for (; it != _channels.end(); it++)
		if (command[2] == (*it)->getNickname())
		{
			itsOperator = (*it)->getOperators().begin();
			iteOperator = (*it)->getOperators().end();
			break;
		}
	if (it == _channels.end())
	{
		this->sendMessage(client, "Channel not found\n");
		return;
	}
		for (; itsOperator != iteOperator; itsOperator++)
		if (client->getNickname() == (*itsOperator)->getNickname())
		{
			invit = client->getNickname();
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

void	Server::_MODE(Client* client, std::vector<std::string> & command)
{
	if (command.size() != 5)
		this->sendMessage("usage: mode -o <nick> <channel>");
	if(command[1] != "-o")
		this->sendMessage("usage: mode -o <nick> <channel>");
	 

}


