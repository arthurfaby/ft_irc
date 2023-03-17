#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <vector>
#include <iostream>
#include "Client.hpp"

class Client;

class Channel
{
	public:

		Channel(void);
		Channel(std::string const &name);
		~Channel(void);
	

		void						kick(Client const & member);
		void						quit(Client const & member);
		void						join(Client	const & member);
		void						send_message(std::string const & message) const;
		std::string					getName(void) const;
		const std::vector<Client*>&	getMembers(void) const;
		

	private:

		const std::string		_name;
		std::vector<Client*>	_members;
		Channel(const Channel & other);
		Channel & operator=(const Channel & other);
};

#endif
