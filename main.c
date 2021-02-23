/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/23 17:49:41 by kmacquet         ###   ########.fr       */
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

int	is_map_valid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->one = 0;
	map->nb_player = 0;
	while (map->map[i][j])
	{
		while (map->map[i][j] == ' ')
			j++;
		while (map->map[i][j])
		{
			if (!is_charset(map->map[i][j], "012 NSEW"))
				return (0);
			if (map->map[i][j] == '1')
				map->one = 1;
			if (map->map[i][j] == ' ')
				map->one = 0;
			if (map->one == 0 && !is_charset(map->map[i][j], "1 "))
				return (0);
			if (is_charset(map->map[i][j], "NSEW"))
			{
				map->nb_player += 1;
				if (map->nb_player > 1)
					return (0);
				map->player = is_charset(map->map[i][j], "NSEW");
				map->i_player = i;
				map->j_player = j;
				map->map[i][j] = '0';
			}
			if (map->map[i][j++] == '0' && i == 0)
				return (0);
		}
		map->one = 0;
		while (map->map[i][--j])
		{
			if (map->map[i][j] == '1')
				map->one = 1;
			if (map->one == 0 && map->map[i][j] == '0')
				return (0);
		}
		map->one = 0;
		i++;
		j = 0;
	}
	if (!is_charset(map->player, "NSEW"))
		return (0);
	while (map->map[i - 2][j])
	{
		if (map->map[i - 2][j] == '0')
			if (map->map[i - 1][j] != '1')
				return (0);
		j++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int				fd;
	int				i;
	int				j;
	char			*line;
	t_map	map;

	i = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			while (*line)
			{
				map.map[i][j++] = *line++;
				printf("%c", map.map[i][j - 1]);
			}
			printf("%c",'\n');
			j = 0;
			i++;
		}
		map.map[i][j] = '\0';
		close(fd);
		if (!is_map_valid(&map))
		{
			printf("la map est invalide");
			return (-1);
		}
		printf("%c", map.map[4][3]);
	}
	return (0);
}
