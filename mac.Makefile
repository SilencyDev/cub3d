# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 11:51:41 by kmacquet          #+#    #+#              #
#    Updated: 2021/02/26 10:45:49 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
FLAGS = -Wall -Wextra -Werror -Imlx -I./includes
SRCS =	srcs/get_next_line.c srcs/get_next_line_utils.c \
		srcs/draw.c srcs/move.c srcs/utils.c srcs/rotate.c \
		srcs/keys.c srcs/cub3d.c
OBJS = $(SRCS:.c=.o)
ARRCS = ar -rcs
RM = rm -f

all: $(NAME)

.c.o:
	$(CC) $(FLAGS) -o $(<:.c=.o) -c $<

$(NAME):$(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re