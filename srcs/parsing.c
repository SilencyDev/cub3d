/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:53:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 00:04:19 by kmacquet         ###   ########.fr       */
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
	if (i > 2)
		ft_error("Resolution parameters incorrect", data);
	data->width = ft_atoi(str[0]);
	data->height = ft_atoi(str[1]);
	while (--i >= 0)
		ft_memdel((void **)&str[i]);
	free(str);
	str = NULL;
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
	if (i > 4)
		ft_error("Resolution parameters incorrect", data);
	data->color.rgb =
	(ft_atoi(str[1]) << 16 | ft_atoi(str[2]) << 8 | ft_atoi(str[3]));
	if (str[0][0] == 'F')
		data->f = data->color.rgb;
	else
		data->c = data->color.rgb;
	while (--i >= 0)
		ft_memdel((void **)&str[i]);
	free(str);
	str = NULL;
	if (data->f < 0 || data->c < 0)
		ft_error("Color parameters can't be negative", data);
	return (1);
}

int			recup_path(char *s, t_data *data)
{
	int		i;
	char	**str;

	i = 0;
	str = NULL;
	str = ft_split_str(s, " 	\t\v\r\f\n");
	while (str[i])
		i++;
	if (i != 2)
		ft_error("Path parameters incorrect", data);
	if (str[0][0] == 'S' && !str[0][1])
		data->texture[4].path = str[1];
	else if (str[0][0] == 'N' && str[0][1] == 'O')
		data->texture[0].path = str[1];
	else if (str[0][0] == 'S' && str[0][1] == 'O')
		data->texture[2].path = str[1];
	else if (str[0][0] == 'E' && str[0][1] == 'A')
		data->texture[1].path = str[1];
	else if (str[0][0] == 'W' && str[0][1] == 'E')
		data->texture[3].path = str[1];
	ft_memdel((void **)&str[0]);
	free(str);
	str = NULL;
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
		else if (*l == 'R' && is_charset(*(l + 1), " 	\t\v\r\f\n"))
			is_resolution_valid(l + 2, data);
		else if ((*l == 'F' && is_charset(*(l + 1), " 	\t\v\r\f\n"))
			|| (*l == 'C' && is_charset(*(l + 1), " 	\t\v\r\f\n")))
			is_ceil_floor_color(l, data);
		else if ((((*l == 'N' && *(l + 1) == 'O')
			|| (*l == 'S' && *(l + 1) == 'O')
			|| (*l == 'W' && *(l + 1) == 'E') || (*l == 'E' && *(l + 1) == 'A'))
			&& is_charset(*(l + 2), " 	\t\v\r\f\n"))
			|| (*l == 'S' && is_charset(*(l + 1), " 	\t\v\r\f\n")))
			recup_path(l, data);
		else
			data->mymap = count_max_map(l, data, data->mymap);
		ft_memdel((void **)&l);
	}
	close(fd);
}
