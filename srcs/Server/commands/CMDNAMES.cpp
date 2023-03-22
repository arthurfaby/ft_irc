#include "Server.hpp"

void	Server::_CMDNAMES(Client* client, std::vector<std::string> & args)
{
	//verifier si l'utilisateur qui appelle names est dans le channel
	std::vector<std::string>	names;
	std::string					res;

	if (args.size() < 2)
	{
		this->sendMessage(client, "Usage: /listnames <channel>\n");
		return ;
	}
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i]->getName().compare(args[1]) == 0)
		{
			for (size_t j = 0; j < this->_channels[i]->getMembers().size(); j++)
				names.push_back(this->_channels[i]->getMembers()[j]->getNickname());
			res = names[0];
			for (size_t i = 1; i < names.size(); i++)
				res.append(" " + names[i]);
			this->sendMessage(client, "Users in " + args[1] + ": " + res + "\n");
			return ;
		}
	}
	this->sendMessage(client, "Channel " + args[1] + " does not exist\n");
}
