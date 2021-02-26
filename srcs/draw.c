/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:42:28 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/26 10:18:43 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_square(t_data *data, int x, int y, int color)
{
	int x_max;
	int y_max;
	int i;
	int j;

	x_max = x * 64;
	y_max = y * 64;
	i = 0;
	j = 0;
	while (i < 64)
	{
		while (j < 64)
		{
			my_mlx_pixel_put(data, x_max + j, y_max + i, color);
			if (i < 1 || i > 63 ||
				j < 1 || j > 63)
				my_mlx_pixel_put(data, x_max + j, y_max + i, 0x10000000);
			j++;
		}
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

	x_max = x * 64;
	y_max = y * 64;
	i = 0;
	j = 0;
	while (i < 64)
	{
		if (i < 64 / 4)
			while (j < 64)
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

	x_max = x * 64;
	y_max = y * 64;
	i = 0;
	j = 0;
	while (i < 64)
	{
		if (i > (3 * 64) / 4)
			while (j < 64)
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

	x_max = x * 64;
	y_max = y * 64;
	i = 0;
	j = 0;
	while (i < 64)
	{
		while (j < 64)
		{
			if (j > (3 * 64) / 4)
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

	x_max = x * 64;
	y_max = y * 64;
	i = 0;
	j = 0;
	while (i < 64)
	{
		while (j < 64)
		{
			if (j < 64 / 4)
				my_mlx_pixel_put(data, x_max + j, y_max + i, color);
			j++;
		}
		j = 0;
		i++;
	}
}
