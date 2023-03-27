NAME = ircserv

SRCS =	srcs/main.cpp						\
		srcs/Server/Server.cpp				\
		srcs/Client/Client.cpp				\
		srcs/Channel/Channel.cpp			\
		srcs/Server/commands/CMDUSER.cpp	\
		srcs/Server/commands/CMDNAMES.cpp	\
		srcs/Server/commands/CMDMSG.cpp		\
		srcs/Server/commands/CMDQUIT.cpp	\
		srcs/Server/commands/CMDPART.cpp	\
		srcs/Server/commands/CMDKICK.cpp	\
		srcs/Server/commands/CMDBOT.cpp	\
		srcs/Server/commands/CMDWHOAMI.cpp	\
		srcs/signal.cpp						\
		srcs/Server/commands/CMDINVITE.cpp	\
		srcs/Server/commands/CMDPASS.cpp	\
		srcs/Server/commands/CMDJOIN.cpp	\
		srcs/Server/commands/CMDNICK.cpp	\
		srcs/Server/commands/CMDMODE.cpp	\

OBJS = ${SRCS:.cpp=.o}

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

HEAD  =	-I srcs/Server \
		-I srcs/Client \
		-I srcs/Channel \
		-I includes/

RM = rm -f

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

run: re
	./ircserv 6666 password

.cpp.o:
	${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.cpp=.o}

${NAME}:${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${HEAD} -o ${NAME}

.PHONY: all clean fclean re run
