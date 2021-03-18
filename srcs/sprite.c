/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:39:28 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/18 17:53:37 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_sprite(double p_sprite, int x, int n, t_data *data)
{
	int		height;
	double	offset;
	double	i;
	int		j;

	i = 1;
	offset = (p_sprite - data->height) / 2;
	height = data->height - 1;
	while (height)
	{
		j = p_sprite / 2;
		if ((height < data->height / 2 - (p_sprite / 2) + p_sprite)
			&& (height > data->height / 2 - p_sprite / 2))
		{
			if (p_sprite > data->height)
			{
				while (j)
				{
					if ((x - j + 1) > 0 && (data->sprite[n].d < data->d[x - j + 1]))
						my_mlx_pixel_put(data, x - j + 1, height, 0x00FFFFFF);
					j--;
				}
				j = p_sprite / 2;
				while (j)
				{
					if ((x + j - 1) < data->width && (data->sprite[n].d < data->d[x + j - 1]))
						my_mlx_pixel_put(data, x + j - 1, height, 0x00FFFFFF);
					j--;
				}
			}
			else
			{
				while (j)
				{
					if ((x - j + 1) > 0 && (data->sprite[n].d < data->d[x - j + 1]))
						my_mlx_pixel_put(data, x - j + 1, height, 0x00FFFFFF);
					j--;
				}
				j = p_sprite / 2;
				while (j)
				{
					if ((x + j - 1) < data->width && (data->sprite[n].d < data->d[x + j - 1]))
						my_mlx_pixel_put(data, x + j - 1, height, 0x00FFFFFF);
					j--;
				}
			}
			i++;
		}
		height--;
	}
}

void	sprite(t_data *data)
{
	int		n;
	double	beta;
	double	alpha;
	int		x;
	int		p_sprite;

	n = 0;
	while (n < data->nb_sprite)
	{
		beta = atan2(data->sprite[n].sy - data->y_pplayer
		,data->sprite[n].sx - data->x_pplayer);
		alpha = (data->pa + (FOV/2 * DTOR)) + beta;
		alpha = ceil(alpha) >= (2.0 * PI) ? alpha - (2.0 * PI) : alpha;
		// alpha = floor(alpha) < 0.0 ? alpha + (2.0 * PI) : alpha;
		x = floor(alpha * data->width / (FOV * DTOR));
		p_sprite = ceil((SIZE / data->sprite[n].d) * (data->width / 2)
		/ tan(FOV2 * DTOR));
		print_sprite(p_sprite, x, n, data);
		printf("[n:%d][x:%d] [p_sprite:%d] [beta:%f] [alpha:%f] [pa:%f] [sx:%f]\n", n, x, p_sprite, beta * RTOD, alpha * RTOD, data->pa * RTOD, data->sprite[n].sx);
		n++;
	}
}

void	order_sprite(t_data *data)
{
	int n;
	int j;
	double tmp;

	tmp = 0;
	n = 0;
	while (n < data->nb_sprite - 1)
	{
		j = n + 1;
		while (j < data->nb_sprite)
		{
			if (data->sprite[n].d < data->sprite[j].d)
			{
				tmp = data->sprite[n].d;
				data->sprite[n].d = data->sprite[j].d;
				data->sprite[j].d = tmp;
				tmp = data->sprite[n].sx;
				data->sprite[n].sx = data->sprite[j].sx;
				data->sprite[j].sx = tmp;
				tmp = data->sprite[n].sy;
				data->sprite[n].sy = data->sprite[j].sy;
				data->sprite[j].sy = tmp;
			}
			j++;
		}
		n++;
	}
}

void	set_sprite_distance(t_data *data)
{
	int n;

	n = 0;
	while (n < data->nb_sprite)
	{
		data->sprite[n].d = sqrt(pow(data->sprite[n].sx - data->x_pplayer, 2)
		+ pow(data->sprite[n].sy - data->y_pplayer, 2));
		n++;
	}
	order_sprite(data);
}
