#include "Operator.hpp"
#include <iostream>

Operator::Operator(void)
{
	std::cout << "Default constructor called" << std::endl;
}

Operator::Operator(const Operator & other)
{
	(void)other;
	std::cout << "Default copy constructor called" << std::endl;
}

Operator::~Operator(void)
{
	std::cout << "Default destructor called" << std::endl;
}

Operator & Operator::operator=(const Operator & other)
{
	//copy operations here;
	(void)other;
	std::cout << "Assignment operator called" << std::endl;
	return (*this);
}
