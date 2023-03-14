#ifndef USER_HPP
#define USER_HPP

class User
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
