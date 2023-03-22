#include "Channel.hpp"

Channel::Channel(std::string const & name, Client *client)
	:	_name(name)
{
	this->_members.push_back(client);
	this->_operators.push_back(client);
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

const std::vector<Client*>&	Channel::getOperators(void) const
{
	return (this->_operators);
}

void	Channel::addMember(Client *client)
{
	this->_members.push_back(client);
}

void	Channel::addOperator(Client *client)
{
	this->_operators.push_back(client);
}

void	Channel::_send_msg_to_all_members(const std::string & msg) const
{
	int	res;
	std::vector<Client*>::iterator	it;
	std::vector<Client*>::iterator	ite;

	for (size_t i = 0; i < this->_members.size(); i++)
	{
		res = send(this->_members[i]->getSockfd(), msg.c_str(), msg.length(), 0);
		if (res == -1)
		{
			(void)res;
			//kick le client ?
		}
	}
}

void	Channel::removeMember(const Client *client)
{
	std::vector<Client*>::iterator	it;
	std::vector<Client*>::iterator	ite;

	it = _members.begin();
	ite = _members.end();
	for (; it != ite; ++it)
	{
		if (*it == client)
		{
			std::cout << client->getName() << " has left the channel." << std::endl;
			_members.erase(it);
		}
	}
	it = _operators.begin();
	ite = _operators.end();
	for (; it != ite; ++it)
	{
		if (*it == client)
		{
			_operators.erase(it);
			return ;
		}
	}
}

bool	Channel::isIn(const std::string& name) const
{
	for (size_t i = 0; i < _members.size(); ++i)
		if (_members[i]->getName() == name)
			return (true);
	return (false);
}

bool	Channel::isOp(const std::string& name) const
{
	for (size_t i = 0; i < _operators.size(); ++i)
		if (_operators[i]->getName() == name)
			return (true);
	return (false);
}
