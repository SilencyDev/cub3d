# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 11:51:41 by kmacquet          #+#    #+#              #
#    Updated: 2021/03/09 16:33:35 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx -I./includes
SRCS =	srcs/get_next_line.c srcs/get_next_line_utils.c \
		srcs/draw.c srcs/move.c srcs/utils.c srcs/keys.c \
		srcs/cub3d.c srcs/raycasting.c srcs/parsing.c \
		srcs/init.c srcs/libft.c srcs/error.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -o $(<:.c=.o) -c $<

$(NAME):$(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -g -fsanitize=address

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re