/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:51:53 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/19 17:16:34 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	mlx_get_screen_size(data->mlx_ptr, &data->screenx, &data->screeny);
**	(WIDTH > data->screenx) ? data->screenx :
**	(HEIGHT > data->screeny) ? data->screeny :
*/
#include "cub3d.h"

void		check_horizontal2(t_data *data, double ya, double xa)
{
	while (data->mxmap > (int)floor((data->hx) / SIZE)
		&& (int)floor((data->hx) / SIZE) > 0
		&& data->mymap > (int)floor((data->hy) / SIZE)
		&& (int)floor((data->hy) / SIZE) > 0
		&& data->map[(int)floor((data->hy) / SIZE)]
		[(int)floor((data->hx) / SIZE)]
		&& data->map[(int)floor(data->hy / SIZE)]
		[(int)floor(data->hx / SIZE)] != '1')
	{
		data->hx += xa;
		data->hy += ya;
	}
}

void		check_horizontal(t_data *data)
{
	double	ya;
	double	xa;

	ya = SIZE;
	xa = 0;
	if (!sin(data->pa))
		data->hx = DBL_MAX;
	else
	{
		if (sin(data->pa) > 0.0)
		{
			data->hy = floor(data->y_pplayer / SIZE) * SIZE - 0.000000001;
			xa = SIZE / tan(data->pa);
			ya *= -1;
		}
		else if (sin(data->pa) < 0.0)
		{
			data->hy = floor(data->y_pplayer / SIZE) * SIZE + SIZE;
			xa = -SIZE / tan(data->pa);
		}
		data->hx = data->x_pplayer
		+ (data->y_pplayer - data->hy) / tan(data->pa);
		check_horizontal2(data, ya, xa);
	}
}

void		check_vertical2(t_data *data, double ya, double xa)
{
	while (data->mymap > (int)floor((data->vy) / SIZE)
		&& (int)floor((data->vy) / SIZE) > 0
		&& data->mxmap > (int)floor((data->vx) / SIZE)
		&& (int)floor((data->vx) / SIZE) > 0
		&& data->map[(int)floor((data->vy) / SIZE)]
		[(int)floor((data->vx) / SIZE)]
		&& data->map[(int)floor(data->vy / SIZE)]
		[(int)floor(data->vx / SIZE)] != '1')
	{
		data->vx += xa;
		data->vy += ya;
	}
}

void		check_vertical(t_data *data)
{
	double	ya;
	double	xa;

	ya = 0;
	xa = SIZE;
	if (!cos(data->pa))
		data->vy = DBL_MAX;
	else
	{
		if (cos(data->pa) < 0.0)
		{
			data->vx = floor(data->x_pplayer / SIZE) * SIZE - 0.000000001;
			ya = SIZE * tan(data->pa);
			xa *= -1;
		}
		else if (cos(data->pa) > 0.0)
		{
			data->vx = floor(data->x_pplayer / SIZE) * SIZE + SIZE;
			ya = -SIZE * tan(data->pa);
		}
		data->vy = data->y_pplayer
		+ (data->x_pplayer - data->vx) * tan(data->pa);
		check_vertical2(data, ya, xa);
	}
}
