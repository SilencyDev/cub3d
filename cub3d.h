/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:32:22 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/25 16:21:28 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define FORWARD 13
# define LEFT 0
# define BACKWARD 1
# define RIGHT 2
# define RLEFT 123
# define RRIGHT 124
# define SPACE 49
# define SIZE 64

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	map[255][255];
	int		one;
	char	player;
	int		nb_player;
	int		y_player;
	int		x_player;
	int		forward;
	int		left;
	int		backward;
	int		right;
	int		rleft;
	int		rright;
}				t_data;

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *str);
char	*ft_memalloc(size_t size);
void	*ft_memset(void *b, int c, size_t len);
int		ft_memdel(char **ptr);
int		get_next_line(int fd, char **line);

#endif
