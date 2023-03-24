#include "Server.hpp"

void	Server::_CMDWHOAMI(Client *client, std::vector<std::string>& args)
{
	if (args.size() != 1)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDWHOAMI.\n");
		return ;
	}
	
	std::string message;

	message =  "---- Who are you ? ----\n";
	message += "Name : " + client->getName() + "\n";
	message += "Nickname : " + client->getNickname() + "\n";
	message += "Channels in : ";
	for (size_t i = 0; i < _channels.size(); ++i)
		if (_channels[i]->isIn(client->getNickname()))
			message += _channels[i]->getName() + " ";
	message += "\n";
	message += "Operator of : ";
	for (size_t i = 0; i < _channels.size(); ++i)
		if (_channels[i]->isOp(client->getNickname()))
			message += _channels[i]->getName() + " ";
	message += "\n";
	message += "------------------------\n";
	this->sendMessage(client, message);
}
