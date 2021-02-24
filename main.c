/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/24 17:38:02 by kmacquet         ###   ########.fr       */
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

int	is_map_valid(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->one = 0;
	data->nb_player = 0;
	while (data->map[i][j])
	{
		while (data->map[i][j] == ' ')
			j++;
		while (data->map[i][j])
		{
			if (!is_charset(data->map[i][j], "012 NSEW"))
				return (0);
			if (data->map[i][j] == '1')
				data->one = 1;
			if (data->map[i][j] == ' ')
				data->one = 0;
			if (data->one == 0 && !is_charset(data->map[i][j], "1 "))
				return (0);
			if (is_charset(data->map[i][j], "NSEW"))
			{
				data->nb_player += 1;
				if (data->nb_player > 1)
					return (0);
				data->player = is_charset(data->map[i][j], "NSEW");
				data->i_player = i;
				data->j_player = j;
				data->map[i][j] = '0';
			}
			if (data->map[i][j++] == '0' && i == 0)
				return (0);
		}
		data->one = 0;
		while (data->map[i][--j])
		{
			if (data->map[i][j] == '1')
				data->one = 1;
			if (data->one == 0 && data->map[i][j] == '0')
				return (0);
		}
		data->one = 0;
		i++;
		j = 0;
	}
	if (!is_charset(data->player, "NSEW"))
		return (0);
	while (data->map[i - 2][j])
	{
		if (data->map[i - 2][j] == '0')
			if (data->map[i - 1][j] != '1')
				return (0);
		j++;
	}
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
		{
			my_mlx_pixel_put(data, x_max + i, y_max + j, color);
			j++;
		}
		j = 0;
		i++;
	}
}

int	key_hook(int keycode, t_data *data)
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
	printf("%d\n", keycode);
	return (1);
}

int	ft_imprim(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	mlx_key_hook(data->mlx_win, key_hook, &data);
	if (data->forward)
	{
		data->i_player = data->i_player - 1;
		data->forward = 0;
	}
	while (data->map[i][j])
	{
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0')
				ft_square(data, j, i, 0x00FF0000);
			if (data->map[i][j] == '1')
				ft_square(data, j, i, 0x50FFFFFF);
			j++;
		}
		j = 0;
		i++;
	}
	ft_square(data, data->j_player, data->i_player, 0x000000FF);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	int				fd;
	int				i;
	int				j;
	char			*line;
	t_data			data;

	i = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			while (*line)
			{
				data.map[i][j++] = *line++;
				printf("%c", data.map[i][j - 1]);
			}
			printf("%c",'\n');
			j = 0;
			i++;
		}
		data.map[i][j] = '\0';
		close(fd);
		if (!is_map_valid(&data))
		{
			printf("la map est invalide");
			return (-1);
		}
		data.mlx_ptr = mlx_init();
		data.mlx_win = mlx_new_window(data.mlx_ptr, 500, 500, "Hello world!");
		data.img = mlx_new_image(data.mlx_ptr, 500, 500);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
		mlx_loop_hook(data.mlx_ptr, ft_imprim, &data);
		mlx_loop(data.mlx_ptr);
	}
	return (0);
}
