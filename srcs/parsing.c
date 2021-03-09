/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:53:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/09 14:50:18 by kmacquet         ###   ########.fr       */
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
	str = ft_split_str(s, " 	\t\v\r\f\n");
	while (str[i])
			i++;
	if (i > 2)
		ft_error("Resolution parameters incorrect");
	data->width = ft_atoi(str[0]);
	data->height = ft_atoi(str[1]);
	while (--i >= 0)	
		free(str[i]);
	free(str);
	if (data->width <= 0 || data->height <= 0)
		ft_error("Resolution parameters can't be negative or equal to 0");
	return (1);
}

int	is_ceil_floor_color(char *s, t_data *data)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	str = ft_split_str(s, " 	,\t\v\r\f\n");
	while (str[i])
		i++;
	if (i > 4)
		ft_error("Resolution parameters incorrect");
	data->color.rgb = (ft_atoi(str[1])<<16 | ft_atoi(str[2])<<8 | ft_atoi(str[3]));
	if (str[0][0] == 'F')
		data->f = data->color.rgb;
	else
		data->c = data->color.rgb;
	while (--i >= 0)	
		free(str[i]);
	free(str);
	if (data->screenx < 0 || data->screeny < 0)
		ft_error("Color parameters can't be negative");
	return (1);
}

int	recup_path(char *s, t_data *data)
{
	int	i;
	int	j;
	char **str;

	i = 0;
	j = 0;
	str = ft_split_str(s, " 	\t\v\r\f\n");
	while (str[i])
			i++;
	if (i > 2)
		ft_error("Path parameters incorrect");
	if (str[0][0] == 'S' && !str[0][1])
		data->texture[4].path = str[1];
	else if (str[0][0] == 'N' && str[0][1] == 'O')
		data->texture[0].path = str[1];
	else if (str[0][0] == 'S' && str[0][1] == 'O')
		data->texture[2].path = str[1];
	else if (str[0][0] == 'E' && str[0][1] == 'A')
		data->texture[1].path = str[1];
	else if (str[0][0] == 'W' && str[0][1] == 'E')
		data->texture[3].path = str[1];
	free(str);
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
