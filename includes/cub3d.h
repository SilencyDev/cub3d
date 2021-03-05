/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:32:22 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/05 15:44:50 by kmacquet         ###   ########.fr       */
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
# include <limits.h>
# include <float.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
// # define FORWARD 119
// # define LEFT 97
// # define BACKWARD 115
// # define RIGHT 100
// # define RLEFT 65361
// # define RRIGHT 65363
// # define SPACE 32
# define FORWARD 13
# define LEFT 0
# define BACKWARD 1
# define RIGHT 2
# define RLEFT 123
# define RRIGHT 124
# define SPACE 49
# define WIDTH 1080.0
# define WIDTH2 (WIDTH / 2)
# define HEIGHT 720.0
# define HEIGHT2 (HEIGHT / 2)
# define FOV 60.0
# define FOV2 (FOV / 2)
# define SPEED 10.0
# define INC (FOV * 1.0 / WIDTH)
# define PI M_PI
# define N (2.0 * PI)
# define E 0.0
# define S (PI * 3.0/2.0)
# define W PI
# define DTOR (PI / 180.0)
# define FOVR (FOV * PI / 180.0)
# define SIZE 64.0
# define DPROJ (WIDTH2 / tan(FOV2 * DTOR))
# define CWALL (SIZE / DPROJ)

typedef struct		s_texture
{
	void			*img_ptr;
	void			*addr_ptr;
	int				img_width;
	int				img_height;
	int				bits_per_pixel_t;
	int				line_length_t;
	int				endian_t;
}					t_texture;

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
	double	y_player;
	double	x_player;
	double	y_pplayer;
	double	x_pplayer;
	double	mxmap;
	double	mymap;
	double	pdx;
	double	pdy;
	double	pa;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	dv;
	double	dh;
	double	d;
	double	dx;
	double	dy;
	int		forward;
	int		left;
	int		backward;
	int		right;
	int		rleft;
	int		rright;
	t_texture	texture;
}				t_data;

unsigned int	get_image_pixel(t_data *data, int x, int y);
void	init_max_map(t_data *data);
void	ft_init_hv(t_data *data);
void	ft_init_player(t_data *data);
void	check_vertical(t_data *data);
void	check_horizontal(t_data *data);
void	ft_player(t_data *data, int x, int y, int color);
int		ft_imprim(t_data *data);
int		is_map_valid(t_data *data);
void	ft_render(int height, double p_wall, int x, t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
void	ft_rotate_r(t_data *data);
void	ft_rotate_l(t_data *data);
void	ft_move_f(t_data *data, double pdx, double pdy);
void	ft_move_b(t_data *data, double pdx, double pdy);
void	ft_move_l(t_data *data, double pdx, double pdy);
void	ft_move_r(t_data *data, double pdx, double pdy);
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
