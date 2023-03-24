#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include "Client.hpp"
#include "Channel.hpp"
#include "common.hpp"

class Client;
class Channel;

class Server
{

public:

	//constructors / destructors / assignation
	Server(char *port, char *password);
	~Server(void);

	static bool			running;

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
//	bool				isOperator(std::string const &channel, Client const &Client); 

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
	std::string				_cmds[12];
	void					(Server::*_commands_funcs[12])(Client *client, std::vector<std::string> & args);
	std::vector<Client *>	_clients; // temp attributs of sockets waiting for Client class
	std::vector<Channel *>	_channels;
	struct sockaddr_in		_address;
	fd_set					_readfds;
	fd_set					_writefds;
	fd_set					_exceptfds;

	void				_remove_empty_channels(void);
	void				_disconnect_client(Client* client);
	void				_new_client_connection(void);
	void				_init_selectfds(void);
	struct sockaddr_in	_init_address(void) const;
	int					_init_listening_socket(void) const;
	int					_bind(void) const;
	int					_listen(void) const;
	void				_init_cmds(void);
	void				_init_commands_funcs(void);

	bool		_doesChannelExists(const std::string& name) const;
	bool		_doesClientExists(const std::string& name) const;
	Channel*	_getChannel(const std::string& name);
	Client*		_getClient(const std::string& name);

	// Commands
	std::vector<std::string>	_parse_cmds(std::string & args);
	void						_parse_cmd_args(std::string args, Client *client);
	void						_call_cmd(std::vector<std::string> & args, Client *client);

	void	_CMDNICK(Client* client, std::vector<std::string> &args);

	void	_CMDUSER(Client* client, std::vector<std::string> & args);
	
	void	_CMDPASS(Client* client, std::vector<std::string> & args);

	void	_CMDINVITE(Client* client, std::vector<std::string> & args);

	void	_CMDKICK(Client* client, std::vector<std::string> & args);

	void	_CMDMODE(Client* client, std::vector<std::string> & args);	

	void	_CMDMSG(Client* client, std::vector<std::string> & args);	
	bool	_check_channel_or_user_exists(const std::string dest, Client *client);

	void	_CMDQUIT(Client* client, std::vector<std::string> & args);	

	void	_CMDNAMES(Client* client, std::vector<std::string> & args);	

	void	_CMDJOIN(Client* client, std::vector<std::string> & args);	

	void	_CMDPART(Client* client,  std::vector<std::string> & args);	

	void	_CMDWHOAMI(Client* client, std::vector<std::string> & args);
};

#endif
