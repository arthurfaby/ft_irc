#include "Server.hpp"

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
