#include "Server.hpp"

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


Server::~Server(void)
{
}

void	Server::sendMessage(Client* client, const std::string& message)
{
	int	res;

	res = send(client->getSockfd(), message.c_str(), message.length(), 0);
	if (res == -1)
	{
		std::cerr << ERROR << "Send failed." << std::endl;
		return ;
	}
}

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
			if (_clients[i]->getSockfd() > nfds)
				nfds = _clients[i]->getSockfd();

		// select
		select_res = select(nfds + 1, &_readfds, &_writefds, &_exceptfds, NULL);
		if (select_res == -1)
		{
			std::cerr << ERROR << "Select failed" << std::endl;
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
			if (FD_ISSET(_clients[i]->getSockfd(), &_readfds))
			{
				res = recv(_clients[i]->getSockfd(), buffer, 1024, 0);
				if (res == -1)
				{
					std::cerr << ERROR << "Recv failed" << std::endl;
					return ; // handle rerror
				}
				buffer[res - 1] = 0; // put \0 and remove \n at the same time
				std::cout << LOG << "Message received from " << _clients[i]->getName() << "(" << _clients[i]->getSockfd() << ") : '" << buffer << "'" << std::endl;
				if (std::string(buffer) == "quit")
				{
					this->_disconnect_client(_clients[i]);
					continue;
				}
				res = send(_clients[i]->getSockfd(), "Yes mon bro\n", 12, 0);


			}

			if (FD_ISSET(_clients[i]->getSockfd(), &_exceptfds))
			{
				this->_disconnect_client(_clients[i]);
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

void	Server::_disconnect_client(Client* client)
{
	std::vector<Client*>::iterator	it;
	std::vector<Client*>::iterator	ite;

	it = _clients.begin();
	ite = _clients.end();
	for (; it != ite; ++it)
	{
		if (*it == client)
		{
			std::cout << LOG << "Client " << client->getName() << " has just been disconnect." << std::endl;
			this->sendMessage(client, "You have been disconnected by server.");
			close(client->getSockfd());
			_clients.erase(it);
			return ;
		}
	}
}

void	Server::_new_client_connection(void)
{
	int	client_socket;

	client_socket = accept(_listening_socket, NULL, NULL); // pas sur de ca
	if (client_socket == -1)
	{
		std::cerr << ERROR << "Accept failed." << std::endl;
		return ; // handle error
	}
	Client*	new_client = new Client(*this, client_socket);
	std::cout << LOG << "New client (" << client_socket << ")" << std::endl;
	_clients.push_back(new_client);
	this->sendMessage(new_client, "Connected to server.\n");
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
			FD_SET(_clients[i]->getSockfd(), &_readfds);
			FD_SET(_clients[i]->getSockfd(), &_writefds);
			FD_SET(_clients[i]->getSockfd(), &_exceptfds);
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
	int	opt(-1);

	new_listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (new_listening_socket < 0)
	{
		std::cerr << ERROR << "Socket failed." << std::endl;
		return (-1);
	}
	if (setsockopt(new_listening_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) != 0)
	{
		std::cerr << ERROR << "Setsockopt failed." << std::endl;
		return (-1);
	}
	return (new_listening_socket);
}

int	Server::_bind(void) const
{
	int	bind_value;

	bind_value = bind(_listening_socket, (struct sockaddr*)&_address, sizeof(struct sockaddr));
	if (bind_value == -1)
		std::cerr << ERROR << "Bind failed." << std::endl;
	return (bind_value);
}

int	Server::_listen(void) const
{
	int	listen_value;

	listen_value = listen(_listening_socket, 10);
	if (listen_value == -1)
		std::cerr << ERROR << "Listen failed." << std::endl;
	return (listen_value);
}

void	Server::_join(Client const & member) const
{
	
}

void	Server::_kick(Client const & member) const
{
	
}

void	Server::_part(Client const & member) const
{
	
}

void	Server::_send_message(std::string const & msg) const
{
	
}
