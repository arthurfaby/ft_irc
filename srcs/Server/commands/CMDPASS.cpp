#include "Server.hpp"

void	Server::_CMDPASS(Client* client, std::vector<std::string> & args)
{
	if (args.size() != 2)
	{
		this->sendMessage(client, "[ERROR] Usage: CMDPASS <password>\n");
		return ;
	}
	std::cout << LOG << "CMDPASS command called by " << client->getSockfd() << std::endl;
	if (client->getPass() == true)
		this->sendMessage(client, "[ERROR] : Password has already been entered\n");
	else if(args[1] == _password)
	{
		client->setPass(true);
		this->sendMessage(client, "Correct password, please register using <cmduser>\n");
	}
	else
		this->sendMessage(client, "[ERROR] : Wrong password\n");
}
