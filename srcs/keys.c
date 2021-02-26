/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:20:56 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/26 10:23:35 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release(int keycode, t_data *data)
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

int	key_press(int keycode, t_data *data)
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
	{
		mlx_destroy_image(data->mlx_ptr, data->img);
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	return (1);
}
