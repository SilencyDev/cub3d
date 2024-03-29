/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 19:56:11 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		free_tab(char **s, int i)
{
	while (--i >= 0)
		ft_memdel((void **)&s[i]);
	free(s);
	s = NULL;
}

void		ft_strcpy2(char *path, char *str)
{
	while (*str)
		*path++ = *str++;
	*path = '\0';
}

int			count_max_map(char *line, t_data *data, int y)
{
	int	x;

	x = 0;
	data->map_set = 1;
	while (*line)
	{
		if (*line++ == '2')
			data->nb_sprite += 1;
		x++;
	}
	data->mxmap = data->mxmap < x ? x : data->mxmap;
	return (++y);
}

int			set_map(char *line, t_data *data, int y)
{
	int	x;

	x = 0;
	data->map[y] = NULL;
	if (!(data->map[y] = malloc((int)data->mxmap + 1)))
		ft_error("Malloc of row's map failed", data);
	while (*line)
		data->map[y][x++] = *line++;
	data->map[y][x] = '\0';
	return (++y);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	if (argc == 2 || (argc == 3 && is_save(argv[2], &data)))
	{
		if ((fd = open(argv[1], O_DIRECTORY)) != -1)
			ft_error("This is a directory, not a .cub file", &data);
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			ft_error(".cub invalid", &data);
		data.save = argc == 3 ? 1 : 0;
		ft_init(&data);
		fd = open(argv[1], O_RDONLY);
		ft_parsing_setting(&data, fd);
		fd = open(argv[1], O_RDONLY);
		ft_parsing_map(&data, fd);
		if (!is_map_valid(&data))
			ft_error("la map est invalide", &data);
		ft_init_player(&data);
		ft_mlx(&data);
	}
	return (0);
}
