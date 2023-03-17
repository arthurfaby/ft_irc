#include "Channel.hpp"

Channel::Channel(std::string const & name, Client *client)
	:	_name(name),
	:	_client(client)
{
	this->_members.push_back(client);
}

Channel::~Channel(void)
{
}

std::string	Channel::getName(void) const
{
	return (this->_name);
}

const std::vector<Client*>&	Channel::getMembers(void) const
{
	return (this->_members);
}

void	Channel::addMember(const Client *client)
{
	this->_members.push_back(client);
}

void	Channel::removeMember(const Client *client)
{
	this->_members.push_back(client);
}
