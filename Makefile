# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 13:25:04 by blevrel           #+#    #+#              #
#    Updated: 2023/03/17 19:15:44 by blevrel          ###   ########.fr        #
#    Updated: 2023/03/17 11:34:47 by afaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRCS =	srcs/main.cpp					\
		srcs/Server/Server.cpp			\
		srcs/Client/Client.cpp			\
		srcs/Channel/Channel.cpp		\
		srcs/Server/commands/USER.cpp	\
		srcs/Server/commands/QUIT.cpp   \


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
