/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:42:05 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/19 22:09:51 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_save(t_data *data)
{
	int	fd;
	int	x;
	int	y;

	if ((fd = open("./save.bmp", O_CREAT | O_RDWR | O_TRUNC)) < 0)
		ft_error("Can't create save image", data);
	ft_header(data, fd);
	y = (int)data->height;
	while (y >= 0)
	{
		x = 0;
		while (x < (int)data->width)
		{
			write(fd, &data->addr[y * data->line_length + x * 4], 4);
			x++;
		}
		y--;
	}
	system("chmod 777 save.bmp");
	exit(0);
}

void	ft_header(t_data *data, int fd)
{
	int	tmp;
	int	i;
	int	width;
	int	height;

	i = 6;
	width = data->width;
	height = data->height;
	write(fd, "BM", 2);
	tmp = 14 + 40 + (4 * width * height);
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 4);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &width, 4);
	write(fd, &height, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &data->bits_per_pixel, 2);
	tmp = 0;
	while (i--)
		write(fd, &tmp, 4);
}
