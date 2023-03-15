#ifndef SERVER_HPP
#define SERVER_HPP

class Server
{

public:

	//constructors / destructors / assignation
	Server(void);
	Server(const Server & other);
	~Server(void);
	Server & operator=(const Server & other);

	//getters / setters
	int					getPort(void) const;
	void				setPort(const int & port);

	int					getNbClient(void) const;
	void				setNbClient(const int & nb_client);

	int					getReplyCode(void) const;
	void				setReplyCode(const int & reply_code);

	int					getListeningSocket(void) const;
	void				setListeningSocket(const int & listening_socket);

	std_::string		getPassword(void) const;
	void				setPassword(const std::string & password);

	int					getName(void) const;
	void				setName(const int & name);

	Client				getClient(int index) const;
	void				setClient(const Client & client);

	//methods
	int					create_listening_socket(void);
	struct sockaddr_in	init_address(struct sockadd_in address);
	void				create_new_client_socket(void) const;
	void				read_on_socket(int );
	void				write_to_socket(int socket);

	//pas sur pour les deux suivantes parce que l'appel de la fonction dedans prendrait juste une ligne dans le main.
	/*int					bind_socket(void) const;
	int					listen_to_port(void) const;*/
	

private:
	
	const int			_port;
	int					_nb_client
	int					_reply_code;
	int					_listening_socket;
	Client				_clients[10]
	const std::string	_name;
	const std::string	_password;
	struct sockaddr_in	address;
};

#endif
