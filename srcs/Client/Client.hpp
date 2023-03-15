#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"
#include "Channel.hpp"

class Client
{

public:

	// Constructors
	Client(void);
	Client(const Client & other);
	~Client(void);
	Client & operator=(const Client & other);

	// Setters
	void			setName(const std::string& name);
	void			setChannel(const Channel& channel);
	void			setOp(const bool& is_op);

	// Getters
	std::string		getname(void) const;
	const Server&	getIntroducer(void) const;
	const int		getSockfd(void) const;
	Channel*		getChannel(void) const;
	bool			isOp(void) const;
	bool			isInChannel(void) const;

	// Methods
	bool			joinChannel(Channel* channel);
	bool			sendMessageToClient(const Client& other);
	bool			sendMessageToChannel(const Channel& other);
	bool			quitChannel(Channel* channel);

private:

	std::string				_name;			// Unique nickname of the client (max 9 characters)
	const Server&			_introducer;	// Server which introduced the client
	const int				_sockfd;		// fd which referred to the client socket
	std::vector<Channel*>	_channels;		// Channel in which the client is (or NULL if not)
	bool					_is_op;			// true if client is an operator, false otherwise


};

#endif /* !CLIENT_HPP */
