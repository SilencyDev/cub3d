/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:42:28 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/06 17:35:18 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_square(t_data *data, int x, int y, int color)
{
	int x_max;
	int y_max;
	int i;
	int j;

	x_max = x * 8;
	y_max = y * 8;
	i = 0;
	j = 0;
	while (i < 8)
	{
		while (j < 8)
		{
			my_mlx_pixel_put(data, x_max + j, y_max + i, color);
			if (i < 1 || i > 7 ||
				j < 1 || j > 7)
				my_mlx_pixel_put(data, x_max + j, y_max + i, 0x10000000);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_player(t_data *data, int x, int y, int color)
{
	int x_max;
	int y_max;
	int i;
	int j;

	x_max = x * 8;
	y_max = y * 8;
	i = 0;
	j = 0;
	while (i < 8)
	{
		while (j < 8)
		{
			my_mlx_pixel_put(data, x_max + j, y_max + i, color);
			if (i < 1 || i > 7 ||
				j < 1 || j > 7)
				my_mlx_pixel_put(data, x_max + j, y_max + i, 0x10000000);
			j++;
		}
		j = 0;
		i++;
	}
}
