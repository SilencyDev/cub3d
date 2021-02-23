# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 11:51:41 by kmacquet          #+#    #+#              #
#    Updated: 2021/02/23 13:56:40 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
FLAGS = -Wall -Wextra -Werror -I./includes
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
ARRCS = ar -rcs
RM = rm -f

all: $(NAME)

.c.o:
	$(CC) $(FLAGS) -o $(<:.c=.o) -c $<

$(NAME):$(OBJS)
	$(ARRCS) $@ $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
