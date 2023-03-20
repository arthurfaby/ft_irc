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
	/* Init commands array */
	this->_init_cmds();
	/* Init commands functions pointer array */
	this->_init_commands_funcs();
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
		this->_disconnect_client(client);
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
					if (FD_ISSET(_clients[i]->getSockfd(), &_readfds))
			{
				res = recv(_clients[i]->getSockfd(), buffer, 1024, 0);
				if (res == -1 || res == 0)
				{
					if (res == -1)
						std::cerr << ERROR << "Recv failed" << std::endl;
					else
						std::cerr << ERROR << "Recv nothing" << std::endl;
					this->_disconnect_client(_clients[i]);
					continue ; // handle rerror
				}
				buffer[res] = 0; // put \0
				this->_parse_cmd_args(buffer, _clients[i]);
				std::cout << LOG << "Message received from " << _clients[i]->getName() << "(" << _clients[i]->getSockfd() << ") : '" << buffer << "'" << std::endl;
				if (std::string(buffer) == "quit\n")
				{
					this->_disconnect_client(_clients[i]);
					continue;
				}
			}

			if (FD_ISSET(_clients[i]->getSockfd(), &_exceptfds))
			{
				this->_disconnect_client(_clients[i]);
			}
				// receive
		}
	}
}

void	Server::_parse_cmd_args(std::string args, Client *client)
{
	std::vector<std::string>	parsed_args;
	size_t 						start = 0;
	size_t						end;
	size_t						pos = args.find_first_not_of(" ");
	
	if (args.size() <= 2)
		return ;
	args.resize(args.size() - 2);
	if (pos != std::string::npos)
		args.erase(0, pos);
	pos = args.find_last_not_of(" ");
	if (pos != std::string::npos)
		args.erase(pos + 1);
	for (size_t i = 0; i < args.size(); i++)
		args[i] = tolower(args[i]);
	end = args.find(' ', start);
	while (end != std::string::npos)
	{
		if (args.substr(start, end - start).size() > 0)
			parsed_args.push_back(args.substr(start, end - start));
		start = end + 1;
		end = args.find(' ', start);
	}
	//compter les args
	if (args.substr(start, end - start).size() > 0)
		parsed_args.push_back(args.substr(start));
	for (size_t i = 0; i < parsed_args.size(); i++)
		std::cout << i << " : '" << parsed_args[i] << "'" << std::endl;
	this->_call_cmd(parsed_args, client);
}

void	Server::_call_cmd(std::vector<std::string> & args, Client *client)
{
	if (args.size() == 0)
	{
		std::cout << "nothing in vector" << std::endl;
		return ;
	}
	for (int i = 0; i < 11; i++)
	{
		if (args[0].compare(this->_cmds[i]) == 0)
			(this->*_commands_funcs[i])(client, args);
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
			//this->sendMessage(client, "You have been disconnected by server.");
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
	Client*	new_client = new Client(client_socket);
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
		FD_SET(_clients[i]->getSockfd(), &_readfds);
		FD_SET(_clients[i]->getSockfd(), &_writefds);
		FD_SET(_clients[i]->getSockfd(), &_exceptfds);
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

void	Server::_NICK(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_PASS(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_INVITE(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_KICK(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_MODE(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_MSG(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_NAMES(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_JOIN(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_PART(Client* client, std::vector<std::string> & command)
{
	(void)client;
	(void)command;
}

void	Server::_init_commands_funcs(void)
{
	this->_commands_funcs[0] = (&Server::_NICK);
	this->_commands_funcs[1] = (&Server::_USER);
	this->_commands_funcs[2] = (&Server::_PASS);
	this->_commands_funcs[3] = (&Server::_INVITE);
	this->_commands_funcs[4] = (&Server::_KICK);
	this->_commands_funcs[5] = (&Server::_MODE);
	this->_commands_funcs[6] = (&Server::_MSG);
	this->_commands_funcs[7] = (&Server::_QUIT);
	this->_commands_funcs[8] = (&Server::_NAMES);
	this->_commands_funcs[9] = (&Server::_JOIN);
	this->_commands_funcs[10] = (&Server::_PART);
}

void	Server::_init_cmds(void)
{
	this->_cmds[0] = "nick";
	this->_cmds[1] = "user";
	this->_cmds[2] = "pass";
	this->_cmds[3] = "invite";
	this->_cmds[4] = "kick";
	this->_cmds[5] = "mode";
	this->_cmds[6] = "msg";
	this->_cmds[7] = "quit";
	this->_cmds[8] = "names";
	this->_cmds[9] = "join";
	this->_cmds[10] = "part";
}
