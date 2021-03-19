/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:48:38 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/19 17:57:20 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		print_sprite2_bis(t_data *data, int height, int i, int x)
{
	int		j;
	double	p_sprite;
	int		n;

	n = data->n;
	p_sprite = data->p_sprite;
	j = p_sprite / 2;
	while (j)
	{
		if ((x + j - 1) < data->width && (x + j - 1) > 0 && (data->sprite[n].d
			< data->d[x + j - 1]) && get_image_pixel(data, (int)(round(
			(p_sprite / 2 - j)) * 64 / p_sprite) % 64, (int)round(p_sprite -
			i) * 64 / p_sprite, 4) != 0x980088)
			my_mlx_pixel_put(data, x + j - 1, height,
			get_image_pixel(data, (int)round((p_sprite / 2 - j)) * 64 /
			p_sprite, (int)round(p_sprite - i) * 64 / p_sprite, 4));
		j--;
	}
}

void		print_sprite2(t_data *data, int height, int i, int x)
{
	int		j;
	double	p_sprite;
	int		n;

	n = data->n;
	p_sprite = data->p_sprite;
	j = p_sprite / 2;
	while (j)
	{
		if ((x - j) > 0 && (x - j) < data->width && (data->sprite[n].d <
			data->d[x - j]) && get_image_pixel(data, (int)(round((
			p_sprite / 2 - j)) * 64 / p_sprite) % 64, (int)round(
			p_sprite - i) * 64 / p_sprite, 4) != 0x980088)
			my_mlx_pixel_put(data, x - j, height,
			get_image_pixel(data, (int)round((p_sprite / 2 - j)) * 64 /
			p_sprite, (int)round(p_sprite - i) * 64 / p_sprite, 4));
		j--;
	}
	print_sprite2_bis(data, height, i, x);
}

void		print_sprite1_bis(t_data *data, int height, int i, int x)
{
	int		j;
	double	p_sprite;
	int		n;

	n = data->n;
	p_sprite = data->p_sprite;
	j = p_sprite / 2;
	while (j)
	{
		if ((x + j - 1) < data->width && (x + j - 1) > 0 && (data->sprite[n].d
			< data->d[x + j - 1]) && get_image_pixel(data, (int)(round(
			(p_sprite / 2 + j - 1)) * 64 / p_sprite) % 64, (int)round(p_sprite
			- data->offset - i) * 64 / p_sprite, 4) != 0x980088)
			my_mlx_pixel_put(data, x + j - 1, height, get_image_pixel(data,
			(int)(round((p_sprite / 2 + j - 1)) * 64 / p_sprite) % 64,
			(int)round(p_sprite - data->offset - i) * 64 / p_sprite, 4));
		j--;
	}
}

void		print_sprite1(t_data *data, int height, int i, int x)
{
	int		j;
	double	p_sprite;
	int		n;

	n = data->n;
	p_sprite = data->p_sprite;
	j = p_sprite / 2;
	while (j)
	{
		if ((x - j) > 0 && (x - j) < data->width && (data->sprite[n].d <
			data->d[x - j]) && get_image_pixel(data, (int)(round(
			(p_sprite / 2 - j)) * 64 / p_sprite) % 64, (int)round(
			p_sprite - data->offset - i) * 64 / p_sprite, 4)
			!= 0x980088)
			my_mlx_pixel_put(data, x - j, height,
			get_image_pixel(data, (int)(round((p_sprite / 2 - j)) * 64 /
			p_sprite) % 64, (int)round(p_sprite - data->offset - i) * 64 /
			p_sprite, 4));
		j--;
	}
	print_sprite1_bis(data, height, i, x);
}

void		print_sprite(double p_sprite, int x, int n, t_data *data)
{
	int		height;
	double	i;
	int		j;

	i = 1;
	data->n = n;
	data->p_sprite = p_sprite;
	data->offset = (p_sprite - data->height) / 2;
	height = data->height;
	while (height)
	{
		j = p_sprite / 2;
		if ((height < data->height / 2 - (p_sprite / 2) + p_sprite)
			&& (height > data->height / 2 - p_sprite / 2))
		{
			if (p_sprite > data->height)
				print_sprite1(data, height, i, x);
			else
				print_sprite2(data, height, i, x);
			i++;
		}
		height--;
	}
}
