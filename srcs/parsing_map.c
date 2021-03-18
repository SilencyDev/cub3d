/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:47:43 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/18 10:16:49 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_map_valid(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (!(data->sprite = malloc(sizeof(t_sprite) * data->nb_sprite)))
		ft_error("Sprite couldn't be malloc");
	while (y < data->mymap && data->map[y][x])
	{
		if (!is_valid_to_right(data, y, x))
			return (0);
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

int			is_valid_to_left(t_data *data, int y, int x)
{
	static int n = 0;

	while (x >= 0 && data->map[y][--x])
	{
		if (data->map[y][x] == '1')
			data->one = 1;
		if (data->one == 0 && is_charset(data->map[y][x], "02NSEW"))
			return (0);
		if (data->map[y][x] == '2')
		{
			data->sprite[n].sy = y * 64 + 32;
			data->sprite[n].sx = x * 64 + 32;
			n++;
		}
	}
	data->one = 0;
	return (1);
}

int			is_valid_to_right(t_data *data, int y, int x)
{
	while (data->map[y][x])
	{
		if (!is_charset(data->map[y][x], "012 NSEW")
			|| (data->one == 0 && !is_charset(data->map[y][x], "1 ")))
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
	if (!is_valid_to_left(data, y, x))
			return (0);
	return (1);
}

void		ft_parsing_map(t_data *data, int fd)
{
	int		ret;
	int		y;
	char	*l;

	ret = 1;
	y = 0;
	if (!(data->map = malloc(sizeof(char*) * (int)data->mymap + 1)))
		ft_error("Malloc of map failed");
	while (ret != 0)
	{
		ret = get_next_line(fd, &l) > 0;
		if (is_empty_line(l, " 	\t\v\r\f\n")
			|| (*l == 'R' && is_charset(*(l + 1), " 	\t\v\r\f\n"))
			|| (*l == 'F' && is_charset(*(l + 1), " 	\t\v\r\f\n"))
			|| (*l == 'C' && is_charset(*(l + 1), " 	\t\v\r\f\n"))
			|| ((*l == 'N' && *(l + 1) == 'O') || (*l == 'S' && *(l + 1) == 'O')
			|| (*l == 'W' && *(l + 1) == 'E') || ((*l == 'E' && *(l + 1) == 'A')
			&& is_charset(*(l + 2), " 	\t\v\r\f\n")))
			|| (*l == 'S' && is_charset(*(l + 1), " 	\t\v\r\f\n")))
			;
		else
			y = set_map(l, data, y);
	}
	data->map[y] = NULL;
	close(fd);
}
