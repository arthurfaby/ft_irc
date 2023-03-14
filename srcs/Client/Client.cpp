#include "Client.hpp"
#include <iostream>

Client::Client(void)
{
	std::cout << "Default constructor called" << std::endl;
}

Client::Client(const Client & other)
{
	(void)other;
	std::cout << "Default copy constructor called" << std::endl;
}

Client::~Client(void)
{
	std::cout << "Default destructor called" << std::endl;
}

Client & Client::operator=(const Client & other)
{
	//copy operations here;
	(void)other;
	std::cout << "Assignment operator called" << std::endl;
	return (*this);
}
