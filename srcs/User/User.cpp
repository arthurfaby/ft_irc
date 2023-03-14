#include "User.hpp"
#include <iostream>

User::User(void)
{
	std::cout << "Default constructor called" << std::endl;
}

User::User(const User & other)
{
	(void)other;
	std::cout << "Default copy constructor called" << std::endl;
}

User::~User(void)
{
	std::cout << "Default destructor called" << std::endl;
}

User & User::operator=(const User & other)
{
	//copy operations here;
	(void)other;
	std::cout << "Assignment operator called" << std::endl;
	return (*this);
}
