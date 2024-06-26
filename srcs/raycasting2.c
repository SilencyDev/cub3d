/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:15:17 by kmacquet          #+#    #+#             */
/*   Updated: 2024/06/14 21:48:51 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_render2(t_data *data, int x, int h, int i)
{
	int	n;

	data->offset = (data->p_wall - data->height) / 2;
	if (data->dh > data->dv)
	{
		n = cos(data->pa) > 0 ? 1 : 3;
		if (data->p_wall > data->height)
			my_mlx_pixel_put(data, x, h, get_image_pixel(data,
			(int)data->dy % (int)SIZE, (int)round((data->p_wall - data->offset - i))
			* SIZE / data->p_wall, n));
		else
			my_mlx_pixel_put(data, x, h, get_image_pixel(data, (int)data->dy
			% (int)SIZE, (int)round((data->p_wall - i)) * (int)SIZE / data->p_wall, n));
	}
	else
	{
		n = sin(data->pa) > 0 ? 0 : 2;
		if (data->p_wall > data->height)
			my_mlx_pixel_put(data, x, h, get_image_pixel(data,
			(int)data->dx % (int)SIZE, (int)round((data->p_wall - data->offset - i))
			* SIZE / data->p_wall, n));
		else
			my_mlx_pixel_put(data, x, h, get_image_pixel(data, (int)data->dx
			% (int)SIZE, (int)round((data->p_wall - i)) * (int)SIZE / data->p_wall, n));
	}
}

void		ft_render(double p_wall, int x, t_data *data)
{
	int		height;
	double	i;

	i = 1;
	data->p_wall = p_wall;
	height = data->height;
	while (height)
	{
		if ((height < data->height / 2 - (p_wall / 2) + p_wall)
			&& (height > data->height / 2 - p_wall / 2))
			ft_render2(data, x, height, i++);
		else if (!(height < (data->height / 2 - (p_wall / 2) + p_wall)))
			my_mlx_pixel_put(data, x, height, data->floorColor);
		else
			my_mlx_pixel_put(data, x, height, data->ceilingColor);
		height--;
	}
}

void		ft_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	mlx_get_screen_size(data->mlx_ptr, &data->screenx, &data->screeny);
	data->width = (data->width > data->screenx || data->width < 320)
	? data->screenx : data->width;
	data->height = (data->height > data->screeny || data->height < 200)
	? data->screeny : data->height;
	data->mlx_win =
	mlx_new_window(data->mlx_ptr, data->width, data->height, "Cub3D!");
	ft_init_texture(data);
	data->img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img,
	&data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx_win, 33, 1L << 17, ft_exit, data);
	if (!(data->d = malloc(sizeof(double) * data->width)))
		ft_error("Wall's distance couldn't be malloc", data);
	mlx_loop_hook(data->mlx_ptr, ft_imprim, data);
	mlx_loop(data->mlx_ptr);
}

int			ft_wall_size(t_data *data, double iangle, int x)
{
	int	i;

	data->dv = fabs((data->x_pplayer - data->vx) / cos(data->pa));
	data->dh = fabs((data->x_pplayer - data->hx) / cos(data->pa));
	data->dx = data->dv < data->dh ? data->vx : data->hx;
	data->dy = data->dv < data->dh ? data->vy : data->hy;
	data->d[x] = data->dv < data->dh ? data->dv : data->dh;
	i = data->d[x] * cos(iangle - data->pa);
	return (ceil((SIZE / i) * (data->width / 2)
		/ tan(FOV / 2 * DTOR)));
}
