#include "common.hpp"
#include "Server.hpp"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		Server::running = false;
		std::cout << std::endl;
	}
}

int	handle_signal(void)
{
	if (signal(SIGINT, &sig_handler) == SIG_ERR)
	{
		std::cerr << ERROR << "Signal function failed." << std::endl;
		return (1);
	}
	return (0);
}
