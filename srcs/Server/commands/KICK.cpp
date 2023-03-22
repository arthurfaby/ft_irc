#include "Server.hpp"


void	Server::_KICKUSR(Client* client, std::vector<std::string>& args)
{
	if (args.size() < 3)
	{
		this->sendMessage(client, "usage: KICK <channel>[,...] <user> [<comment>]\n");
		return;
	}

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
		this->sendMessage(client, "User '" + args[2] + "' does not exists.\n");
		return ;
	}
	for (size_t i = 0; i < channels.size(); ++i)
	{
		if (channels[i][0] != '#')
		{
			this->sendMessage(client, "Channel '" + channels[i] + "' is invalid.\n");
			continue;
		}
		if (!_doesChannelExists(channels[i]))
		{
			this->sendMessage(client, "Channel '" + channels[i] + "' does not exists.\n");
			continue;
		}
		else
		{
			actual = _getChannel(channels[i]);
			if (actual->isOp(client->getName()) == false)
			{
				this->sendMessage(client, "you are not operator of this channel\n");
				return;
			}
			if (actual->isIn(args[2]))
			{
				actual->removeMember(_getClient(args[2]));
				this->sendMessage(client, "You kicked " + args[2] + ".\n");
			}
			/* for (size_t j = 0; j < actual->getMembers().size(); ++j) */
				/* this->sendMessage(actual->getMembers()[j], channels[i] + ": " + client->getName() + " has leaved the channel (" + args[2].substr(1) + ").\n"); */
		}
	}
}
