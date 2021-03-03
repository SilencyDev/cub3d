/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:05:38 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/01 15:20:15 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	ft_rotate_r(t_data *data)
// {
// 	data->pa += 0.1;
// 	if (data->pa > 2*PI)
// 		data->pa-=2*PI;
// 	data->pdx=cos(data->pa)*5;
// 	data->pdy=sin(data->pa)*5;
// 	data->rright = 0;
// }

// void	ft_rotate_l(t_data *data)
// {
// 	data->pa -= 0.1;
// 	if (data->pa < 0)
// 		data->pa+=2*PI;
// 	data->pdx=cos(data->pa)*5;
// 	data->pdy=sin(data->pa)*5;
// 	data->rleft = 0;
// }

void	ft_rotate_r(t_data *data)
{
	data->pa -= 0.1;
	if (data->pa < 0)
		data->pa = 2*PI + data->pa;
	data->rright = 0;
}

void	ft_rotate_l(t_data *data)
{
	data->pa += 0.1;
	if (data->pa > 2*PI)
		data->pa = data->pa - 2*PI;
	data->rleft = 0;
}
