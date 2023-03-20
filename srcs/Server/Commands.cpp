#include "Server.hpp"

void	Server::_JOIN(Client* client, const std::vector<std::string> & command)
{
		for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		if (command[1] == (*it)->getName())
		{
			(*it)->addMember(client);
			return;
		}
	_channels.push_back(new Channel(command[1], client));
}

void	Server::_INVITE(Client* client, const std::vector<std::string> & command)
{
	(void)client;
	(void)command;	
}

void	Server::_NICK(Client* client, const std::vector<std::string> &args)
{
		std::cout << args[1] << std::endl;
		/*std::cout << args[1].length() << std::endl;*/
		if (args[1].length() > 9)
		{
			this->sendMessage(client, "your nickname is too long/n");
			return;
		}
		for (size_t i = 0; i != _clients.size(); i++)
		{
			if (args[1] == _clients[i]->getNickname())
			{
				this->sendMessage(client, "your nickname is already to use/n");
				return;
			}
		}
		client->setNickname(args[1]);
}

void	Server::_PASS(Client* client, const std::vector<std::string> & args)
{
	if(args[1] == _password)
		client->setPass(true);
}
