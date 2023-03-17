#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <vector>
#include <iostream>
#include "Client.hpp"

class Client;

class Channel
{
	public:

		Channel(std::string const &name, Client *client);
		~Channel(void);
	
		std::string					_getName(void) const;
		const std::vector<Client*>&	_getMembers(void) const;
		void						_addMember(const Client *client);
		void						_removeMember(const Client *client);

	private:

		const std::string		_name;
		std::vector<Client*>	_members;
};

#endif
