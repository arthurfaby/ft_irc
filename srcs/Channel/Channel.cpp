#include "Channel.hpp"
#include <iostream>

Channel::Channel(void)
{
	std::cout << "Default constructor called" << std::endl;
}

Channel::Channel(const Channel & other)
{
	(void)other;
	std::cout << "Default copy constructor called" << std::endl;
}

Channel::~Channel(void)
{
	std::cout << "Default destructor called" << std::endl;
}

Channel & Channel::operator=(const Channel & other)
{
	//copy operations here;
	(void)other;
	std::cout << "Assignment operator called" << std::endl;
	return (*this);
}
