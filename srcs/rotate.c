/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:05:38 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/26 10:16:06 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotate_r(t_data *data)
{
	if (data->player == 'N')
		data->player = 'E';
	else if (data->player == 'E')
		data->player = 'S';
	else if (data->player == 'S')
		data->player = 'W';
	else if (data->player == 'W')
		data->player = 'N';
	data->rright = 0;
}

void	ft_rotate_l(t_data *data)
{
	if (data->player == 'N')
		data->player = 'W';
	else if (data->player == 'W')
		data->player = 'S';
	else if (data->player == 'S')
		data->player = 'E';
	else if (data->player == 'E')
		data->player = 'N';
	data->rleft = 0;
}
