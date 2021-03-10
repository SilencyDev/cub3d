/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:42:28 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/10 16:12:23 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_imprim(t_data *data)
{
	int		x;
	int		width;
	double	iangle;
	int		p_wall;

	x = 0;
	width = data->width;
	ft_move(data);
	iangle = data->pa;
	data->pa -= FOV2 * DTOR;
	while (width--)
	{
		ft_init_hv(data);
		check_horizontal(data);
		check_vertical(data);
		p_wall = ft_wall_size(data, iangle);
		ft_render(p_wall, x++, data);
		data->pa += (FOV * DTOR/ data->width);
	}
	x = 0;
	data->pa = iangle;
	ft_minimap(data);
	// printf("x:[%f] y:[%f] vx:[%.2f] vy:[%.2f] hx:[%.2f] hy:[%.2f] dh:[%.2f] dv:[%.2f] a:[%f]\n", data->x_pplayer, data->y_pplayer, data->vx,data->vy ,data->hx ,data->hy ,data->dh,data->dv ,data->pa);
	if (data->save)
		ft_save(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (1);
}

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
			if (i < 1 || i > 7 || j < 1 || j > 7)
				my_mlx_pixel_put(data, x_max + j, y_max + i, 0xFF000000);
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
			if (i < 1 || i > 7 || j < 1 || j > 7)
				my_mlx_pixel_put(data, x_max + j, y_max + i, 0x10000000);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_minimap(t_data *data)
{
	int	y;
	int	x;
	int	offset;

	y = 0;
	x = 0;
	offset = 1;
	while (data->map[y][x])
	{
		while (data->map[y][x])
		{
			if (is_charset(data->map[y][x], "02SEWN"))
				ft_square(data, x + offset, y + offset, 0xF0FF0000);
			if (data->map[y][x] == '1')
				ft_square(data, x + offset, y + offset, 0x00FFFFFF);
			x++;
		}
		x = 0;
		y++;
	}
	ft_player(data, floor(data->x_pplayer/64) + offset, floor(data->y_pplayer/64) + offset, 0x40FFFF00);
}
