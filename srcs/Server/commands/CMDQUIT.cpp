#include "Server.hpp"

void	Server::_CMDQUIT(Client* client, std::vector<std::string>& args)
{
	if (args.size() < 2)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDQUIT <:message>\n");
		return ;
	}
	if (args[1][0] != ':' || args[1][1] == '\0')
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDQUIT <:message>\n");
		return ;
	}
	std::cout << LOG << "CMDQUIT command called by " << client->getName() << std::endl;
	this->sendMessage(client, "You are disconnected.\n");
	this->_disconnect_client(client);
}
