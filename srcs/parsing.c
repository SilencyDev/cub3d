/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:53:26 by kmacquet          #+#    #+#             */
/*   Updated: 2024/06/14 21:48:51 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_resolution_valid(char *s, t_data *data)
{
	int		i;
	char	**str;

	i = 0;
	str = NULL;
	str = ft_split_str(s, " 	\t\v\r\f\n");
	while (str[i])
		i++;
	if (i != 2 || !(is_numspace(str[0]) && is_numspace(str[1]))
		|| data->width > 0 || data->height > 0)
	{
		free_tab(str, i);
		ft_error("Resolution parameters incorrect", data);
	}
	path_order(data, str, i);
	data->width = ft_atoi(str[0]);
	data->height = ft_atoi(str[1]);
	free_tab(str, i);
	if (data->width <= 0 || data->height <= 0)
		ft_error("Resolution parameters can't be negative or equal to 0", data);
	return (1);
}

int			is_ceil_floor_color(char *s, t_data *data)
{
	int		i;
	char	**str;

	i = 0;
	str = NULL;
	str = ft_split_str(s, " 	,\t\v\r\f\n");
	while (str[i])
		i++;
	if (i != 4)
	{
		free_tab(str, i);
		ft_error("Ceil || Floor parameters incorrect", data);
	}
	path_order(data, str, i);
	color_check(str, data, i);
	data->color.rgb =
	(ft_atoi(str[1]) << 16 | ft_atoi(str[2]) << 8 | ft_atoi(str[3]));
	if (str[0][0] == 'F')
		data->floorColor = data->color.rgb;
	else
		data->ceilingColor = data->color.rgb;
	free_tab(str, i);
	return (1);
}

void		fillTexturePath(t_data *data, char **str, char *path)
{
	if (str[0][0] == 'S' && !str[0][1])
		data->texture[4].path = path;
	else if (str[0][0] == 'N' && str[0][1] == 'O' && !str[0][2])
		data->texture[0].path = path;
	else if (str[0][0] == 'S' && str[0][1] == 'O' && !str[0][2])
		data->texture[2].path = path;
	else if (str[0][0] == 'E' && str[0][1] == 'A' && !str[0][2])
		data->texture[1].path = path;
	else if (str[0][0] == 'W' && str[0][1] == 'E' && !str[0][2])
		data->texture[3].path = path;
}

int			recup_path(char *s, t_data *data)
{
	int		i;
	char	**str;
	char	*path;

	i = 0;
	str = ft_split_str(s, " 	\t\v\r\f\n");
	while (str[i])
		i++;
	if (i != 2)
	{
		free_tab(str, i);
		ft_error("Path parameters incorrect", data);
	}
	path_order(data, str, i);
	if (!(path = malloc(ft_strlen(str[1]) + 1)))
	{
		free_tab(str, i);
		ft_error("Path couldn't be malloc", data);
	}
	ft_strcpy2(path, str[1]);
	fillTexturePath(data, str, path);
	free_tab(str, i);
	return (1);
}

void		ft_parsing_setting(t_data *data, int fd)
{
	int		ret;
	char	*l;

	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(fd, &l) > 0;
		if (is_empty_line(l, " 	\t\v\r\f\n"))
			;
		else if (*l == 'R')
			is_resolution_valid(l + 2, data);
		else if ((((*l == 'N' && *(l + 1) == 'O')
			|| (*l == 'S' && *(l + 1) == 'O')
			|| (*l == 'W' && *(l + 1) == 'E') || (*l == 'E' && *(l + 1) ==
			'A'))) || (*l == 'S' && *(l + 1) != 'O'))
			recup_path(l, data);
		else if ((*l == 'F')
			|| (*l == 'C'))
			is_ceil_floor_color(l, data);
		else
			data->mymap = count_max_map(l, data, data->mymap);
		ft_memdel((void **)&l);
	}
	close(fd);
}
