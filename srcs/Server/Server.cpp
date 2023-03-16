#include "Server.hpp"

/*Server::Server(void)
{
	std::cout << "Default constructor called" << std::endl;
}*/

Server::Server(char *port, char *password) :
	_port(std::atoi(port)),
	_name("ircserver"),
	_password(password),
	_nb_client(0),
	_reply_code(-1),
	_listening_socket(-1)
{
	/* Init address of the server */
	_address = _init_address();

	/* Init listening socket */
	_listening_socket = _init_listening_socket();
	if (_listening_socket == -1)
		return ; // throw exception ? and close sockets

	if (this->_bind() == -1)
		return ; // throw expection ? and close sockets

	if (this->_listen() == -1)
		return ; // throw exception ? and close sockets
	
}

Server::Server(const Server & other) :
	_port(0),
	_name("")
	/* _port(other.getPort()), */
	/* _name(other.getName()), */
	/* _password(other.getPassword()), */
	/* _nb_client(other.getNbClient()), */
	/* _reply_code(other.getReplyCode()), */
	/* _listening_socket(other.getListeningSocket()) */
{
	(void)other;
}

Server::~Server(void)
{
}

/*Server & Server::operator=(const Server & other)
{
	//copy operations here;
	(void)other;
	return (*this);
}*/

/*

	GETTERS AND SETTERS

*/

/* int	Server::getPort(void) const */
/* { */
/* 	return (_port); */
/* } */

/* void	Server::setPort(const int& port) */
/* { */
/* 	_port = port; */
/* } */

/* int	Server::getNbClient( */


void	Server::run(void)
{
	int		select_res;
	int		nfds;
	char	buffer[1024];
	int		res;

	while (1)
	{
		// init readfds, writefds and exceptfds
		this->_init_selectfds();

		// get high-numbered socket
		nfds = _listening_socket;
		/* for (int i = 0; i < _clients.size(); ++i) */
		/* 	if (_clients[i] != NULL && _clients[i]->getSockfd() > nfds) */
		/* 		nfds = _clients[i]->getSockfd(); */

		for (size_t i = 0; i < _clients.size(); ++i)
			if (_clients[i] > nfds)
				nfds = _clients[i];

		// select
		select_res = select(nfds + 1, &_readfds, &_writefds, &_exceptfds, NULL);
		if (select_res == -1)
		{
			std::cerr << "[ERROR] Select failed" << std::endl;
			return ; // throw exception ?
		}

		// treat with FD_ISSET
		if (FD_ISSET(_listening_socket, &_readfds))
			_new_client_connection();
			// new connection

		for (size_t i = 0; i < _clients.size(); ++i)
		{
			/* if (_clients[i] == NULL) continue; */
			/* if (FD_ISSET(_clients[i]->getSockfd(), &_readfds)) */
			/* { */
				// receive	
			/* } */
			if (FD_ISSET(_clients[i], &_readfds))
			{
				res = recv(_clients[i], buffer, 1024, 0);
				if (res == -1)
				{
					std::cerr << "[ERROR] Recv failed" << std::endl;
					return ; // handle rerror
				}
				buffer[res] = 0;
				std::cout << "[LOG] Message received from " << _clients[i] << ": '" << buffer << "'" << std::endl;
				res = send(_clients[i], "Yes mon bro\n", 12, 0);
				if (res == -1)
				{
					std::cerr << "[ERROR] Send failed." << std::endl;
					return ;
				}

			}
				// receive
		}

/* 		for (size_t i = 0; i < _clients.size(); ++i) */
/* 		{ */
/* 			/1* if (_clients[i] == NULL) continue; *1/ */
/* 			/1* if (FD_ISSET(_clients[i]->getSockfd(), &_writefds)) *1/ */
/* 				// send */

/* 			if (FD_ISSET(_clients[i], &_writefds)) */
/* 			{ */
/* 				res = send(_clients[i], "Yes mon bro\n", 12, 0); */
/* 				if (res == -1) */
/* 				{ */
/* 					std::cerr << "[ERROR] Send failed." << std::endl; */
/* 					return ; */
/* 				} */
/* 				/1* std::cout << "[LOG] Message sent." << std::endl; *1/ */
/* 				/1* close(_clients[i]); *1/ */
/* 			} */
/* 				// send */
/* 		} */
	}
}

void	Server::_new_client_connection(void)
{
	//Client*	new_client = new Client(*this, );
	int	client_socket;

	client_socket = accept(_listening_socket, NULL, NULL); // pas sur de ca
	if (client_socket == -1)
	{
		std::cerr << "[ERROR] Accept failed." << std::endl;
		return ; // handle error
	}
	std::cout << "[LOG] New client (" << client_socket << ")" << std::endl;
	_clients.push_back(client_socket);
}

void	Server::_init_selectfds(void)
{
	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	FD_ZERO(&_exceptfds);

	FD_SET(_listening_socket, &_readfds);
	FD_SET(_listening_socket, &_exceptfds);
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		/* if (_clients[i] != NULL) */
		/* { */
			FD_SET(_clients[i], &_readfds);
			FD_SET(_clients[i], &_writefds);
			FD_SET(_clients[i], &_exceptfds);
			/* FD_SET(_clients[i]->getSockfd(), &_readfds); */
			/* FD_SET(_clients[i]->getSockfd(), &_writefds); */
			/* FD_SET(_clients[i]->getSockfd(), &_exceptfds); */
		/* } */
	}
	
}

struct sockaddr_in	Server::_init_address() const
{
	struct sockaddr_in	address;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(_port);
	return (address);
}

int Server::_init_listening_socket(void) const
{
	int	new_listening_socket;
	/* int	opt; */

	new_listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (new_listening_socket < 0)
	{
		std::cerr << "[ERROR] Socket failed." << std::endl;
		return (-1);
	}
	/* if (setsockopt(new_listening_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0) */
	/* { */
	/* 	std::cerr << "[ERROR] Setsockopt failed." << std::endl; */
	/* 	return (-1); */
	/* } */
	return (new_listening_socket);
}

int	Server::_bind(void) const
{
	int	bind_value;

	bind_value = bind(_listening_socket, (struct sockaddr*)&_address, sizeof(struct sockaddr));
	if (bind_value == -1)
		std::cerr << "[ERROR] Bind failed." << std::endl;
	return (bind_value);
}

int	Server::_listen(void) const
{
	int	listen_value;

	listen_value = listen(_listening_socket, 10);
	if (listen_value == -1)
		std::cerr << "[ERROR] Listen failed." << std::endl;
	return (listen_value);
}
