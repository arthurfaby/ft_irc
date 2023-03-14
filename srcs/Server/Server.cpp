#include "Server.hpp"
#include <iostream>

Server::Server(void)
{
	std::cout << "Default constructor called" << std::endl;
}

Server::Server(const Server & other)
{
	(void)other;
	std::cout << "Default copy constructor called" << std::endl;
}

Server::~Server(void)
{
	std::cout << "Default destructor called" << std::endl;
}

Server & Server::operator=(const Server & other)
{
	//copy operations here;
	(void)other;
	std::cout << "Assignment operator called" << std::endl;
	return (*this);
}
