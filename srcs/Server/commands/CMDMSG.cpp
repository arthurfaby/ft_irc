#include "Server.hpp"

bool	Server::_check_channel_or_user_exists(const std::string dest, Client *client)
{
	if (dest.compare(0, 1, "#") == 0)
	{
		for (size_t i = 0; i < this->_channels.size(); i++)
		{
			if (this->_channels[i]->getName().compare(dest) == 0)
				return (true);
		}
		this->sendMessage(client, "[ERROR] : " + dest + " not found\n");
		return (false);
	}
	else
	{
		for (size_t i = 0; i < this->_clients.size(); i++)
		{
			if (this->_clients[i]->getName().compare(dest) == 0)
				return (true);
		}
		this->sendMessage(client, "[ERROR] : " + dest + " not found\n");
		return (false);
	}
}

void	Server::_CMDMSG(Client* client, std::vector<std::string> & args)
{
	if (args.size() < 3)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDMSG <nickname>/<channel> <:message>\n");
		return ;
	}
	if (args[2][0] != ':' || args[2][1] == '\0')
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDMSG <nickname>/<channel> <:message>\n");
		return ;
	}
	std::cout << LOG << "CMDMSG command called by " + client->getName() << std::endl;
	if (_check_channel_or_user_exists(args[1], client) == false)
		return ;
	if (args[2].size() == 1)
	{
		this->sendMessage(client, "[ERROR] : Message can not be empty\n");
		return ;
	}
	if (args[1].compare(0, 1, "#") == 0)
	{
		for (size_t i = 0; i < this->_channels.size(); i++)
		{
			if (this->_channels[i]->isIn(client->getNickname()) == false)
			{
				this->sendMessage(client, "[ERROR] : You are not in the " + args[1] + " channel\n");
				return ;
			}
			if (this->_channels[i]->getName().compare(args[1]) == 0)
				this->_channels[i]->_send_msg_to_all_members(this, this->_channels[i]->getName() + " " + client->getNickname() + ": " + args[2].substr(1) + "\n");
		}
	}
	else
	{
		for (size_t i = 0; i < this->_clients.size(); i++)
		{
			if (args[1].compare(client->getNickname()) == 0)
			{
				this->sendMessage(client, "[ERROR] : You can not send yourself a message\n");
				return ;
			}
			if (this->_clients[i]->getNickname().compare(args[1]) == 0)
			{
				this->sendMessage(this->_clients[i], client->getNickname() + ": " + args[2].substr(1) + "\n");
				this->sendMessage(client, "You just sent '" + args[2].substr(1) + "' to " + _clients[i]->getNickname() + ".\n");
				return ;
			}
		}
	}
}
