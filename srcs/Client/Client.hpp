#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{

public:

	// Constructors
	Client(const int& sockfd);
	~Client(void);

	void			addToBuffer(const std::string& add);
	void			resetBuffer(void);

	// Setters
	void			setName(const std::string& name);
	void			setPass(const bool& pass);
	void			setRegister(const bool& is_register);
	void			setNickname(const std::string& nickname);


	// Getters
	const bool&				getPass(void) const;
	const std::string&		getName(void) const;
	const int&				getSockfd(void) const;
	const bool&				isRegister(void) const;
	const std::string&		getNickname(void)const;
	const std::string&		getBuffer(void) const;

private:
	std::string				_name;		// Unique name of the client (max 9 characters)
	std::string				_nickname;
	std::string				_buffer;
	const int				_sockfd;	// fd which referred to the client socket
	bool					_pass;		// true if client entererd password, false otherwise
	bool					_is_register;	// true if client used 'USER' command to register

};

#endif /* !CLIENT_HPP */
