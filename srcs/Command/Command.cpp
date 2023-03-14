#include "Command.hpp"
#include <iostream>

Command::Command(void)
{
	std::cout << "Default constructor called" << std::endl;
}

Command::Command(const Command & other)
{
	(void)other;
	std::cout << "Default copy constructor called" << std::endl;
}

Command::~Command(void)
{
	std::cout << "Default destructor called" << std::endl;
}

Command & Command::operator=(const Command & other)
{
	//copy operations here;
	(void)other;
	std::cout << "Assignment operator called" << std::endl;
	return (*this);
}
