#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <iostream>
#include <sys/socket.h>
#include "Client.hpp"
#include "Server.hpp"

class Client;

class Server;

class Channel
{
	public:

		Channel(std::string const &name, Client *client);
		~Channel(void);
	
		std::string					getName(void) const;
		const std::vector<Client*>&	getMembers(void) const;
		const std::vector<Client*>&	getOperators(void) const;
		void						addMember(Client *client);
		void						addOperator(Client *client);
		void						removeOperator(const Client *client);
		void						removeMember(const Client *client);
		void						_send_msg_to_all_members(Server *server, const std::string & msg) const;

		bool						isIn(const std::string& name) const;
		bool						isOp(const std::string& name) const;

	private:

		const std::string		_name;
		std::vector<Client*>	_members;
		std::vector<Client*>	_operators;

};

#endif
