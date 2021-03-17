/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:42:28 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/17 13:10:28 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_imprim(t_data *data)
{
	int		x;
	int		width;
	double	iangle;

	x = 0;
	width = data->width;
	ft_move(data);
	iangle = data->pa;
	data->pa -= FOV2 * DTOR;
	while (width--)
	{
		check_horizontal(data);
		check_vertical(data);
		ft_render(ft_wall_size(data, iangle), x++, data);
		data->pa += (FOV * DTOR / data->width);
	}
	x = 0;
	data->pa = iangle;
	ft_minimap(data);
	if (data->save)
		ft_save(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (1);
}

void		ft_square(t_data *data, int x, int y, int color)
{
	int	x_max;
	int	y_max;
	int	i;
	int	j;

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
				my_mlx_pixel_put(data, x_max + j, y_max + i, 0x40000000);
			j++;
		}
		j = 0;
		i++;
	}
}

void		ft_player(t_data *data, int x, int y, int color)
{
	int	x_max;
	int	y_max;
	int	i;
	int	j;

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
				my_mlx_pixel_put(data, x_max + j, y_max + i, 0x00000000);
			j++;
		}
		j = 0;
		i++;
	}
}

void		ft_minimap(t_data *data)
{
	int	y;
	int	x;
	int	offset;

	y = 0;
	x = 0;
	offset = 1;
	while (data->mymap > y && data->map[y][x])
	{
		while (data->mxmap > x && data->map[y][x])
		{
			if (is_charset(data->map[y][x], "02SEWN"))
				ft_square(data, x + offset, y + offset, 0xF9FF0000);
			if (data->map[y][x] == '1')
				ft_square(data, x + offset, y + offset, 0x00FFFFFF);
			x++;
		}
		x = 0;
		y++;
	}
	ft_player(data, floor(data->x_pplayer / 64) + offset,
	floor(data->y_pplayer / 64) + offset, 0x00FFFF00);
}
