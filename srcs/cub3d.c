/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/08 21:02:19 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_minimap(t_data *data)
{
	int	y;
	int	x;
	int	offset;

	y = 0;
	x = 0;
	offset = 1;
	while (data->map[y][x])
	{
		while (data->map[y][x])
		{
			if (is_charset(data->map[y][x], "02SEWN"))
				ft_square(data, x + offset, y + offset, 0x40FF0000);
			if (data->map[y][x] == '1')
				ft_square(data, x + offset, y + offset, 0x40FFFFFF);
			x++;
		}
		x = 0;
		y++;
	}
	ft_player(data, floor(data->x_pplayer/64) + offset, floor(data->y_pplayer/64) + offset, 0x40FFFF00);
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
	width = data->width;
	ft_move(data);
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
		p_wall = ceil((SIZE / data->d) * (data->width / 2) / tan(FOV2 * DTOR));
		ft_render(p_wall, x++, data);
		data->pa += (FOV * DTOR/ data->width);
		data->pa = data->pa < 0 ? 2 * PI + data->pa : data->pa;
		data->pa = data->pa > 2 * PI ? data->pa - 2 * PI : data->pa;
	}
	x = 0;
	data->pa = i;
	ft_minimap(data);
	// printf("x:[%f] y:[%f] vx:[%.2f] vy:[%.2f] hx:[%.2f] hy:[%.2f] dh:[%.2f] dv:[%.2f] a:[%f]\n", data->x_pplayer, data->y_pplayer, data->vx,data->vy ,data->hx ,data->hy ,data->dh,data->dv ,data->pa);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	int				fd;
	int				y;
	int				x;
	int				ret;
	char			*line;
	t_data			data;

	y = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (ret != 0)
		{
			ret = get_next_line(fd, &line) > 0;
			if (*line == '\n')
				;
			else if (*line == 'R' && *(line + 1) == ' ')
				is_resolution_valid(line + 2, &data);
			else if (((*line == 'N' && *(line + 1) == '0') || (*line == 'S' && *(line + 1) == '0') ||
				(*line == 'W' && *(line + 1) == 'E') || (*line == 'E' && *(line + 1) == 'A')) &&
				(*(line + 2) == ' '))
				ft_texture_path();
			else if (*line == 'S' && *(line + 1) == ' ')
				ft_sprite_path();
			else if ((*line == 'F' && *(line + 1) == ' ') || (*line == 'C' && *(line + 1) == ' '))
				is_ceil_floor_color();
			else
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
		mlx_get_screen_size(data.mlx_ptr, &data.screenx, &data.screeny);
		data.width = (WIDTH > data.screenx) ? data.screenx : WIDTH;
		data.height = (HEIGHT > data.screeny) ? data.screeny : HEIGHT;
		data.mlx_win = mlx_new_window(data.mlx_ptr, data.width, data.height, "Hello world!");
		ft_init_texture(&data);
		data.img = mlx_new_image(data.mlx_ptr, data.width, data.height);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
		mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &data);
		mlx_hook(data.mlx_win, 3, 1L<<1, key_release, &data);
		mlx_hook(data.mlx_win, 33, 1L << 17, ft_exit, &data);
		mlx_loop_hook(data.mlx_ptr, ft_imprim, &data);
		mlx_loop(data.mlx_ptr);
	}
	return (0);
}
