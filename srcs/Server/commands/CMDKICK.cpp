#include "Server.hpp"

void	Server::_CMDKICK(Client* client, std::vector<std::string>& args)
{
	if (args.size() < 4)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDKICK <channel>[,...] <user> <:comment>\n");
		return;
	}
	if (args[3][0] != ':' || args[3][1] == '\0')
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDKICK <channel>[,...] <user> <:comment>\n");
		return ;
	}
	std::cout << LOG << "CMDKICK command called by " + client->getName() << std::endl;
	std::vector<std::string>	copy(args);
	std::vector<std::string>	channels;
	Channel						*actual;
	size_t						pos;

	pos = copy[1].find(',');
	while (pos != std::string::npos)
	{
		channels.push_back(copy[1].substr(0, pos));
		copy[1].erase(0, pos + 1);
		pos = copy[1].find(',');
	}
	channels.push_back(copy[1]);

	if (!_doesClientExists(args[2]))
	{
		this->sendMessage(client, "[ERROR] : User '" + args[2] + "' does not exists.\n");
		return ;
	}
	for (size_t i = 0; i < channels.size(); ++i)
	{
		if (channels[i][0] != '#')
		{
			this->sendMessage(client, "[ERROR] : Channel '" + channels[i] + "' is invalid.\n");
			continue;
		}
		if (!_doesChannelExists(channels[i]))
		{
			this->sendMessage(client, "[ERROR] : Channel '" + channels[i] + "' does not exists.\n");
			continue;
		}
		else
		{
			actual = _getChannel(channels[i]);
			if (actual->isOp(client->getNickname()) == false)
			{
				this->sendMessage(client, "[ERROR] : You are not operator of this channel\n");
				continue;
			}
			if (actual->isIn(args[2]))
			{
				actual->removeMember(_getClient(args[2]));
				this->sendMessage(client, "You kicked " + args[2] + ".\n");
				this->sendMessage(this->_getClient(args[2]), "You have been kicked from " + actual->getName() + " by " + client->getNickname() + ".\n");
				this->sendMessage(this->_getClient(args[2]), "Reason : " + args[3].substr(1) + ".\n");
				for (size_t j = 0; j < actual->getMembers().size(); ++j)
					if (actual->getMembers()[j] != client)
						this->sendMessage(actual->getMembers()[j], channels[i] + ": " + client->getNickname() + " has been kicked by " + client->getNickname() + ".\n");

			}
			else
			{
				this->sendMessage(client, "User " + args[2] + " is not in channel (" + actual->getName() + ").\n");
				continue;
			}
		}
	}
}
