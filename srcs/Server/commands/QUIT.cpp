#include "Server.hpp"

void	Server::_QUIT(Client* client, std::vector<std::string>& args)
{
	std::string	username;

	std::cout << LOG << "QUIT command called by " << client->getSockfd() << std::endl;
	for (size_t i = 0; i < args.size() ; ++i)
		std::cout << "QUIT : " << i << " : " << args[i] << std::endl;
	if (args.size() < 1)
	{
		this->sendMessage(client, "[ERROR] : Usage : /quit [<message>]\n");
		return ;
	}
	this->sendMessage(client, "You are disconnected.\n");
	this->_disconnect_client(client);
}
