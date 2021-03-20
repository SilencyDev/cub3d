/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:20:56 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 12:07:43 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_release(int keycode, t_data *data)
{
	if (keycode == FORWARD)
		data->forward = 0;
	else if (keycode == LEFT)
		data->left = 0;
	else if (keycode == BACKWARD)
		data->backward = 0;
	else if (keycode == RIGHT)
		data->right = 0;
	else if (keycode == RLEFT)
		data->rleft = 0;
	else if (keycode == RRIGHT)
		data->rright = 0;
	return (1);
}

int		key_press(int keycode, t_data *data)
{
	if (keycode == FORWARD)
		data->forward = 1;
	else if (keycode == LEFT)
		data->left = 1;
	else if (keycode == BACKWARD)
		data->backward = 1;
	else if (keycode == RIGHT)
		data->right = 1;
	else if (keycode == RLEFT)
		data->rleft = 1;
	else if (keycode == RRIGHT)
		data->rright = 1;
	else if (keycode == SPACE)
		ft_exit(data, 0);
	return (1);
}

void	ft_rotate_l(t_data *data)
{
	data->pa += 0.1;
	angle_limit(&data->pa);
}

void	ft_rotate_r(t_data *data)
{
	data->pa -= 0.1;
	angle_limit(&data->pa);
}
