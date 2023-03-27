#include "Server.hpp"

void	Server::_CMDJOIN(Client* client, std::vector<std::string> & command)
{
	std::vector<std::string>	copy(command);
	std::vector<std::string>	channels;
	Channel						*channel;
	size_t						pos;

	if(command.size() != 2)
	{
		this->sendMessage(client, "[ERROR] : Usage: CMDJOIN <channel>\n");
		return ;
	}
	std::cout << LOG << "CMDJOIN command called by " << client->getName() << std::endl;
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
			channel = _getChannel(channels[i]);
			if (channel->isIn(client->getName()) == false)
			{
				channel->_send_msg_to_all_members(this, channel->getName() + " " + client->getNickname() + " has joined the channel\n");
				this->sendMessage(client, "You have joined the " + channel->getName() + " channel\n");
				channel->addMember(client);
			}
			else
				this->sendMessage(client, "[ERROR] : You are already in this channel\n");
		}
		else
		{
			if(channels[i][0] == '#')
			{
				_channels.push_back(new Channel(channels[i], client));
				this->sendMessage(client, "You have joined the " + channels[i] + " channel\n");
			}
			else
				this->sendMessage(client, "[ERROR] : Channel name must start with '#'\n");
		}
	}
}

void	Server::_CMDINVITE(Client* client, std::vector<std::string> & command)
{
	std::string	invit;
	Client	*dest;
	Channel	*channel;

	if (command.size() != 3)
	{
		this->sendMessage(client, "[ERROR] : Usage: CMDINVITE <nick> <channel>\n");
		return ;
	}
	std::cout << LOG << "CMDINVITE command called by " << client->getName() << std::endl;
	dest = _getClient(command[1]);
	if (!dest)
	{
		this->sendMessage(client, "[ERROR] : Client not found\n");
		return;
	}
	if (dest == client)
	{
		this->sendMessage(client, "[ERROR] : You can't invite yourself.\n");
		return ;
	}
	channel = _getChannel(command[2]);
	if (!channel)
	{
		this->sendMessage(client, "[ERROR] : Channel not found\n");
		return;
	}
	if (!channel->isIn(client->getNickname()))
	{
		this->sendMessage(client, "[ERROR] : You can't invite to a channel if you're not in it.\n");
		return ;
	}
	if (channel->isOp(client->getNickname()) == true)
	{
		invit = client->getNickname();
		invit += " invites you in the channel ";
		invit += command[2];	
		invit += ".\nDo '/CMDJOIN ";
		invit += command[2];
		invit += "' if you want to join the channel.\n";
		this->sendMessage(dest, invit);
		this->sendMessage(client, "You just invited " + command[1] + " to the channel " + command[2] + ".\n");
		return ;
	}
	this->sendMessage(client, "[ERROR] : You are not operator of this channel\n");
}

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
	if (args[1][0] == '#' || args[1][0] == ':')
	{
		this->sendMessage(client, "[ERROR] : Your nickname can't begin with '#' or ':'.\n");
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

void	Server::_CMDPASS(Client* client, std::vector<std::string> & args)
{
	if (args.size() != 2)
	{
		this->sendMessage(client, "[ERROR] Usage: CMDPASS <password>\n");
		return ;
	}
	std::cout << LOG << "CMDPASS command called by " << client->getSockfd() << std::endl;
	if (client->getPass() == true)
		this->sendMessage(client, "[ERROR] : Password has already been entered\n");
	else if(args[1] == _password)
	{
		client->setPass(true);
		this->sendMessage(client, "Correct password, please register using <cmduser>\n");
	}
	else
		this->sendMessage(client, "[ERROR] : Wrong password\n");
}

void	Server::_CMDMODE(Client* client, std::vector<std::string> & command)
{
	Channel *channel;

	if (command.size() != 4)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDMODE {-,+}o <nick> <channel>\n");
		return;
	}
	std::cout << LOG << "CMDMODE command called by " << client->getSockfd() << std::endl;
	if (command[1] != "-o" && command[1] != "+o")
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDMODE {-,+}o <nick> <channel>\n");
		return;
	}
	if (_doesClientExists(command[2]) == false)
	{
		this->sendMessage(client, "[ERROR] : Client doesn't exist\n");
		return;
	}
	if (_doesChannelExists(command[3]) == false)
	{
		this->sendMessage(client, "[ERROR] : Channel doesn't exist\n");
		return;
	}
	channel = _getChannel(command[3]);
	if (channel->isOp(client->getName()) == false)
	{
		this->sendMessage(client, "[ERROR] : You are not operator\n");
		return;	
	} 
	if (channel->isIn(command[2]) == false)
	{
		this->sendMessage(client, "[ERROR] : Client is not in channel\n");
		return;
	}
	if (channel->isOp(command[2]) == true && command[1] == "+o")
	{
		this->sendMessage(client, "[ERROR] : Client is already operator\n");
		return;
	}
	if (command[1] == "+o")
	{
		channel->addOperator(_getClient(command[2]));
		this->sendMessage(client, command[2] + " is now an operator in channel " + command[3] + ".\n");
		this->sendMessage(_getClient(command[2]), "You are now an operator in channel " + command[3] + ".\n");
	}
	if (command[1] == "-o")
	{
		channel->removeOperator(_getClient(command[2]));
		this->sendMessage(client, command[2] + " is no longer an operator in channel " + command[3] + ".\n");
		this->sendMessage(_getClient(command[2]), "You are no longer an operator in channel " + command[3] + ".\n");
	}
}
