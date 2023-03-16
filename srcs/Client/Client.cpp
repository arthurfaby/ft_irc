#include "Client.hpp"

Client::Client(void)
{
	return ;//exception ?	
}

Client::Client(const Server& introducer, const int& sockfd)
{}

Client::Client(const Client & other)
{}

Client::~Client(void)
{}

Client & Client::operator=(const Client & other)
{
	return (*this);
}
