# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccottin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 12:16:24 by ccottin           #+#    #+#              #
#    Updated: 2023/03/23 15:23:30 by ccottin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= btc

SRCS	= main.cpp BitcoinExchange.cpp

CC		= c++

OBJS	= $(SRCS:.cpp=.o)

DEPS	= $(OBJS:.o=.d)

CFLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD -g3

all:	$(NAME)

%.o:	%.cpp
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
		rm -rf $(DEPS)
		rm -rf $(OBJS)

fclean:	clean
		rm -rf $(NAME)

re:		fclean
		make

-include $(DEPS)

.PHONY	:	all fclean clean re
