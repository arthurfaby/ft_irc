#include "Server.hpp"

void	Server::_CMDPART(Client* client, std::vector<std::string>& args)
{
	if (args.size() < 3)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDPART <channel>[,...] <:comment>\n");
		return;
	}
	std::cout << "CMDPART command called by " + client->getName() << std::endl;
	if (args[2][0] != ':')
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDPART <channel>[,...] <:comment>\n");
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
			for (size_t j = 0; j < _channels.size(); ++j)
				if (channels[i] == _channels[j]->getName())
					actual = _channels[j];
			if (!actual->isIn(client->getName()))
			{
				this->sendMessage(client, "You are not in the channel " + actual->getName() + ".\n");
				continue ;
			}
			for (size_t j = 0; j < actual->getMembers().size(); ++j)
				this->sendMessage(actual->getMembers()[j], channels[i] + ": " + client->getName() + " has left the channel (" + args[2].substr(1) + ").\n");
			actual->removeMember(client);
		}
	}
}
