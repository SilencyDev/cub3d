/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:32:22 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/19 18:54:02 by kmacquet         ###   ########.fr       */
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
# include "mlx.h"
# include <math.h>
# include <limits.h>
# include <float.h>

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
# define WIDTH 1080
# define HEIGHT 720
# define FOV 60.0
# define SPEED 5
# define PI 3.141592653589793
# define N 1.570796326790000
# define E 0.0
# define S 4.71238898038
# define W PI
# define DTOR 0.01745329251
# define RTOD 57.2957795131
# define SIZE 64.0

typedef struct	s_texture
{
	void		*img_ptr;
	void		*addr_ptr;
	int			img_width;
	int			img_height;
	int			bits_per_pixel_t;
	int			line_length_t;
	int			endian_t;
	char		*path;
}				t_texture;

typedef struct	s_sprite
{
	double		sx;
	double		sy;
	double		d;
}				t_sprite;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
	int			rgb;
}				t_color;

typedef struct	s_data
{
	int			n;
	int			offset;
	int			p_wall;
	int			p_sprite;
	int			save;
	int			screenx;
	int			screeny;
	int			f;
	int			c;
	char		*n_path;
	char		*s_path;
	char		*w_path;
	char		*e_path;
	int			nb_sprite;
	char		*sprite_path;
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	int			one;
	char		player;
	int			nb_player;
	double		width;
	double		height;
	double		y_player;
	double		x_player;
	double		y_pplayer;
	double		x_pplayer;
	double		mxmap;
	double		mymap;
	double		pdx;
	double		pdy;
	double		pa;
	double		hx;
	double		hy;
	double		vx;
	double		vy;
	double		dv;
	double		dh;
	double		*d;
	double		dx;
	double		dy;
	int			forward;
	int			left;
	int			backward;
	int			right;
	int			rleft;
	int			rright;
	t_color		color;
	t_texture	texture[5];
	t_sprite	*sprite;
}				t_data;

void			print_sprite1(t_data *data, int height, int i, int x);
void			print_sprite1_bis(t_data *data, int height, int i, int x);
void			print_sprite2(t_data *data, int height, int i, int x);
void			print_sprite2_bis(t_data *data, int height, int i, int x);
void			check_vertical2(t_data *data, double ya, double xa);
void			check_horizontal2(t_data *data, double ya, double xa);
void			ft_render2(t_data *data, int x, int h, int i);
void			print_sprite(double p_sprite, int x, int n, t_data *data);
void			angle_limit(double *data);
void			sprite(t_data *data);
void			set_sprite_distance(t_data *data);
void			order_sprite(t_data *data);
int				is_valid_to_left(t_data *data, int y, int x);
int				is_valid_to_right(t_data *data, int y, int x);
void			ft_parsing_setting(t_data *data, int fd);
int				count_max_map(char *line, t_data *data, int y);
void			ft_save(t_data *data);
void			ft_header(t_data *data, int fd);
int				ft_wall_size(t_data *data, double iangle, int width);
void			ft_mlx(t_data *data);
void			ft_parsing_map(t_data *data, int fd);
int				set_map(char *line, t_data *data, int y);
int				is_save(char *s);
void			ft_error(char *s);
int				recup_path(char *s, t_data *data);
int				is_empty_line(char *str, char *charset);
char			**ft_split_str(char *s, char *charset);
int				ft_atoi(char *str);
int				ft_countword(char *str, char *charset);
void			ft_strcpy(char *start, char *str, char *dest);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
int				is_ceil_floor_color(char *s, t_data *data);
int				is_resolution_valid(char *s, t_data *data);
void			ft_init_texture(t_data *data);
void			ft_minimap(t_data *data);
int				ft_exit(t_data *data);
unsigned int	get_image_pixel(t_data *data, int x, int y, int n);
void			init_max_map(t_data *data);
void			ft_init_player(t_data *data);
void			check_vertical(t_data *data);
void			check_horizontal(t_data *data);
void			ft_player(t_data *data, int x, int y, int color);
int				ft_imprim(t_data *data);
int				is_map_valid(t_data *data);
void			ft_render(double p_wall, int x, t_data *data);
int				key_release(int keycode, t_data *data);
int				key_press(int keycode, t_data *data);
void			ft_rotate_r(t_data *data);
void			ft_rotate_l(t_data *data);
void			ft_move_f(t_data *data, double pdx, double pdy);
void			ft_move_b(t_data *data, double pdx, double pdy);
void			ft_move_l(t_data *data, double pdx, double pdy);
void			ft_move_r(t_data *data, double pdx, double pdy);
void			ft_move(t_data *data);
void			ft_square(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_init(t_data *data);
void			ft_print_tab(t_data *data);
char			is_charset(char c, char *charset);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
int				ft_strlen(const char *str);
char			*ft_memalloc(size_t size);
void			*ft_memset(void *b, int c, size_t len);
int				ft_memdel(char **ptr);
int				get_next_line(int fd, char **line);

#endif
