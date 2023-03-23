#include "Server.hpp"

void	Server::_CMDNAMES(Client* client, std::vector<std::string> & args)
{
	std::vector<std::string>	names;
	std::vector<std::string>	copy(args);
	std::vector<std::string>	channels;
	std::string					res;
	size_t						pos;
	size_t						j = 0;
	size_t						k = 0;
	size_t						l = 1;

	if (args.size() != 2)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDNAMES <channel>[,...]\n");
		return ;
	}
	pos = copy[1].find(',');
	while (pos != std::string::npos)
	{
		channels.push_back(copy[1].substr(0, pos));
		copy[1].erase(0, pos + 1);
		pos = copy[1].find(',');
	}
	channels.push_back(copy[1]);

	std::cout << LOG << "CMDNAMES command called by " + client->getName() << std::endl;
	for (size_t i = 0; i < channels.size(); ++i)
	{
		for (; j < this->_channels.size(); ++j)
		{
			if (_doesChannelExists(channels[i]) == false)
			{
				this->sendMessage(client, "[ERROR] : Channel " + channels[i] + " does not exist\n");
				break ;
			}
			if (this->_channels[j]->getName().compare(channels[i]) == 0)
			{
				if (this->_channels[j]->isIn(client->getName()) == false)
				{
					this->sendMessage(client, "[ERROR] : You are not in the " + channels[i] + " channel\n");
					break ;
				}
				for (; k < this->_channels[j]->getMembers().size(); ++k)
					names.push_back(this->_channels[j]->getMembers()[k]->getName());
				res = names[0];
				for (; l < names.size(); ++l)
					res.append(" " + names[l]);
				this->sendMessage(client, "Users in " + channels[i] + ": " + res + "\n");
				break ;
			}
		}
		j = 0;
		k = 0;
		l = 1;
		names.clear();
	}
}
