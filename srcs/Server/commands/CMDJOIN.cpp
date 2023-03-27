#include "Server.hpp"

void	Server::_CMDJOIN(Client* client, std::vector<std::string> & command)
{
	std::vector<std::string>	copy(command);
	std::vector<std::string>	channels;
	Channel						*channel;
	size_t						pos;

	if(command.size() != 2)
	{
		this->sendMessage(client, "[ERROR] : Usage: CMDJOIN <channel>\n");
		return ;
	}
	std::cout << LOG << "CMDJOIN command called by " << client->getName() << std::endl;
	pos = copy[1].find(',');
	while (pos != std::string::npos)
	{
		channels.push_back(copy[1].substr(0, pos));
		copy[1].erase(0, pos + 1);
		pos = copy[1].find(',');
	}
	channels.push_back(copy[1]);
	for (size_t i = 0; i < channels.size(); ++i)
	{
		if (_doesChannelExists(channels[i]) == true)
		{
			channel = _getChannel(channels[i]);
			if (channel->isIn(client->getName()) == false)
			{
				channel->_send_msg_to_all_members(this, channel->getName() + " " + client->getNickname() + " has joined the channel\n");
				this->sendMessage(client, "You have joined the " + channel->getName() + " channel\n");
				channel->addMember(client);
			}
			else
				this->sendMessage(client, "[ERROR] : You are already in this channel\n");
		}
		else
		{
			if(channels[i][0] == '#')
			{
				_channels.push_back(new Channel(channels[i], client));
				this->sendMessage(client, "You have joined the " + channels[i] + " channel\n");
			}
			else
				this->sendMessage(client, "[ERROR] : Channel name must start with '#'\n");
		}
	}
}
