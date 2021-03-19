# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Mac.Makefile                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 11:51:41 by kmacquet          #+#    #+#              #
#    Updated: 2021/03/19 19:19:16 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx -I./includes
SRCS =	srcs/get_next_line.c srcs/get_next_line_utils.c \
		srcs/draw.c srcs/move.c srcs/utils.c srcs/keys.c \
		srcs/cub3d.c srcs/raycasting.c srcs/parsing.c \
		srcs/init.c srcs/libft.c srcs/error.c srcs/save.c \
		srcs/parsing_map.c srcs/sprite.c srcs/raycasting2.c \
		srcs/sprite2.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

bonus : $(NAME)

.c.o:
	$(CC) $(CFLAGS) -o $(<:.c=.o) -c $<

$(NAME):$(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
