#include "Client.hpp"

Client::Client(const int& sockfd) : 
	_name("default"),
	_sockfd(sockfd), 
	_pass(false)
{
}

Client::~Client(void)
{
}

const bool& Client::isRegister(void) const
{
	return (_is_register);
}

const bool&	Client::getPass(void) const
{
	return (_pass);
}

const int&	Client::getSockfd(void) const
{
	return (_sockfd);
}

const std::string&	Client::getName(void) const
{
	return (_name);
}

void	Client::setName(const std::string& name)
{
	_name = name;
}

void	Client::setPass(const bool& pass)
{
	_pass = pass;
}

void	Client::setRegister(const bool& is_register)
{
	_is_register = is_register;
}
