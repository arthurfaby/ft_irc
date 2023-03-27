#include "Server.hpp"

bool Server::running = true;

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
	size_t	channel_size = _channels.size();
	size_t	client_size = _clients.size();

	if (_listening_socket > 0)
		close(_listening_socket);
	for (size_t i = 0; i < client_size; ++i)
		this->_disconnect_client(_clients[0]);
	for (size_t i = 0; i < channel_size; ++i)
		delete _channels[i];
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

	while (running)
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
		if (!running)
			break;
		if (select_res == -1)
		{
			std::cerr << ERROR << "Select failed" << std::endl;
			break ; // throw exception ?
		}

		// treat with FD_ISSET
		if (FD_ISSET(_listening_socket, &_readfds))
			_new_client_connection();
			// new connection
		for (size_t i = 0; i < _clients.size(); ++i)
		{
			if (FD_ISSET(_clients[i]->getSockfd(), &_exceptfds))
			{
				this->_disconnect_client(_clients[i]);
				continue;
			}
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
			}
		}
		_remove_empty_channels();
	}
}

void	Server::_remove_empty_channels(void)
{
	std::vector<Channel*>::iterator			it = _channels.begin();
	
	for (it = _channels.begin(); it != _channels.end(); ++it)
	{
		if ((*it)->getMembers().begin() == (*it)->getMembers().end())
		{
			delete *it;
			_channels.erase(it);
			it = _channels.begin();
			break;
		}
	}
}

void	Server::_parse_cmd_args(std::string args, Client *client)
{
	std::vector<std::string>	parsed_args;
	std::string					temp;
	size_t 						start = 0;
	size_t						end;
	size_t						pos;

	client->addToBuffer(args);
	if (client->getBuffer().find("\r\n") == std::string::npos)
	{
		return ;
	}
	args = client->getBuffer();
	client->resetBuffer();
	if (args[0] == ' ')
	{
		this->sendMessage(client, "Space before command is not valid\n");
		return ;
	}
	args.resize(args.size() - 2);//only one command
	pos = args.find_last_not_of(" ");
	if (pos != std::string::npos)
		args.erase(pos + 1);//remove trailing spaces
	for (size_t i = 0; args[i] != ' ' && i < args.size(); i++)
		args[i] = tolower(args[i]);//lowercase the entire string
	end = args.find(' ', start);
	while (end != std::string::npos)
	{
		temp = args.substr(start, end - start);
		if (temp[0] == ':')
		{
			parsed_args.push_back(args.substr(start));//puts everything after the ':' in the vector
			end = std::string::npos;
			break ;
		}
		if (args.substr(start, end - start).size() > 0)
			parsed_args.push_back(args.substr(start, end - start));
		start = end + 1;
		end = args.find(' ', start);
	}
	if (args.substr(start, end - start).size() > 0 && end == std::string::npos)//in case there is only one arg
		parsed_args.push_back(args.substr(start));
	else
		return ;
	if (parsed_args[0].compare("cmdquit") != 0 && (client->getPass() == false && parsed_args[0].compare("cmdpass") != 0))
	{
		this->sendMessage(client, "Enter the password with <cmdpass> before using any command\n");
		return ;
	}
	else if (parsed_args[0].compare("cmdquit") != 0 && (client->isRegister() == false && parsed_args[0].compare("cmduser") != 0 && parsed_args[0].compare("cmdpass") != 0 ))
	{
		this->sendMessage(client, "Register with <cmduser> before using any command\n");
		return ;
	}
	this->_call_cmd(parsed_args, client);
}

void	Server::_call_cmd(std::vector<std::string> & args, Client *client)
{
	if (args.size() != 0)
	{
		for (int i = 0; i < 13; i++)
		{
			if (args[0].compare(this->_cmds[i]) == 0)
			{
				(this->*_commands_funcs[i])(client, args);
				return ;
			}
		}
	}
	this->sendMessage(client, "Command not found.\n");
}

void	Server::_disconnect_client(Client* client)
{
	std::vector<Client*>::iterator	it;
	std::vector<Client*>::iterator	ite;

	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->isIn(client->getNickname()))
		{
			_channels[i]->removeMember(client);
			_channels[i]->_send_msg_to_all_members(this, _channels[i]->getName() + " " + client->getNickname() + " has left the channel.\n");
		}
	}
	it = _clients.begin();
	ite = _clients.end();
	for (; it != ite; ++it)
	{
		if (*it == client)
		{
			std::cout << LOG << "Client " << client->getName() << " has just been disconnected." << std::endl;
			close(client->getSockfd());
			delete *it;
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

void	Server::_init_commands_funcs(void)
{
	this->_commands_funcs[0] = (&Server::_CMDNICK);
	this->_commands_funcs[1] = (&Server::_CMDUSER);
	this->_commands_funcs[2] = (&Server::_CMDPASS);
	this->_commands_funcs[3] = (&Server::_CMDINVITE);
	this->_commands_funcs[4] = (&Server::_CMDKICK);
	this->_commands_funcs[5] = (&Server::_CMDMODE);
	this->_commands_funcs[6] = (&Server::_CMDMSG);
	this->_commands_funcs[7] = (&Server::_CMDQUIT);
	this->_commands_funcs[8] = (&Server::_CMDNAMES);
	this->_commands_funcs[9] = (&Server::_CMDJOIN);
	this->_commands_funcs[10] = (&Server::_CMDPART);
	this->_commands_funcs[11] = (&Server::_CMDBOT);
	this->_commands_funcs[12] = (&Server::_CMDWHOAMI);
}

void	Server::_init_cmds(void)
{
	this->_cmds[0] = "cmdnick";
	this->_cmds[1] = "cmduser";
	this->_cmds[2] = "cmdpass";
	this->_cmds[3] = "cmdinvite";
	this->_cmds[4] = "cmdkick";
	this->_cmds[5] = "cmdmode";
	this->_cmds[6] = "cmdmsg";
	this->_cmds[7] = "cmdquit";
	this->_cmds[8] = "cmdnames";
	this->_cmds[9] = "cmdjoin";
	this->_cmds[10] = "cmdpart";
	this->_cmds[11] = "cmdbot";
	this->_cmds[12] = "cmdwhoami";
}

bool	Server::_doesChannelExists(const std::string& name) const
{
	for  (size_t i = 0; i < _channels.size(); ++i)
		if (name == _channels[i]->getName())
			return (true);
	return (false);
}

bool	Server::_doesClientExists(const std::string& name) const
{
	for (size_t i = 0; i < _clients.size(); ++i)
		if (_clients[i]->getNickname() == name)
			return (true);
	return (false);
}

Channel*	Server::_getChannel(const std::string& name)
{
	for  (size_t i = 0; i < _channels.size(); ++i)
		if (name == _channels[i]->getName())
			return (_channels[i]);
	return (NULL);
}

Client*	Server::_getClient(const std::string& name)
{
	for  (size_t i = 0; i < _clients.size(); ++i)
		if (name == _clients[i]->getNickname())
			return (_clients[i]);
	return (NULL);
}
