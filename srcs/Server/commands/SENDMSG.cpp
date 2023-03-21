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
		this->sendMessage(client, dest + " not found\n");
		return (false);
	}
	else
	{
		for (size_t i = 0; i < this->_clients.size(); i++)
		{
			if (this->_clients[i]->getName().compare(dest) == 0)
				return (true);
		}
		this->sendMessage(client, dest + " not found\n");
		return (false);
	}
}

void	Server::_SENDMSG(Client* client, std::vector<std::string> & args)
{
	if (_check_channel_or_user_exists(args[1], client) == false)
		return ;
	if (args[1].compare(0, 1, "#") == 0)
	{
		for (size_t i = 0; i < this->_channels.size(); i++)
		{
			if (this->_channels[i]->getName().compare(args[1]) == 0)
			{
				for (size_t i = 0; this->_channels[i]->getMembers()[i]->getName().compare(client->getName()) == 0; i++)
				{
					if (i + 1 == this->_members.size())
					{
						this->sendMessage(client, "You are not in the " + args[1] + " channel\n");
						return ;
					}
				}
				this->_channels[i]->_send_msg_to_all_members(args[2] + "\n");
			}
		}
	}
	else
	{
		for (size_t i = 0; i < this->_clients.size(); i++)
		{
			if (this->_clients[i]->getName().compare(args[1]) == 0)
				this->sendMessage(this->_clients[i], args[2] + "\n");
		}
	}
}
