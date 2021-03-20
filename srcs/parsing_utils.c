/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:37:24 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 18:53:03 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	path_order(t_data *data, char **str, int i)
{
	if ((data->parsing_order != 0 && str[0][0] == 'R' && !str[0][1])
		|| (data->parsing_order != 1 && str[0][0] == 'N'
		&& str[0][1] == 'O' && !str[0][2])
		|| (data->parsing_order != 2 && str[0][0] == 'S'
		&& str[0][1] == 'O' && !str[0][2])
		|| (data->parsing_order != 3 && str[0][0] == 'W'
		&& str[0][1] == 'E' && !str[0][2])
		|| (data->parsing_order != 4 && str[0][0] == 'E'
		&& str[0][1] == 'A' && !str[0][2])
		|| (data->parsing_order != 5 && str[0][0] == 'S' && !str[0][1])
		|| (data->parsing_order != 6 && str[0][0] == 'F')
		|| (data->parsing_order != 7 && str[0][0] == 'C'))
	{
		free_tab(str, i);
		ft_error("Order of parameters not respected", data);
	}
	if (data->map_set == 1)
	{
		free_tab(str, i);
		ft_error("Map should be set as the last parameter", data);
	}
	data->parsing_order++;
}

void	color_check(char **str, t_data *data, int i)
{
	if (!is_numspace(str[1]) || !is_numspace(str[2]) || !is_numspace(str[2]))
	{
		free_tab(str, i);
		ft_error("Color parameters can only be numeric", data);
	}
	if (ft_atoi(str[1]) < 0 || ft_atoi(str[2]) < 0 ||
		ft_atoi(str[3]) < 0 || ft_atoi(str[1]) > 255 ||
		ft_atoi(str[2]) > 255 || ft_atoi(str[3]) > 255)
	{
		free_tab(str, i);
		ft_error("Color parameters can't be negative or superior to 255", data);
	}
}
