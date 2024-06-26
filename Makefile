# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 11:51:41 by kmacquet          #+#    #+#              #
#    Updated: 2024/06/01 22:57:02 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Iminilibx-linux -Imlx -I./includes
SRCS =	srcs/get_next_line.c srcs/get_next_line_utils.c \
		srcs/draw.c srcs/move.c srcs/utils.c srcs/keys.c \
		srcs/cub3d.c srcs/raycasting.c srcs/parsing.c \
		srcs/init.c srcs/libft.c srcs/error.c srcs/save.c \
		srcs/parsing_map.c srcs/sprite.c srcs/raycasting2.c \
		srcs/sprite2.c srcs/parsing_map2.c srcs/parsing_utils.c
OBJS = $(SRCS:.c=.o)
ARRCS = ar -rcs
RM = rm -f

all: $(NAME)

bonus : $(NAME)

.c.o:
	$(CC) $(FLAGS) -o $(<:.c=.o) -c $<

$(NAME):$(OBJS)
	$(CC) $(OBJS) -Lminilibx-linux -Lmlx -Iminilibx-linux -L/usr/lib -lmlx -lm -lbsd -lX11 -lXext -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
