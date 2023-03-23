#include "Server.hpp"

void	Server::_CMDJOIN(Client* client, std::vector<std::string> & command)
{
	std::vector<std::string>	copy(command);
	std::vector<std::string>	channels;
	size_t						pos;

	if(command.size() < 2)
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
		if (_doesChannelExists(channels[i]) == true)
		{
			Channel	*channel = _getChannel(channels[i]);
			if (channel->isIn(client->getName()) == false)
			{
				channel->addMember(client);
			}
			else
				this->sendMessage(client, "you are already in this channel\n");
		}
		else
		{
			if(channels[i][0] == '#')
				_channels.push_back(new Channel(channels[i], client));
			else
				this->sendMessage(client, "No channel joined. Try /join #<channel>\n");
		}
	}
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		std::cout << (*it)->getName() << std::endl;
}

void	Server::_CMDINVITE(Client* client, std::vector<std::string> & command)
{
	std::string	invit;
	Client	*dest;
	Channel	*channel;

	if (command.size() != 3)
	{
		this->sendMessage(client, "usage: INVITE <nick> <channel>");
	}
	dest = _getClient(command[1]);
	if (!client)
	{
		this->sendMessage(client, "Client not found\n");
		return;
	}
	channel = _getChannel(command[1]);
	if (!channel)
	{
		this->sendMessage(client, "Channel not found\n");
		return;
	}
	if (channel->isOp(client->getName()) == true)
	{
		invit = client->getNickname();
		invit += " invites you in the channel ";
		invit += command[1];	
		invit += " /join ";
		invit += command[1];	
		this->sendMessage(dest, invit);
		return ;
	}
	this->sendMessage(client, "you are not operator of this channel\n");
}

void	Server::_CMDNICK(Client* client, std::vector<std::string> &args)
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

void	Server::_CMDPASS(Client* client, std::vector<std::string> & args)
{
	if(args[1] == _password)
		client->setPass(true);
}

void	Server::_CMDMODE(Client* client, std::vector<std::string> & command)
{
	Channel *channel;

	if (command.size() != 4)
	{
		this->sendMessage(client, "usage: mode -o <nick> <channel>\n");
		return;
	}
	if(command[1] != "-o")
	{
		this->sendMessage(client, "usage: mode -o <nick> <channel>\n");
		return;
	}
	if (_doesClientExists(command[2]) == false)
	{
		this->sendMessage(client, "client doesn't exist\n");
		return;
	}
	if (_doesChannelExists(command[3]) == false)
	{
		this->sendMessage(client, "channel	doesn't exist\n");
		return;
	}
	channel = _getChannel(command[3]);
	if (channel->isOp(client->getName()) == false)
	{
		this->sendMessage(client, "you are not operator\n");
		return;	
	} 
	if (channel->isIn(command[2]) == false)
	{
		this->sendMessage(client, "client is not in channel\n");
		return;
	}
	if (channel->isOp(command[2]) == true)
	{
		this->sendMessage(client, "client is already operator\n");
		return;
	}
	channel->addOperator(_getClient(command[2]));
}
