/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/17 14:54:16 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_max_map(char *line, t_data *data, int y)
{
	int	x;

	x = 0;
	while (*line++)
		x++;
	data->mxmap = data->mxmap < x ? x : data->mxmap;
	return (++y);
}

int	set_map(char *line, t_data *data, int y)
{
	int x;

	x = 0;
	if (!(data->map[y] = malloc((int)data->mxmap + 1)))
		ft_error("Malloc of row's map failed");
	while (*line)
		data->map[y][x++] = *line++;
	data->map[y][x] = '\0';
	free(line - x);
	return (++y);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_data			data;

	if (argc == 2 || (argc == 3 && is_save(argv[2])))
	{
		data.save = argc == 3 ? 1 : 0;
		ft_init(&data);
		fd = open(argv[1], O_RDONLY);
		ft_parsing_setting(&data, fd);
		fd = open(argv[1], O_RDONLY);
		ft_parsing_map(&data, fd);
		if (!is_map_valid(&data))
		{
			ft_putstr_fd("la map est invalide", 1);
			return (-1);
		}
		ft_init_player(&data);
		ft_mlx(&data);
	}
	return (0);
}
