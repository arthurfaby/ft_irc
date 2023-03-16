# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 13:25:04 by blevrel           #+#    #+#              #
#    Updated: 2023/03/16 19:28:06 by pirabaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRCS =	srcs/main.cpp				\
		srcs/Server/Server.cpp		\
		srcs/Client/Client.cpp
		

OBJS = ${SRCS:.cpp=.o}

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

HEAD  = -I srcs/Command -I srcs/Server -I srcs/Client -I srcs/Channel -I srcs/User -I srcs/Operator

RM = rm -f

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.cpp.o:
	${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.cpp=.o}

${NAME}:${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${HEAD} -o ${NAME}

.PHONY: all clean fclean re
