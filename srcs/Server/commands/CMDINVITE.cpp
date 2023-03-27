#include "Server.hpp"

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
