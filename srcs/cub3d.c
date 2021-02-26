/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/26 10:43:08 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_valid(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	data->one = 0;
	data->nb_player = 0;
	while (data->map[y][x])
	{
		while (data->map[y][x] == ' ')
			x++;
		while (data->map[y][x])
		{
			if (!is_charset(data->map[y][x], "012 NSEW") || (data->one == 0 && !is_charset(data->map[y][x], "1 ")))
				return (0);
			if (data->map[y][x] == '1')
				data->one = 1;
			if (data->map[y][x] == ' ')
				data->one = 0;
			if (is_charset(data->map[y][x], "NSEW"))
			{
				data->nb_player += 1;
				if (data->nb_player > 1)
					return (0);
				data->player = is_charset(data->map[y][x], "NSEW");
				data->y_player = y;
				data->x_player = x;
			}
			if (data->map[y][x++] == '0' && y == 0)
				return (0);
		}
		data->one = 0;
		while (data->map[y][--x])
		{
			if (data->map[y][x] == '1')
				data->one = 1;
			if (data->one == 0 && is_charset(data->map[y][x], "02NSEW"))
				return (0);
		}
		data->one = 0;
		y++;
		x = 0;
	}
	if (!is_charset(data->player, "NSEW"))
		return (0);
	while (data->map[y - 2][x])
	{
		if (data->map[y - 2][x] == '0')
			if (data->map[y - 1][x] != '1')
				return (0);
		x++;
	}
	return (1);
}

int	ft_imprim(t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	ft_move(data);
	while (data->map[y][x])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0')
				ft_square(data, x, y, 0x00FF0000);
			if (data->map[y][x] == '1')
				ft_square(data, x, y, 0x50FFFFFF);
			if (is_charset(data->map[y][x], "SWEN"))
			{
				ft_square(data, x, y, 0x000000FF);
				if (data->player == 'N')
					ft_direction_n(data, x, y, 0x00FFFF00);
				else if (data->player == 'S')
					ft_direction_s(data, x, y, 0x00FFFF00);
				else if (data->player == 'E')
					ft_direction_e(data, x, y, 0x00FFFF00);
				else
					ft_direction_w(data, x, y, 0x00FFFF00);
			}
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (1);
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
			printf("%c",'\n');
			x = 0;
			y++;
		}
		data.map[y][x] = '\0';
		close(fd);
		if (!is_map_valid(&data))
		{
			printf("la map est invalide");
			return (-1);
		}
		ft_init(&data);
		data.mlx_ptr = mlx_init();
		data.mlx_win = mlx_new_window(data.mlx_ptr, 650, 650, "Hello world!");
		data.img = mlx_new_image(data.mlx_ptr, 650, 650);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
		mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &data);
		mlx_hook(data.mlx_win, 3, 1L<<1, key_release, &data);
		mlx_loop_hook(data.mlx_ptr, ft_imprim, &data);
		mlx_loop(data.mlx_ptr);
	}
	return (0);
}
