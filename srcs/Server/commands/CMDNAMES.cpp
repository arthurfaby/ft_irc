#include "Server.hpp"

void	Server::_CMDNAMES(Client* client, std::vector<std::string> & args)
{
	//gerer plusieurs channel : #42,#43,#44...
	std::vector<std::string>	names;
	std::string					res;

	if (args.size() != 2)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDNAMES <channel>\n");
		return ;
	}
	std::cout << LOG << "CMDNAMES command called by " + client->getNickname() << std::endl;
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i]->getName().compare(args[1]) == 0)
		{
			if (this->_channels[i]->isIn(client->getNickname()) == false)
			{
				this->sendMessage(client, "[ERROR] : You are not in the " + args[1] + " channel\n");
				return ;
			}
			for (size_t j = 0; j < this->_channels[i]->getMembers().size(); j++)
				names.push_back(this->_channels[i]->getMembers()[j]->getNickname());
			res = names[0];
			for (size_t i = 1; i < names.size(); i++)
				res.append(" " + names[i]);
			this->sendMessage(client, "Users in " + args[1] + ": " + res + "\n");
			return ;
		}
	}
	this->sendMessage(client, "[ERROR] : Channel " + args[1] + " does not exist\n");
}
