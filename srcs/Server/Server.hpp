#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <iostream>
#include <sys/socket.h>
/* #include <sys/time.h> */
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include "../Client/Client.hpp"

class Client;

class Server
{

public:

	//constructors / destructors / assignation
	//Server(void);
	Server(char *port, char *password);
	Server(const Server & other);
	~Server(void);
	//Server & operator=(const Server & other);

	//getters / setters
	int					getPort(void) const;
	void				setPort(const int & port);

	int					getNbClient(void) const;
	void				setNbClient(const int & nb_client);

	int					getReplyCode(void) const;
	void				setReplyCode(const int & reply_code);

	int					getListeningSocket(void) const;
	void				setListeningSocket(const int & listening_socket);

	std::string			getPassword(void) const;
	void				setPassword(const std::string & password);

	int					getName(void) const;
	void				setName(const int & name);

	/* Client				getClient(int index) const; */
	/* void				setClient(const Client & client); */

	//methods
	void				create_new_client_socket(void) const;
	void				read_on_socket(int );
	void				write_to_socket(int socket);

	void				run(void);

	//pas sur pour les deux suivantes parce que l'appel de la fonction dedans prendrait juste une ligne dans le main.
	/*int					bind_socket(void) const;
	int					listen_to_port(void) const;*/
	

private:
	
	const int				_port;
	const std::string		_name;
	const std::string		_password;
	int						_nb_client;
	int						_reply_code;
	int						_listening_socket;
	std::vector<Client *>		_clients; // temp attributs of sockets waiting for Client class
	/* std::vector<Client*>	_clients; */
	struct sockaddr_in		_address;
	fd_set					_readfds;
	fd_set					_writefds;
	fd_set					_exceptfds;

	void				_new_client_connection(void);
	void				_init_selectfds(void);
	struct sockaddr_in	_init_address(void) const;
	int					_init_listening_socket(void) const;
	int					_bind(void) const;
	int					_listen(void) const;
};

#endif
