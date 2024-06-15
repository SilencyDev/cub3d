/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:51:53 by kmacquet          #+#    #+#             */
/*   Updated: 2024/06/14 20:53:21 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_horizontal2(t_data *data, double ya, double xa)
{
	int currX = (int)floor(data->hx / SIZE);
	int currY = (int)floor(data->hy / SIZE);
	while (data->mxmap > currX
		&& currX > 0
		&& data->mymap > currY
		&& currY > 0
		&& data->map[currY]
		[currX]
		&& data->map[currY]
		[currX] != '1')
	{
		data->hx += xa;
		data->hy += ya;
		currX = (int)floor(data->hx / SIZE);
		currY = (int)floor(data->hy / SIZE);
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
	int currX = (int)floor(data->vx / SIZE);
	int currY = (int)floor(data->vy / SIZE);
	while (data->mymap > currY
		&& currY > 0
		&& data->mxmap > currX
		&& currX > 0
		&& data->map[currY]
		[currX]
		&& data->map[currY]
		[currX] != '1')
	{
		data->vx += xa;
		data->vy += ya;
		currX = (int)floor(data->vx / SIZE);
		currY = (int)floor(data->vy / SIZE);
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
