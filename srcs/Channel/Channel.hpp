#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Channel
{
	public:

		Channel(void);
		Channel(std::string const &name);
		Channel(const Channel & other);
		~Channel(void);
	
		Channel & operator=(const Channel & other);

		void						kick(Client const &Client member);
		void						quit(Client const &Client member);
		void						join(Client	const &Client member);
		void						message(std::string const &message)const;
		std::string					getName(void)const;
		const std::vector<Client*>&	getMembers(void)const;
		

	private:

		std::string				_name;
		std::vector<Client*>	_members;
};

#endif
