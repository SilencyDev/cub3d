/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:28:03 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 19:24:02 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				is_valid_to_left(t_data *data, int y, int x)
{
	static int	n = 0;

	x = x >= data->mxmap ? x - 1 : x;
	while (x >= 0 && data->map[y][x])
	{
		if (data->map[y][x] == '1')
			data->one = 1;
		if (data->map[y][x] == ' ')
			data->one = 0;
		if (data->one == 0 && is_charset(data->map[y][x], "02NSEW"))
			return (0);
		if (data->map[y][x] == '2')
		{
			data->sprite[n].sy = y * 64 + 32;
			data->sprite[n].sx = x * 64 + 32;
			n++;
		}
		x--;
	}
	data->one = 0;
	return (1);
}

int				is_valid_to_right(t_data *data, int y, int x)
{
	while (data->map[y][x])
	{
		if (data->map[y][x] == '1')
			data->one = 1;
		if (data->map[y][x] == ' ')
			data->one = 0;
		if (!is_charset(data->map[y][x], "012 NSEW")
			|| (data->one == 0 && !is_charset(data->map[y][x], "1 ")))
			return (0);
		if (is_charset(data->map[y][x], "NSEW"))
		{
			data->nb_player += 1;
			if (data->nb_player > 1)
				return (0);
			data->player = is_charset(data->map[y][x], "NSEW");
			data->y_player = y;
			data->x_player = x;
		}
		if (x + 1 > data->mxmap && data->map[y][x] != '1')
			return (0);
		x++;
	}
	data->one = 0;
	if (!is_valid_to_left(data, y, x))
		return (0);
	return (1);
}

int				is_valid_to_top(t_data *data, int y, int x)
{
	y = y >= 0 ? y - 1 : y;
	while (y >= 0 && data->map[y][x])
	{
		if (data->map[y][x] == '1')
			data->one = 1;
		if (data->one == 0 && is_charset(data->map[y][x], "02NSEW"))
			return (0);
		y--;
	}
	data->one = 0;
	return (1);
}

int				is_valid_to_bottom(t_data *data, int y, int x)
{
	while (y < data->mymap && data->map[y][x])
	{
		if (data->map[y][x] == '1')
			data->one = 1;
		if (data->map[y][x] == ' ')
			data->one = 0;
		if (!is_charset(data->map[y][x], "012 NSEW")
			|| (data->one == 0 && !is_charset(data->map[y][x], "1 ")))
			return (0);
		if (y + 1 > data->mymap && data->map[y][x] != '1')
			return (0);
		y++;
	}
	data->one = 0;
	if (!is_valid_to_top(data, y, x))
		return (0);
	return (1);
}
