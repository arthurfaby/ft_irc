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
	void			setPass(const bool& pass);


	// Getters
	const bool&				getPass(void) const;
	const std::string&		getName(void) const;
	const int&				getSockfd(void) const;

private:

	std::string				_name;		// Unique nickname of the client (max 9 characters)
	const int				_sockfd;	// fd which referred to the client socket
	bool					_pass;		// true if client entererd password, false otherwise

};

#endif /* !CLIENT_HPP */
