/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:51:53 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/09 16:18:33 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_render(double p_wall, int x, t_data *data)
{
	int		height;
	double	offset;
	double	i;
	int 	n;

	i = 0;
	n = 0;
	offset = (p_wall - data->height)/2;
	height = data->height;
	while (height)
	{
		if ((height < data->height / 2 - (p_wall / 2) + p_wall) && (height > data->height / 2 - p_wall / 2))
		{
			if (data->dh >= data->dv)
			{
				n = cos(data->pa) > 0 ? 1 : 3;
				if (p_wall > data->height)
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dy % 64, (int)round((p_wall - offset - i))* 64 / p_wall, n));
				else
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dy % 64, (int)round((p_wall - i))* 64 / p_wall, n));
			}
			else
			{
				n = sin(data->pa) > 0 ? 0 : 2;
				if (p_wall > data->height)
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dx % 64, (int)round((p_wall - offset - i))* 64 / p_wall, n));
				else
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dx % 64 , (int)round((p_wall- i))* 64 / p_wall, n));
			}
			i++;
		}
		else if (!(height < (data->height / 2 - (p_wall / 2) + p_wall)))
			my_mlx_pixel_put(data, x, height, data->f);
		else
			my_mlx_pixel_put(data, x, height, data->c);
		height--;
	}
}

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
