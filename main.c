/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/25 13:10:35 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_charset(char c, char *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (c);
	return (0);
}

void	ft_print_tab(t_data *data)
{
	int	y;
	int x;

	x = 0;
	y = 0;
	while (data->map[y][x])
	{
		while (data->map[y][x])
			printf("%c", data->map[y][x++]);
		printf("\n");
		x = 0;
		y++;
	}
}

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
	ft_print_tab(data);
	return (1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_square(t_data *data, int x, int y, int color)
{
	int x_max;
	int y_max;
	int i;
	int j;

	x_max = x * 20;
	y_max = y * 20;
	i = j = 0;
	while (i < 20)
	{
		while (j < 20)
			my_mlx_pixel_put(data, x_max + j++, y_max + i, color);
		j = 0;
		i++;
	}
}

void	ft_direction_n(t_data *data, int x, int y, int color)
{
	int x_max;
	int y_max;
	int i;
	int j;

	x_max = x * 20;
	y_max = y * 20;
	i = j = 0;
	while (i < 20)
	{
		if (i < 5)
			while (j < 20)
				my_mlx_pixel_put(data, x_max + j++, y_max + i, color);
		j = 0;
		i++;
	}
}

void	ft_direction_s(t_data *data, int x, int y, int color)
{
	int x_max;
	int y_max;
	int i;
	int j;

	x_max = x * 20;
	y_max = y * 20;
	i = j = 0;
	while (i < 20)
	{
		if (i > 15)
			while (j < 20)
				my_mlx_pixel_put(data, x_max + j++, y_max + i, color);
		j = 0;
		i++;
	}
}

void	ft_direction_e(t_data *data, int x, int y, int color)
{
	int x_max;
	int y_max;
	int i;
	int j;

	x_max = x * 20;
	y_max = y * 20;
	i = j = 0;
	while (i < 20)
	{
		while (j < 20)
		{
			if (j > 15)
				my_mlx_pixel_put(data, x_max + j, y_max + i, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_direction_w(t_data *data, int x, int y, int color)
{
	int x_max;
	int y_max;
	int i;
	int j;

	x_max = x * 20;
	y_max = y * 20;
	i = j = 0;
	while (i < 20)
	{
		while (j < 20)
		{
			if (j < 5)
				my_mlx_pixel_put(data, x_max + j, y_max + i, color);
			j++;
		}
		j = 0;
		i++;
	}
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == FORWARD)
		data->forward = 0;
	else if (keycode == LEFT)
		data->left = 0;
	else if (keycode == BACKWARD)
		data->backward = 0;
	else if (keycode == RIGHT)
		data->right = 0;
	else if (keycode == RLEFT)
		data->rleft = 0;
	else if (keycode == RRIGHT)
		data->rright = 0;
	printf("%s\n", "release");
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == FORWARD)
		data->forward = 1;
	else if (keycode == LEFT)
		data->left = 1;
	else if (keycode == BACKWARD)
		data->backward = 1;
	else if (keycode == RIGHT)
		data->right = 1;
	else if (keycode == RLEFT)
		data->rleft = 1;
	else if (keycode == RRIGHT)
		data->rright = 1;
	printf("%s\n", "press");
	return (1);
}

void	ft_move(t_data *data)
{
	if (data->forward)
	{
		if (data->player == 'N' && (data->map[data->y_player - 1][data->x_player] == '0'))
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[--data->y_player][data->x_player] = 'N';
		}
		else if (data->player == 'S' && (data->map[data->y_player + 1][data->x_player] == '0'))
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[++data->y_player][data->x_player] = 'S';
		}
		else if (data->player == 'E' && (data->map[data->y_player][data->x_player + 1] == '0'))
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[data->y_player][++data->x_player] = 'E';
		}
		else if (data->player == 'W' && (data->map[data->y_player][data->x_player - 1] == '0'))
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[data->y_player][--data->x_player] = 'W';
		}
		data->forward = 0;
	}
	if (data->backward)
	{
		if (data->player == 'N' && (data->map[data->y_player + 1][data->x_player] == '0'))
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[++data->y_player][data->x_player] = 'N';
		}
		else if (data->player == 'S' && (data->map[data->y_player - 1][data->x_player] == '0'))
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[--data->y_player][data->x_player] = 'S';
		}
		else if (data->player == 'E' && (data->map[data->y_player][data->x_player - 1] == '0'))
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[data->y_player][--data->x_player] = 'E';
		}
		else if (data->player == 'W' && (data->map[data->y_player][data->x_player + 1] == '0'))
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[data->y_player][++data->x_player] = 'W';
		}
		data->backward = 0;
	}
	if (data->left)
	{
		if (data->player == 'N' && data->map[data->y_player][data->x_player - 1] == '0')
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[data->y_player][--data->x_player] = 'N';
		}
		else if (data->player == 'S' && data->map[data->y_player][data->x_player + 1] == '0')
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[data->y_player][++data->x_player] = 'S';
		}
		else if (data->player == 'E' && data->map[data->y_player - 1][data->x_player] == '0')
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[--data->y_player][data->x_player] = 'E';
		}
		else if (data->player == 'W' && data->map[data->y_player + 1][data->x_player] == '0')
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[++data->y_player][data->x_player] = 'W';
		}
		data->left = 0;
	}
	if (data->right)
	{
		if (data->player == 'N' && data->map[data->y_player][data->x_player + 1] == '0')
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[data->y_player][++data->x_player] = 'N';
		}
		else if (data->player == 'S' && data->map[data->y_player][data->x_player - 1] == '0')
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[data->y_player][--data->x_player] = 'S';
		}
		else if (data->player == 'E' && data->map[data->y_player + 1][data->x_player] == '0')
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[++data->y_player][data->x_player] = 'E';
		}
		else if (data->player == 'W' && data->map[data->y_player - 1][data->x_player] == '0')
		{
			data->map[data->y_player][data->x_player] = '0';
			data->map[--data->y_player][data->x_player] = 'W';
		}
		data->right = 0;
	}
	if (data->rright)
	{
		if (data->player == 'N')
			data->player = 'E';
		else if (data->player == 'E')
			data->player = 'S';
		else if (data->player == 'S')
			data->player = 'W';
		else if (data->player == 'W')
			data->player = 'N';
		data->rright = 0;
	}
	if (data->rleft)
	{
		if (data->player == 'N')
			data->player = 'W';
		else if (data->player == 'W')
			data->player = 'S';
		else if (data->player == 'S')
			data->player = 'E';
		else if (data->player == 'E')
			data->player = 'N';
		data->rleft = 0;
	}
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

void	ft_init(t_data *data)
{
	data->left = 0;
	data->rleft = 0;
	data->right = 0;
	data->rright = 0;
	data->forward = 0;
	data->backward = 0;
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
		data.mlx_win = mlx_new_window(data.mlx_ptr, 500, 500, "Hello world!");
		data.img = mlx_new_image(data.mlx_ptr, 500, 500);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
		mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &data);
		mlx_hook(data.mlx_win, 3, 1L<<1, key_release, &data);
		mlx_loop_hook(data.mlx_ptr, ft_imprim, &data);
		printf("voici : [%d]", data.x_player);
		mlx_loop(data.mlx_ptr);
	}
	return (0);
}
