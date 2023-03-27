#include "Server.hpp"

int	winning_board(std::vector<std::vector<std::string> > board, std::string player)
{
	if ((board[0][0] == player && board[0][1] == player && board[0][2] == player)
		||	(board[1][0] == player && board[1][1] == player && board[1][2] == player)
		||	(board[2][0] == player && board[2][1] == player && board[2][2] == player)
		||	(board[0][0] == player && board[1][0] == player && board[2][0] == player)
		||	(board[0][1] == player && board[1][1] == player && board[2][1] == player)
		||	(board[0][2] == player && board[1][2] == player && board[2][2] == player)
		||	(board[0][0] == player && board[1][1] == player && board[2][2] == player)
		||	(board[2][0] == player && board[1][1] == player && board[0][2] == player))
		return 1;
	else if (board[0][0] != " " && board[0][1] != " " && board[0][2] != " "
			&& board[1][0] != " " && board[1][1] != " " && board[1][2] != " "
			&& board[2][0] != " " && board[2][1] != " " && board[2][2] != " ")
		return 0;
	else
		return -1;
}

std::vector<std::string>	get_empty_slot(std::vector<std::string> args, std::vector<std::vector<std::string> > board)
{
	size_t				i = 0;
	size_t				j = 0;
	int					count = 0;
	int					found = 0;
	int					rand_value;
	std::string 		s;
	std::stringstream	out;

	for (; i < 3; ++i)
	{
		j = 0;
		for (; j < 3; ++j)
		{
			if (board[i][j] == " ")
				count++;
		}
	}
	rand_value = rand() % count + 1;
	i = 0;
	j = 0;
	for (; i < 3 && found != rand_value; ++i)
	{
		j = 0;
		std::cout << i << std::endl;
		for (; j < 3 && found != rand_value; ++j)
		{
			std::cout << j << std::endl;
			if (board[i][j] == " ")
				found++;
			if (found == rand_value)
				break ;
		}
		if (found == rand_value)
			break ;
	}
	args.pop_back();
	args.pop_back();
	out << i;
	s = out.str();
	args.push_back(s);
	out.str("");
	out.clear();
	out << j;
	s = out.str();
	args.push_back(s);
	return (args);
}

int	Server::_display_game(Client *client, std::vector<std::string> & args, int trigger)
{
	std::string	sign;
	int			col_value;

	col_value = std::atoi(args[2].c_str());
	//fill
	if (trigger == 0)
		sign = "X";
	else
		sign = "O";
	if (args[1].compare("0") == 0 && client->getBoard()[0][col_value] == " ")
		client->setBoard(sign, 0, col_value);
	else if (args[1].compare("1") == 0 && client->getBoard()[1][col_value] == " ")
		client->setBoard(sign, 1, col_value);
	else if (args[1].compare("2") == 0 && client->getBoard()[2][col_value] == " ")
		client->setBoard(sign, 2, col_value);
	else
	{
		this->sendMessage(client, "Please choose an empty spot\n");
		return (0);
	}
	//display
	if (trigger == 0)
		this->sendMessage(client, "You played :\n");
	else
		this->sendMessage(client, "Bot played :\n");
	this->sendMessage(client, " " + client->getBoard()[0][0] + " " + "|" + " " + client->getBoard()[0][1] + " " + "|" + " " + client->getBoard()[0][2] + "\n");
	this->sendMessage(client, " " + client->getBoard()[1][0] + " " + "|" + " " + client->getBoard()[1][1] + " " + "|" + " " + client->getBoard()[1][2] + "\n");
	this->sendMessage(client, " " + client->getBoard()[2][0] + " " + "|" + " " + client->getBoard()[2][1] + " " + "|" + " " + client->getBoard()[2][2] + "\n");
	if (winning_board(client->getBoard(), sign) == 1)
	{
		if (trigger == 1)
			this->sendMessage(client, "You lose :(\n");
		else
			this->sendMessage(client, "You win !\n");
		client->_init_board();
		return (1);
	}
	else if (winning_board(client->getBoard(), sign) == 0)
	{
		this->sendMessage(client, "It's a tie\n");
		client->_init_board();
		return (1);
	}
	return (-1);
}

void	Server::_CMDBOT(Client *client, std::vector<std::string> & args)
{
	int	game_status;

	if (args.size() != 3)
	{
		this->sendMessage(client, "[ERROR] : Usage: /CMDBOT <row> <column>\n");
		return;
	}
	std::cout << LOG << "CMDBOT command called by " + client->getName() << std::endl;
	if (args[1].size() != 1 || args[2].size() != 1 || std::isdigit(args[1][0]) == 0
		|| std::isdigit(args[2][0]) == 0 || std::atoi(args[1].c_str()) > 2 || std::atoi(args[2].c_str()) > 2)
	{
		this->sendMessage(client, "[ERROR] : Invalid arg\n");
		return ;
	}
	game_status = this->_display_game(client, args, 0);
	if (game_status == 1 || game_status == 0)
		return ;
	args = get_empty_slot(args, client->getBoard());
	if (this->_display_game(client, args, 1) == true)
		return ;
}
