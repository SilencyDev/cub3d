/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:51:53 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/11 14:54:39 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_render(double p_wall, int x, t_data *data, double p_sprite)
{
	int		height;
	double	offset;
	double	offset_s;
	double	i;
	double	j;
	int 	n;

	i = j = 1;
	n = 0;
	offset = (p_wall - data->height)/2;
	offset_s = (p_sprite - data->height)/2;
	height = data->height;
	while (height)
	{
		if ((height < data->height / 2 - (p_wall / 2) + p_wall) && (height > data->height / 2 - p_wall / 2))
		{
			if (data->dh > data->dv)
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
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dx % 64 , (int)round((p_wall - i))* 64 / p_wall, n));
			}
			i++;
		}
		else if (!(height < (data->height / 2 - (p_wall / 2) + p_wall)))
			my_mlx_pixel_put(data, x, height, data->f);
		else
			my_mlx_pixel_put(data, x, height, data->c);
		if ((height < data->height / 2 - (p_sprite / 2) + p_sprite) && (height > data->height / 2 - p_sprite / 2) &&
			(data->sprite.d < data->d) && (data->sprite.hx > 0 || data->sprite.vx > 0) && (data->sprite.hy > 0 || data->sprite.vy > 0))
		{
			if (data->sprite.dh > data->sprite.dv)
			{
				if (p_sprite > data->height && (get_image_pixel(data, (int)data->sprite.dy % 64, (int)round((p_sprite - offset_s - j))* 64 / p_sprite, 4) != 0x00980088))
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->sprite.dy % 64, (int)round((p_sprite - offset_s - j))* 64 / p_sprite, 4));
				else if (get_image_pixel(data, (int)data->sprite.dy % 64, (int)round((p_sprite - j))* 64 / p_sprite, 4) != 0x00980088)
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->sprite.dy % 64, (int)round((p_sprite - j))* 64 / p_sprite, 4));
			}
			else
			{
				if (p_sprite > data->height  && (get_image_pixel(data, (int)data->sprite.dx % 64, (int)round((p_sprite - offset_s - j))* 64 / p_sprite, 4) != 0x00980088))
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->sprite.dx % 64, (int)round((p_sprite - offset_s - j))* 64 / p_sprite, 4));
				else if (get_image_pixel(data, (int)data->sprite.dx % 64, (int)round((p_sprite - j))* 64 / p_sprite, 4) != 0x00980088)
					my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->sprite.dx % 64, (int)round((p_sprite - j))* 64 / p_sprite, 4));
			}
			j++;
		}
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
				if (data->map[(int)floor(data->hy / SIZE)][(int)floor(data->hx / SIZE)] == '2')
				{
					data->sprite.hx = data->hx;
					data->sprite.hy = data->hy;
				}
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
				if (data->map[(int)floor(data->vy / SIZE)][(int)floor(data->vx / SIZE)] == '2')
				{
					data->sprite.vx = data->vx;
					data->sprite.vy = data->vy;
				}
				// printf("\nVfsy:[%f] Vfsx:[%f] xa:[%f] ya:[%f]\n\n", floor(data->vy / SIZE), floor((data->vx / SIZE)), xa ,ya);
				data->vx += xa;
				data->vy += ya;
			}
		}
	}
}

void	ft_mlx(t_data *data)
{
		data->mlx_ptr = mlx_init();
		// mlx_get_screen_size(data.mlx_ptr, &data.screenx, &data.screeny);
		data->width = /*(WIDTH > data.screenx) ? data.screenx :*/ WIDTH;
		data->height = /*(HEIGHT > data.screeny) ? data.screeny :*/ HEIGHT;
		data->mlx_win = mlx_new_window(data->mlx_ptr, data->width, data->height, "Cub3D!");
		ft_init_texture(data);
		data->img = mlx_new_image(data->mlx_ptr, data->width, data->height);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
		mlx_hook(data->mlx_win, 2, 1L<<0, key_press, data);
		mlx_hook(data->mlx_win, 3, 1L<<1, key_release, data);
		// mlx_hook(data->mlx_win, 33, 1L << 17, ft_exit, data);
		mlx_loop_hook(data->mlx_ptr, ft_imprim, data);
		mlx_loop(data->mlx_ptr);
}

int		ft_wall_size(t_data *data, double iangle)
{
		data->dv = fabs((data->x_pplayer - data->vx)/cos(data->pa));
		data->dh = fabs((data->x_pplayer - data->hx)/cos(data->pa));
		data->dx = data->dv < data->dh ? data->vx : data->hx;
		data->dy = data->dv < data->dh ? data->vy : data->hy;
		data->d = data->dv < data->dh ? data->dv : data->dh;
		data->d = data->d * cos(iangle - data->pa);
		return (ceil((SIZE / data->d) * (data->width / 2) / tan(FOV2 * DTOR)));
}

int		ft_sprite_size(t_data *data, double iangle)
{
		data->sprite.dv = fabs((data->x_pplayer - data->sprite.vx)/cos(data->pa));
		data->sprite.dh = fabs((data->x_pplayer - data->sprite.hx)/cos(data->pa));
		data->sprite.dx = data->sprite.dv < data->sprite.dh ? data->sprite.vx : data->sprite.hx;
		data->sprite.dy = data->sprite.dv < data->sprite.dh ? data->sprite.vy : data->sprite.hy;
		data->sprite.d = data->sprite.dv < data->sprite.dh ? data->sprite.dv : data->sprite.dh;
		data->sprite.d = data->sprite.d * cos(iangle - data->pa);
		return (ceil((SIZE / data->sprite.d) * (data->width / 2) / tan(FOV2 * DTOR)));
}
