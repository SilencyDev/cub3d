/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:53:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/08 22:31:55 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *s)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
	exit(1);
}

int	is_resolution_valid(char *s, t_data *data)
{
	int	i;
	int	j;
	char **str;

	i = 0;
	j = 0;
	str = ft_split_str(*s, " 	\t\v\r\f");
	while (str[i][j])
		j++;
	if (j > 2)
		ft_error("Resolution parameters incorrect");
	data->screenx = ft_atoi(str[0]);
	data->screeny = ft_atoi(str[1]);
	while (--j >= 0)	
		free(str[j]);
	free(str);
	if (data->screenx <= 0 || data->screeny <= 0)
		ft_error("Resolution parameters can't be negative or equal to 0");
	return (1);
}

int	is_ceil_floor_color(char *s, t_data *data)
{
	int		i;
	int		j;
	char	**str;
	char	*tmp;
	char	*color;

	i = 0;
	j = 0;
	str = ft_split_str(*s, " 	,\t\v\r\f");
	while (str[i][j])
		j++;
	if (j > 4)
		ft_error("Resolution parameters incorrect");
	// function to change base here
	tmp = ft_strjoin(str[1], str[2]);
	color = ft_strjoin(tmp, str[3]);
	free(tmp);
	if (str[0] == 'F')
		data->f = color;
	else
		data->c = color;
	free(color);
	while (--j >= 0)	
		free(str[j]);
	free(str);
	if (data->screenx < 0 || data->screeny < 0)
		ft_error("Color parameters can't be negative");
	return (1);
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
			if (data->map[y][x] == '2')
			{
				data->sprite.sx = x * 64 + 32;
				data->sprite.sy = y * 64 + 32;
			}
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
