#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command
{

private:

	//private attributes here;

public:

	Command(void);
	Command(const Command & other);
	~Command(void);
	Command & operator=(const Command & other);

};

#endif
