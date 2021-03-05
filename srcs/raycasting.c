/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:51:53 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/05 13:52:28 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_horizontal(t_data *data)
{
	double	ya;
	double	xa;

	ya = SIZE;
	xa = 0;
	if (!sin(data->pa))
		data->hx = DBL_MAX;
	else
	{
		if (sin(data->pa) > 0)
		{
			data->hy = floor(data->y_pplayer/SIZE) * SIZE - 0.000000001;
			xa = SIZE / tan(data->pa);
			ya *= -1;
		}
		else if (sin(data->pa) < 0)
		{
			data->hy = floor(data->y_pplayer/SIZE) * SIZE + SIZE;
			xa = -SIZE / tan(data->pa);
		}
		data->hx = data->x_pplayer + (data->y_pplayer - data->hy)/tan(data->pa);
		if (data->mxmap > (int)floor((data->hx) / SIZE) && (int)floor((data->hx) / SIZE) > 0)
		{
			while (data->mymap > (int)floor((data->hy) / SIZE) &&
				data->map[(int)floor((data->hy) / SIZE)][(int)floor((data->hx) / SIZE)] &&
				data->map[(int)floor(data->hy / SIZE)][(int)floor(data->hx / SIZE)] != '1')
			{
				// printf("\nHfsy:[%f] Hfsx:[%f] xa:[%f] ya:[%f]\n\n", floor(data->hy / SIZE), floor((data->hx / SIZE)), xa ,ya);
				data->hx += xa;
				data->hy += ya;
			}
		}
	}
}

void	check_vertical(t_data *data)
{
	double	ya;
	double	xa;

	ya = 0;
	xa = SIZE;
	if (!cos(data->pa))
		data->vy = DBL_MAX;
	else
	{
		if (cos(data->pa) < 0)
		{
			data->vx = floor(data->x_pplayer/SIZE) * SIZE - 0.000000001;
			ya = SIZE * tan(data->pa);
			xa *= -1;
		}
		else if (cos(data->pa) > 0)
		{
			data->vx = floor(data->x_pplayer/SIZE) * SIZE + SIZE;
			ya = -SIZE * tan(data->pa);
		}
		data->vy = data->y_pplayer + (data->x_pplayer - data->vx) * tan(data->pa);
		if (data->mymap > (int)floor((data->vy) / SIZE) && (int)floor((data->vy) / SIZE) > 0)
		{
			while (data->mymap > (int)floor((data->vy) / SIZE) &&
				data->map[(int)floor((data->vy) / SIZE)][(int)floor((data->vx) / SIZE)] &&
				data->map[(int)floor(data->vy / SIZE)][(int)floor(data->vx / SIZE)] != '1')
			{
				// printf("\nVfsy:[%f] Vfsx:[%f] xa:[%f] ya:[%f]\n\n", floor(data->vy / SIZE), floor((data->vx / SIZE)), xa ,ya);
				data->vx += xa;
				data->vy += ya;
			}
		}
	}
}
