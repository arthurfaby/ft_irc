#include "Client.hpp"

/*Client::Client(void) : 
_introducer(NULL)
_sockfd(0), 
_is_op(false),
_name("default"),
_channels(NULL)

{}*/

Client::Client(const Server& introducer, const int& sockfd) : 
_name("default"),
_introducer(introducer), 
_sockfd(sockfd), 
_channels(std::vector<Channel *>()),
_is_op(false)
{}

Client::Client(const Client & other) :
_name(other._name),
_introducer(other._introducer),
_sockfd(other._sockfd),
_channels(other._channels),
_is_op(other._is_op)
{}

Client::~Client(void)
{}

Client & Client::operator=(const Client & other)
{
	/*_introducer = other._introducer;
	_sockfd = other._sockfd;
	_channels = other._channels;
	_is_op = other._is_op;*/
	(void) other;
	return (*this);
}

const int&	Client::getSockfd(void)const
{
	return(_sockfd);
}

const std::string&	Client::getName(void)const
{
	return(_name);
}


bool	sendMessageToClient(const Client& other)
{}
