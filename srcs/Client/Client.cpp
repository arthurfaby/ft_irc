#include "Client.hpp"

Client::Client(const int& sockfd) : 
	_name("default"),
	_sockfd(sockfd), 
	_is_op(false)
{
}

Client::~Client(void)
{
}

const int&	Client::getSockfd(void) const
{
	return(_sockfd);
}

const std::string&	Client::getName(void) const
{
	return(_name);
}

const bool&	Client::isOp(void) const
{
	return (_is_op);
}

void	Client::setName(const std::string& name)
{
	_name = name;
}

void	Client::setOp(const bool& is_op)
{
	_is_op = is_op;
}
