#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include "Client.hpp"
#include "common.hpp"

class Client;

class Server
{

public:

	//constructors / destructors / assignation
	Server(char *port, char *password);
	~Server(void);

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
	void				sendMessage(Client* client, const std::string& message);
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
	std::vector<Client *>	_clients; // temp attributs of sockets waiting for Client class
	struct sockaddr_in		_address;
	fd_set					_readfds;
	fd_set					_writefds;
	fd_set					_exceptfds;

	void				_disconnect_client(Client* client);
	void				_new_client_connection(void);
	void				_init_selectfds(void);
	struct sockaddr_in	_init_address(void) const;
	int					_init_listening_socket(void) const;
	int					_bind(void) const;
	int					_listen(void) const;


	// Commands

	/* NICK <nickname> */
	void	_NICK(Client* client, const std::string& args);

	/* USER <user> <mode> <unused> <realname> set only username to user. */
	void	_USER(Client* client, const std::string& args);

	/* PASS <password> */
	// Check if password is correct, then set client to connected status
	void	_PASS(Client* client, const std::string& args);

	/* INVITE <nickname> [<channel>] */
	void	_INVITE(Client* client, const std::string& args);

	/* KICK <channel>[,...] <user> [<comment>]*/
	void	_KICK(Client* client, const std::string& args);

	/* MODE <nickname> {+,-}{o} */
	void	_MODE(Client* client, const std::string& args);	

	/* MSG  {<nickname> <message> */
	void	_MSG(Client* client, const std::string& args);	

	/* QUIT <quit message> */
	void	_QUIT(Client* client, const std::string& args);	

	/* NAMES [<channel>,...] */
	void	_NAMES(Client* client, const std::string& args);	

	/* JOIN <channel>[,...]  */
	void	_JOIN(Client* client, const std::string& args);	

	/* PART <channel>[,...] */
	void	_PART(Client* client, const std::string& args);	
};

#endif
