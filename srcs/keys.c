/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:20:56 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/06 17:47:42 by kmacquet         ###   ########.fr       */
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
		ft_exit(data);
	return (1);
}

int	ft_exit(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	if (data->texture[0].img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->texture[0].img_ptr);
	if (data->texture[1].img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->texture[1].img_ptr);
	if (data->texture[2].img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->texture[2].img_ptr);
	if (data->texture[3].img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->texture[3].img_ptr);
	if (data->texture[4].img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->texture[4].img_ptr);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}

void	ft_rotate_r(t_data *data)
{
	data->pa += 0.1;
	if (data->pa < 0)
		data->pa = 2 * PI + data->pa;
	data->rright = 0;
}

void	ft_rotate_l(t_data *data)
{
	data->pa -= 0.1;
	if (data->pa > 2 * PI)
		data->pa = data->pa - 2 * PI;
	data->rleft = 0;
}
