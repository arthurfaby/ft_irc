#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"

class Client;

class Channel
{
	public:

		Channel(void);
		Channel(std::string const &name);
		Channel(const Channel & other);
		~Channel(void);
	
		Channel & operator=(const Channel & other);

		void						kick(Client const & member);
		void						quit(Client const & member);
		void						join(Client	const & member);
		void						message(std::string const &message)const;
		std::string					getName(void)const;
		const std::vector<Client*>&	getMembers(void)const;
		

	private:

		std::string				_name;
		std::vector<Client*>	_members;
};

#endif
