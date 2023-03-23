#include "Client.hpp"

Client::Client(const int& sockfd) : 
	_name("default"),
	_nickname(_name),
	_buffer(""),
	_sockfd(sockfd), 
	_pass(false),
	_is_register(false)
{
}

Client::~Client(void)
{
}

const bool& Client::isRegister(void) const
{
	return (_is_register);
}

const std::string&	Client::getBuffer(void) const
{
	return (_buffer);
}

const bool&	Client::getPass(void) const
{
	return (_pass);
}

const int&	Client::getSockfd(void) const
{
	return (_sockfd);
}

const std::string&	Client::getNickname(void)const
{
	return(_nickname);
}

const std::string&	Client::getName(void) const
{
	return (_name);
}

void	Client::setName(const std::string& name)
{
	_name = name;
}

void	Client::resetBuffer(void)
{
	_buffer = "";
}

void	Client::addToBuffer(const std::string& add)
{
	_buffer += add;
}

void	Client::setPass(const bool& pass)
{
	_pass = pass;
}

void	Client::setRegister(const bool& is_register)
{
	_is_register = is_register;
}

void	Client::setNickname(const std::string& nickname)
{
	_nickname = nickname;
}
