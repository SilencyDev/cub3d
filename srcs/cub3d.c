/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/11 11:12:35 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_map(char *line, t_data *data, int y)
{
	int x;

	x = 0;
	while (*line)
		data->map[y][x++] = *line++;
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
		fd = open(argv[1], O_RDONLY);
		ft_init_hv(&data);
		ft_parsing(&data, fd);
		close(fd);
		ft_init(&data);
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
