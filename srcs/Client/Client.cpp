#include "Client.hpp"

Client::Client(const int& sockfd) : 
	_name("default"),
	_nickname(_name),
	_buffer(""),
	_sockfd(sockfd), 
	_pass(false),
	_is_register(false)
{
	this->_init_board();
}

Client::~Client(void)
{
}

const bool& Client::isRegister(void) const
{
	return (_is_register);
}

const std::string&	Client::getBuffer(void) const
{
	return (_buffer);
}

const bool&	Client::getPass(void) const
{
	return (_pass);
}

const int&	Client::getSockfd(void) const
{
	return (_sockfd);
}

const std::string&	Client::getNickname(void)const
{
	return(_nickname);
}

const std::string&	Client::getName(void) const
{
	return (_name);
}

const std::vector<std::vector<std::string> >&	Client::getBoard(void) const
{
	return (_board);
}

void	Client::setName(const std::string& name)
{
	_name = name;
}

void	Client::resetBuffer(void)
{
	_buffer = "";
}

void	Client::addToBuffer(const std::string& add)
{
	_buffer += add;
}

void	Client::setPass(const bool& pass)
{
	_pass = pass;
}

void	Client::setRegister(const bool& is_register)
{
	_is_register = is_register;
}

void	Client::setNickname(const std::string& nickname)
{
	_nickname = nickname;
}

void	Client::setBoard(const std::string& sign, size_t x, size_t y)
{
	this->_board[x][y] = sign;
}

void	Client::_init_board(void)
{
	size_t	j;

	this->_board.clear();
	for (size_t i = 0; i < 3; ++i)
	{
		std::vector<std::string>	row;
		j = 0;
		for (; j < 3; ++j) 
			row.push_back(" ");
		this->_board.push_back(row);
	}
}
