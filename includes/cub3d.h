/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:32:22 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/01 16:42:34 by kmacquet         ###   ########.fr       */
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
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define FORWARD 119
# define LEFT 97
# define BACKWARD 115
# define RIGHT 100
# define RLEFT 65361
# define RRIGHT 65363
# define SPACE 32
// # define FORWARD 13
// # define LEFT 0
// # define BACKWARD 1
// # define RIGHT 2
// # define RLEFT 123
// # define RRIGHT 124
// # define SPACE 49
# define FOV 60
# define N 90
# define E 0
# define S 270
# define W 180
# define PI 3.14159265359
# define DTOR (PI / 180)
# define FOVR (FOV * PI / 180)
# define cwall (64 / 138)
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
	int		y_pplayer;
	int		x_pplayer;
	double	pdx;
	double	pdy;
	double	pa;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	dv;
	double	dh;
	int		forward;
	int		left;
	int		backward;
	int		right;
	int		rleft;
	int		rright;
}				t_data;

void	ft_init_hv(t_data *data);
void	ft_init_player(t_data *data);
void	check_vertical(t_data *data);
void	check_horizontal(t_data *data);
void	ft_player(t_data *data, int x, int y, int color);
int		ft_imprim(t_data *data);
int		is_map_valid(t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
void	ft_rotate_r(t_data *data);
void	ft_rotate_l(t_data *data);
void	ft_move_f(t_data *data);
void	ft_move_b(t_data *data);
void	ft_move_l(t_data *data);
void	ft_move_r(t_data *data);
void	ft_move(t_data *data);
void	ft_square(t_data *data, int x, int y, int color);
void	ft_direction_n(t_data *data, int x, int y, int color);
void	ft_direction_s(t_data *data, int x, int y, int color);
void	ft_direction_e(t_data *data, int x, int y, int color);
void	ft_direction_w(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_init(t_data *data);
void	ft_print_tab(t_data *data);
char	is_charset(char c, char *charset);
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