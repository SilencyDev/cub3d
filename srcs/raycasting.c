/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:51:53 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/18 17:52:58 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	mlx_get_screen_size(data->mlx_ptr, &data->screenx, &data->screeny);
**	(WIDTH > data->screenx) ? data->screenx :
**	(HEIGHT > data->screeny) ? data->screeny :
*/
#include "cub3d.h"

void		ft_render(double p_wall, int x, t_data *data)
{
	int		height;
	double	offset;
	double	i;
	int		n;

	i = 1;
	n = 0;
	offset = (p_wall - data->height) / 2;
	height = data->height - 1;
	while (height)
	{
		if ((height < data->height / 2 - (p_wall / 2) + p_wall)
			&& (height > data->height / 2 - p_wall / 2))
		{
			if (data->dh > data->dv)
			{
				n = cos(data->pa) > 0 ? 1 : 3;
				if (p_wall > data->height)
					my_mlx_pixel_put(data, x, height,
					get_image_pixel(data, (int)data->dy % 64,
					(int)round((p_wall - offset - i)) * 64 / p_wall, n));
				else
					my_mlx_pixel_put(data, x, height,
					get_image_pixel(data, (int)data->dy % 64,
					(int)round((p_wall - i)) * 64 / p_wall, n));
			}
			else
			{
				n = sin(data->pa) > 0 ? 0 : 2;
				if (p_wall > data->height)
					my_mlx_pixel_put(data, x, height,
					get_image_pixel(data, (int)data->dx % 64,
					(int)round((p_wall - offset - i)) * 64 / p_wall, n));
				else
					my_mlx_pixel_put(data, x, height,
					get_image_pixel(data, (int)data->dx % 64,
					(int)round((p_wall - i)) * 64 / p_wall, n));
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
			data->hy = floor(data->y_pplayer / SIZE) * SIZE - 0.000000001;
			xa = SIZE / tan(data->pa);
			ya *= -1;
		}
		else if (sin(data->pa) < 0)
		{
			data->hy = floor(data->y_pplayer / SIZE) * SIZE + SIZE;
			xa = -SIZE / tan(data->pa);
		}
		data->hx = data->x_pplayer
		+ (data->y_pplayer - data->hy) / tan(data->pa);
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
			data->vx = floor(data->x_pplayer / SIZE) * SIZE - 0.000000001;
			ya = SIZE * tan(data->pa);
			xa *= -1;
		}
		else if (cos(data->pa) > 0)
		{
			data->vx = floor(data->x_pplayer / SIZE) * SIZE + SIZE;
			ya = -SIZE * tan(data->pa);
		}
		data->vy = data->y_pplayer
		+ (data->x_pplayer - data->vx) * tan(data->pa);
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
}

void	ft_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx_win =
	mlx_new_window(data->mlx_ptr, data->width, data->height, "Cub3D!");
	ft_init_texture(data);
	data->img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img,
	&data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
	if (!(data->d = malloc(sizeof(double) * data->width)))
		ft_error("Wall's distance couldn't be malloc");
	mlx_loop_hook(data->mlx_ptr, ft_imprim, data);
	mlx_loop(data->mlx_ptr);
}

int		ft_wall_size(t_data *data, double iangle, int x)
{
	data->dv = fabs((data->x_pplayer - data->vx) / cos(data->pa));
	data->dh = fabs((data->x_pplayer - data->hx) / cos(data->pa));
	data->dx = data->dv < data->dh ? data->vx : data->hx;
	data->dy = data->dv < data->dh ? data->vy : data->hy;
	data->d[x] = data->dv < data->dh ? data->dv : data->dh;
	data->d[x] = data->d[x] * cos(iangle - data->pa);
	return (ceil((SIZE / data->d[x]) * (data->width / 2) / tan(FOV2 * DTOR)));
}
