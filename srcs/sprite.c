/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:39:28 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/19 17:49:22 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		sprite(t_data *data)
{
	int		n;
	double	beta;
	double	alpha;
	int		x;
	int		p_sprite;

	n = 0;
	while (n < data->nb_sprite)
	{
		beta = atan2(data->sprite[n].sy - data->y_pplayer,
		data->sprite[n].sx - data->x_pplayer);
		alpha = (data->pa + (FOV / 2 * DTOR)) + beta;
		alpha = ceil(alpha) >= (2.0 * PI) ? alpha - (2.0 * PI) : alpha;
		x = floor(alpha * data->width / (FOV * DTOR));
		p_sprite = ceil((SIZE / data->sprite[n].d) * (data->width / 2)
		/ tan(FOV / 2 * DTOR));
		print_sprite(p_sprite, x, n++, data);
	}
}

void		order_sprite(t_data *data)
{
	int		n;
	int		j;
	double	tmp;

	tmp = 0;
	n = -1;
	while (n++ < data->nb_sprite - 1)
	{
		j = n;
		while (++j < data->nb_sprite)
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
		}
	}
}

void		set_sprite_distance(t_data *data)
{
	int	n;

	n = 0;
	while (n < data->nb_sprite)
	{
		data->sprite[n].d = sqrt(
		pow(data->sprite[n].sx - data->x_pplayer, 2)
		+ pow(data->sprite[n].sy - data->y_pplayer, 2));
		n++;
	}
	order_sprite(data);
}
