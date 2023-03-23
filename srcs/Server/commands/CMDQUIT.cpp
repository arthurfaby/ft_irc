#include "Server.hpp"

void	Server::_CMDQUIT(Client* client, std::vector<std::string>& args)
{
	std::string	username;

	if (args.size() < 1)
	{
		this->sendMessage(client, "[ERROR] : Usage : /CMDQUIT [<message>]\n");
		return ;
	}
	std::cout << LOG << "CMDQUIT command called by " << client->getName() << std::endl;
	this->sendMessage(client, "You are disconnected.\n");
	this->_disconnect_client(client);
}
