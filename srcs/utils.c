/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:39:39 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/06 17:34:59 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_charset(char c, char *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (c);
	return (0);
}

void	ft_print_tab(t_data *data)
{
	int	y;
	int x;

	x = 0;
	y = 0;
	while (data->map[y][x])
	{
		while (data->map[y][x])
			printf("%c", data->map[y][x++]);
		printf("\n");
		x = 0;
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_image_pixel(t_data *data, int x, int y, int n)
{
	char	*dst;

	dst = data->texture[n].addr_ptr + (y * data->texture[n].line_length_t + x * (data->texture[n].bits_per_pixel_t / 8));
	return (*(unsigned int*)dst);
}
