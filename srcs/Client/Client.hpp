#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>

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
	void			setBoard(const std::string& sign, size_t x, size_t y);

	// Getters
	const bool&										getPass(void) const;
	const std::string&								getName(void) const;
	const int&										getSockfd(void) const;
	const bool&										isRegister(void) const;
	const std::string&								getNickname(void)const;
	const std::string&								getBuffer(void) const;
	const std::vector<std::vector<std::string> >&	getBoard(void) const;

	// Methods
	void											_init_board(void);

private:

	std::string								_name;		// Unique name of the client (max 9 characters)
	std::string								_nickname;
	std::string								_buffer;
	std::vector<std::vector<std::string> >	_board;		// Tic tac toe board unique to this client
	const int								_sockfd;	// fd which referred to the client socket
	bool									_pass;		// true if client entererd password, false otherwise
	bool					_is_register;	// true if client used 'USER' command to register


};

#endif /* !CLIENT_HPP */
