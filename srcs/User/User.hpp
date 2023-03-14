#ifndef USER_HPP
#define USER_HPP
#include "Client.hpp"

class User : public Client
{

private:

	//private attributes here;

public:

	User(void);
	User(const User & other);
	~User(void);
	User & operator=(const User & other);

};

#endif
