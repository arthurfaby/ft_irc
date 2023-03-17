#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{

public:

	// Constructors
	Client(const int& sockfd);
	~Client(void);


	// Setters
	void			setName(const std::string& name);
	void			setOp(const bool& is_op);


	// Getters
	const std::string&		getName(void) const;
	const int&				getSockfd(void) const;
	const bool&				isOp(void) const;

private:

	std::string				_name;			// Unique nickname of the client (max 9 characters)
	const int				_sockfd;		// fd which referred to the client socket
	bool					_is_op;			// true if client is an operator, false otherwise

};

#endif /* !CLIENT_HPP */
