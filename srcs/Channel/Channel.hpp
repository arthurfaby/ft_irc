#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <iostream>
#include <sys/socket.h>
#include "Client.hpp"

class Client;

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
		void						removeMember(const Client *client);
		void						_send_msg_to_all_members(const std::string & msg) const;

	private:

		const std::string		_name;
		std::vector<Client*>	_members;
		std::vector<Client*>	_operators;

};

#endif
