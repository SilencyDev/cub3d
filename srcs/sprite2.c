/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:48:38 by kmacquet          #+#    #+#             */
/*   Updated: 2024/06/14 21:48:24 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		print_sprite2_bis(t_data *data, int height, int i, int x)
{
	int		j;
	double	p_sprite;
	int		n;

	n = data->textureIndex;
	p_sprite = data->p_sprite;
	j = p_sprite / 2;
	unsigned int pixel = 0;
	while (j)
	{
		pixel = get_image_pixel(data, (int)(round(
			(p_sprite / 2 - j)) * (int)SIZE / p_sprite) % (int)SIZE, (int)round(p_sprite -
			i) * (int)SIZE / p_sprite, 4);
		if ((x + j - 1) < data->width && (x + j - 1) > 0 && (data->sprite[n].d
			< data->d[x + j - 1]) && pixel != 0x980088)
			my_mlx_pixel_put(data, x + j - 1, height, pixel);
		j--;
	}
}

void		print_sprite2(t_data *data, int height, int i, int x)
{
	int		j;
	double	p_sprite;
	int		n;

	n = data->textureIndex;
	p_sprite = data->p_sprite;
	j = p_sprite / 2;
	unsigned int pixel = 0;
	while (j)
	{
		pixel = get_image_pixel(data, (int)(round((
			p_sprite / 2 - j)) * (int)SIZE / p_sprite) % (int)SIZE, (int)round(
			p_sprite - i) * (int)SIZE / p_sprite, 4);
		if ((x - j) > 0 && (x - j) < data->width && (data->sprite[n].d <
			data->d[x - j]) && pixel != 0x980088)
			my_mlx_pixel_put(data, x - j, height, pixel);
		j--;
	}
	print_sprite2_bis(data, height, i, x);
}

void		print_sprite1_bis(t_data *data, int height, int i, int x)
{
	int		j;
	double	p_sprite;
	int		n;

	n = data->textureIndex;
	p_sprite = data->p_sprite;
	j = p_sprite / 2;
	unsigned int pixel = 0;
	while (j)
	{
		pixel = get_image_pixel(data, (int)(round(
			(p_sprite / 2 + j - 1)) * (int)SIZE / p_sprite) % (int)SIZE, (int)round(p_sprite
			- data->offset - i) * (int)SIZE / p_sprite, 4);
		if ((x + j - 1) < data->width && (x + j - 1) > 0 && (data->sprite[n].d
			< data->d[x + j - 1]) && pixel != 0x980088)
			my_mlx_pixel_put(data, x + j - 1, height, pixel);
		j--;
	}
}

void		print_sprite1(t_data *data, int height, int i, int x)
{
	int		j;
	double	p_sprite;
	int		n;

	n = data->textureIndex;
	p_sprite = data->p_sprite;
	j = p_sprite / 2;
	unsigned int pixel = 0;
	while (j)
	{
		pixel = get_image_pixel(data, (int)(round(
			(p_sprite / 2 - j)) * (int)SIZE / p_sprite) % (int)SIZE, (int)round(
			p_sprite - data->offset - i) * (int)SIZE / p_sprite, 4);
		if ((x - j) > 0 && (x - j) < data->width && (data->sprite[n].d <
			data->d[x - j]) && pixel
			!= 0x980088)
			my_mlx_pixel_put(data, x - j, height, pixel);
		j--;
	}
	print_sprite1_bis(data, height, i, x);
}

void		print_sprite(double p_sprite, int x, int n, t_data *data)
{
	int		height;
	double	i;

	i = 1;
	data->textureIndex = n;
	data->p_sprite = p_sprite;
	data->offset = (p_sprite - data->height) / 2;
	height = data->height;
	while (height)
	{
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
