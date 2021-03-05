/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/05 15:44:42 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_image_pixel(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->texture.addr_ptr + (y * data->texture.line_length_t + x * (data->texture.bits_per_pixel_t / 8));
	return (*(unsigned int*)dst);
}

void	ft_render(int height, double p_wall, int x, t_data *data)
{
	double	i;

	i = 0;
	while (height)
	{
		if ((height < (HEIGHT / 2 - (p_wall / 2) + p_wall)) && (height > (HEIGHT / 2 - p_wall / 2)))
		{
			if (data->dh >= data->dv)
				my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dy % 64, (int)round((p_wall - i))* 64 / p_wall));
			else
				my_mlx_pixel_put(data, x, height, get_image_pixel(data, (int)data->dx % 64 , (int)round((p_wall - i))* 64 / p_wall));
			i++;
		}
		else if (!(height < (HEIGHT / 2 - (p_wall / 2) + p_wall)))
			my_mlx_pixel_put(data, x, height, 0x00FF0000);
		else
			my_mlx_pixel_put(data, x, height, 0x00909090);
		height--;
	}
}

int	ft_imprim(t_data *data)
{
	// int	y;
	int	x;
	int		width;
	double	i;
	int		p_wall;
	int	height;

	// y = 0;
	x = 0;
	i = 0;
	width = WIDTH;
	height = HEIGHT;
	ft_move(data);
	// while (data->map[y][x])
	// {
	// 	while (data->map[y][x])
	// 	{
	// 		if (is_charset(data->map[y][x], "0SEWN"))
	// 			ft_square(data, x, y, 0x00FF0000);
	// 		if (data->map[y][x] == '1')
	// 			ft_square(data, x, y, 0xFFFFFFFF);
	// 		if (is_charset(data->map[y][x], "SWEN"))
	// 		{
	// 			ft_square(data, x, y, 0x000000FF);
	// 			if (data->player == 'N')
	// 				ft_direction_n(data, x, y, 0x00FFFF00);
	// 			else if (data->player == 'S')
	// 				ft_direction_s(data, x, y, 0x00FFFF00);
	// 			else if (data->player == 'E')
	// 				ft_direction_e(data, x, y, 0x00FFFF00);
	// 			else
	// 				ft_direction_w(data, x, y, 0x00FFFF00);
	// 		}
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	i = data->pa;
	data->pa -= (FOV/2)* DTOR;
	while (width--)
	{
		ft_init_hv(data);
		check_horizontal(data);
		check_vertical(data);
		data->dv = fabs((data->x_pplayer - data->vx)/cos(data->pa));
		data->dh = fabs((data->x_pplayer - data->hx)/cos(data->pa));
			data->dx = data->dv < data->dh ? data->vx : data->hx;
			data->dy = data->dv < data->dh ? data->vy : data->hy;
			data->d = data->dv < data->dh ? data->dv : data->dh;
		data->d = data->d * cos(i - data->pa);
		p_wall = ceil((SIZE / data->d) * DPROJ);
		ft_wtf(height, p_wall, x, data);

		height = HEIGHT;
		x++;
		data->pa += (FOV * DTOR/ WIDTH);
		data->pa = data->pa < 0 ? 2 * PI + data->pa : data->pa;
		data->pa = data->pa > 2 * PI ? data->pa - 2 * PI : data->pa;
	}
	x = 0;
	data->pa = i;
	// printf("x:[%f] y:[%f] vx:[%.2f] vy:[%.2f] hx:[%.2f] hy:[%.2f] dh:[%.2f] dv:[%.2f] a:[%f]\n", data->x_pplayer, data->y_pplayer, data->vx,data->vy ,data->hx ,data->hy ,data->dh,data->dv ,data->pa);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	int				fd;
	int				y;
	int				x;
	char			*line;
	t_data			data;
	char		*relative_path = "./textures/bricks.xpm";

	y = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			while (*line)
			{
				data.map[y][x] = *line++;
				printf("%c", data.map[y][x]);
				x++;
			}
			free(line - x);
			printf("%c",'\n');
			x = 0;
			y++;
		}
		data.map[y][x] = '\0';
		close(fd);
		ft_init(&data);
		if (!is_map_valid(&data))
		{
			printf("la map est invalide");
			return (-1);
		}
		ft_init_player(&data);
		data.mlx_ptr = mlx_init();
		data.mlx_win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Hello world!");
		data.texture.img_height = 64;
		data.texture.img_width = 64;
		data.texture.img_ptr = mlx_xpm_file_to_image(data.mlx_ptr, relative_path, &data.texture.img_width, &data.texture.img_height);
		data.texture.addr_ptr = mlx_get_data_addr(data.texture.img_ptr, &data.texture.bits_per_pixel_t, &data.texture.line_length_t, &data.texture.endian_t);
		data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
		mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &data);
		mlx_hook(data.mlx_win, 3, 1L<<1, key_release, &data);
		mlx_loop_hook(data.mlx_ptr, ft_imprim, &data);
		mlx_loop(data.mlx_ptr);
		mlx_destroy_image(data.mlx_ptr, data.texture.img_ptr);
	}
	return (0);
}
