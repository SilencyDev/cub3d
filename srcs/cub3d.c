/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/05 17:08:55 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_image_pixel(t_data *data, int x, int y, int n)
{
	char	*dst;

	dst = data->texture[n].addr_ptr + (y * data->texture[n].line_length_t + x * (data->texture[n].bits_per_pixel_t / 8));
	return (*(unsigned int*)dst);
}

void	ft_render(double p_wall, int x, t_data *data)
{
	int	height;
	double	i;
	int n;

	height = HEIGHT;
	i = 0;
	n = 0;
	while (height)
	{
		if ((height < (HEIGHT / 2 - (p_wall / 2) + p_wall)) && (height > (HEIGHT / 2 - p_wall / 2)))
		{
			if (data->dh >= data->dv)
			{
				n = cos(data->pa) > 0 ? 1 : 3;
				my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dy % 64, (int)round((p_wall - i))* 64 / p_wall, n));
			}
			else
			{
				n = sin(data->pa) > 0 ? 0 : 2;
				my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dx % 64 , (int)round((p_wall - i))* 64 / p_wall, n));
			}
			i++;
		}
		else if (!(height < (HEIGHT / 2 - (p_wall / 2) + p_wall)))
			my_mlx_pixel_put(data, x, height, 0x00FF0000);
		else
			my_mlx_pixel_put(data, x, height, 0x00909090);
		height--;
	}
}

int	ft_imprim(t_data *data)
{
	// int	y;
	int	x;
	int		width;
	double	i;
	int		p_wall;

	// y = 0;
	x = 0;
	i = 0;
	width = WIDTH;
	ft_move(data);
	// while (data->map[y][x])
	// {
	// 	while (data->map[y][x])
	// 	{
	// 		if (is_charset(data->map[y][x], "0SEWN"))
	// 			ft_square(data, x, y, 0x00FF0000);
	// 		if (data->map[y][x] == '1')
	// 			ft_square(data, x, y, 0xFFFFFFFF);
	// 		if (is_charset(data->map[y][x], "SWEN"))
	// 		{
	// 			ft_square(data, x, y, 0x000000FF);
	// 			if (data->player == 'N')
	// 				ft_direction_n(data, x, y, 0x00FFFF00);
	// 			else if (data->player == 'S')
	// 				ft_direction_s(data, x, y, 0x00FFFF00);
	// 			else if (data->player == 'E')
	// 				ft_direction_e(data, x, y, 0x00FFFF00);
	// 			else
	// 				ft_direction_w(data, x, y, 0x00FFFF00);
	// 		}
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	i = data->pa;
	data->pa -= (FOV/2)* DTOR;
	while (width--)
	{
		ft_init_hv(data);
		check_horizontal(data);
		check_vertical(data);
		data->dv = fabs((data->x_pplayer - data->vx)/cos(data->pa));
		data->dh = fabs((data->x_pplayer - data->hx)/cos(data->pa));
		data->dx = data->dv < data->dh ? data->vx : data->hx;
		data->dy = data->dv < data->dh ? data->vy : data->hy;
		data->d = data->dv < data->dh ? data->dv : data->dh;
		data->d = data->d * cos(i - data->pa);
		p_wall = ceil((SIZE / data->d) * DPROJ);
		ft_render(p_wall, x, data);
		x++;
		data->pa += (FOV * DTOR/ WIDTH);
		data->pa = data->pa < 0 ? 2 * PI + data->pa : data->pa;
		data->pa = data->pa > 2 * PI ? data->pa - 2 * PI : data->pa;
	}
	x = 0;
	data->pa = i;
	// printf("x:[%f] y:[%f] vx:[%.2f] vy:[%.2f] hx:[%.2f] hy:[%.2f] dh:[%.2f] dv:[%.2f] a:[%f]\n", data->x_pplayer, data->y_pplayer, data->vx,data->vy ,data->hx ,data->hy ,data->dh,data->dv ,data->pa);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (1);
}

void ft_init_texture(t_data *data)
{
	int	n;
	char			relative_path[4][100] = 
	{"./textures/bricks.xpm",
	"./textures/bark.xpm",
	"./textures/coal.xpm",
	"./textures/stone.xpm"};

	n = 0;
	while (n < 4)
	{
		data->texture[n].img_height = 64;
		data->texture[n].img_width = 64;
		data->texture[n].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, relative_path[n], &data->texture[n].img_width, &data->texture[n].img_height);
		data->texture[n].addr_ptr = mlx_get_data_addr(data->texture[n].img_ptr, &data->texture[n].bits_per_pixel_t, &data->texture[n].line_length_t, &data->texture[n].endian_t);
		n++;
	}
}

int	main(int argc, char **argv)
{
	int				fd;
	int				y;
	int				x;
	char			*line;
	t_data			data;

	y = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			while (*line)
			{
				data.map[y][x] = *line++;
				printf("%c", data.map[y][x]);
				x++;
			}
			free(line - x);
			printf("%c",'\n');
			x = 0;
			y++;
		}
		data.map[y][x] = '\0';
		close(fd);
		ft_init(&data);
		if (!is_map_valid(&data))
		{
			printf("la map est invalide");
			return (-1);
		}
		ft_init_player(&data);
		data.mlx_ptr = mlx_init();
		data.mlx_win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Hello world!");
		ft_init_texture(&data);
		data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
		mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &data);
		mlx_hook(data.mlx_win, 3, 1L<<1, key_release, &data);
		mlx_loop_hook(data.mlx_ptr, ft_imprim, &data);
		mlx_loop(data.mlx_ptr);
		mlx_destroy_image(data.mlx_ptr, data.texture[0].img_ptr);
		mlx_destroy_image(data.mlx_ptr, data.texture[1].img_ptr);
		mlx_destroy_image(data.mlx_ptr, data.texture[2].img_ptr);
		mlx_destroy_image(data.mlx_ptr, data.texture[3].img_ptr);
	}
	return (0);
}
