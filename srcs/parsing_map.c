/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:47:43 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 18:27:52 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_map_valid(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (!(data->sprite = malloc(sizeof(t_sprite) * data->nb_sprite)))
		ft_error("Sprite couldn't be malloc", data);
	while (y < data->mymap && data->map[y][x])
	{
		if (!is_valid_to_right(data, y, x))
			return (0);
		y++;
		x = 0;
	}
	y = 0;
	while (x < data->mxmap && data->map[y][x])
	{
		if (!is_valid_to_bottom(data, y, x))
			return (0);
		x++;
		y = 0;
	}
	if (!is_charset(data->player, "NSEW"))
		return (0);
	return (1);
}

void		ft_parsing_map(t_data *data, int fd)
{
	int		ret;
	int		y;
	char	*l;

	ret = 1;
	y = 0;
	if (!(data->map = malloc(sizeof(char*) * (int)data->mymap)))
		ft_error("Malloc of map failed", data);
	while (ret != 0)
	{
		ret = get_next_line(fd, &l) > 0;
		if (is_empty_line(l, " 	\t\v\r\f\n")
			|| (*l == 'R' && is_charset(*(l + 1), " 	\t\v\r\f\n"))
			|| (*l == 'F' && is_charset(*(l + 1), " 	\t\v\r\f\n"))
			|| (*l == 'C' && is_charset(*(l + 1), " 	\t\v\r\f\n"))
			|| ((*l == 'N' && *(l + 1) == 'O') || (*l == 'S' && *(l + 1) == 'O')
			|| (*l == 'W' && *(l + 1) == 'E') || ((*l == 'E' && *(l + 1) ==
			'A'))) || (*l == 'S' && *(l + 1) != 'O'))
			;
		else
			y = set_map(l, data, y);
		ft_memdel((void **)&l);
	}
	close(fd);
}
