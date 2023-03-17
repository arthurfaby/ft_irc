#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <string>
#include "Client.hpp"

class Client;

class Channel
{
	public:

		Channel(std::string const &name, Client *client);
		~Channel(void);
	
		const std::string&			getName(void) const;
		const std::vector<Client*>&	getMembers(void) const;
		void						addMember(const Client *client);
		void						removeMember(const Client *client);

	private:

		const std::string		_name;
		std::vector<Client*>	_members;
		std::vector<Client*>	_operators;
};

#endif
