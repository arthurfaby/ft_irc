#ifndef OPERATOR_HPP
#define OPERATOR_HPP
#include "Client.hpp"

class Operator : public Client
{

private:

	//private attributes here;

public:

	Operator(void);
	Operator(const Operator & other);
	~Operator(void);
	Operator & operator=(const Operator & other);

};

#endif
