/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:44:38 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/26 17:00:54 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_data *data)
{
	double pdx;
	double pdy;

	pdx = cos(data->pa) * SPEED;
	pdy = sin(data->pa) * SPEED;
	if (data->forward)
		ft_move_f(data, pdx, pdy);
	else if (data->backward)
		ft_move_b(data, pdx, pdy);
	else if (data->left)
		ft_move_l(data, pdx, pdy);
	else if (data->right)
		ft_move_r(data, pdx, pdy);
	else if (data->rright)
		ft_rotate_r(data);
	else if (data->rleft)
		ft_rotate_l(data);
}

void	ft_move_f(t_data *data, double pdx, double pdy)
{
	data->x_pplayer += pdx;
	data->y_pplayer -= pdy;
	data->forward = 0;
}

void	ft_move_b(t_data *data, double pdx, double pdy)
{
	data->x_pplayer -= pdx;
	data->y_pplayer += pdy;
	data->backward = 0;
}

// void	ft_move_f(t_data *data)
// {
// 	if (data->player == 'N')
// 		--data->y_pplayer;
// 	else if (data->player == 'S')
// 		++data->y_pplayer;
// 	else if (data->player == 'E')
// 		++data->x_pplayer;
// 	else if (data->player == 'W')
// 		--data->x_pplayer;
// 	data->forward = 0;
// }

// void	ft_move_b(t_data *data)
// {
// 	if (data->player == 'N')
// 		++data->y_pplayer;
// 	else if (data->player == 'S')
// 		--data->y_pplayer;
// 	else if (data->player == 'E')
// 		--data->x_pplayer;
// 	else if (data->player == 'W')
// 		++data->x_pplayer;
// 	data->backward = 0;
// }

void	ft_move_l(t_data *data, double pdx, double pdy)
{
	data->x_pplayer += pdy;
	data->y_pplayer += pdx;
	data->left = 0;
}

void	ft_move_r(t_data *data, double pdx, double pdy)
{
	data->x_pplayer -= pdy;
	data->y_pplayer -= pdx;
	data->right = 0;
}

// void	ft_move_f(t_data *data)
// {
// 	if (data->player == 'N' &&
// 		(data->map[data->y_player - 1][data->x_player] == '0'))
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[--data->y_player][data->x_player] = 'N';
// 	}
// 	else if (data->player == 'S' &&
// 		(data->map[data->y_player + 1][data->x_player] == '0'))
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[++data->y_player][data->x_player] = 'S';
// 	}
// 	else if (data->player == 'E' &&
// 		(data->map[data->y_player][data->x_player + 1] == '0'))
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[data->y_player][++data->x_player] = 'E';
// 	}
// 	else if (data->player == 'W' &&
// 		(data->map[data->y_player][data->x_player - 1] == '0'))
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[data->y_player][--data->x_player] = 'W';
// 	}
// 	data->forward = 0;
// }

// void	ft_move_b(t_data *data)
// {
// 	if (data->player == 'N' &&
// 		(data->map[data->y_player + 1][data->x_player] == '0'))
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[++data->y_player][data->x_player] = 'N';
// 	}
// 	else if (data->player == 'S' &&
// 		(data->map[data->y_player - 1][data->x_player] == '0'))
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[--data->y_player][data->x_player] = 'S';
// 	}
// 	else if (data->player == 'E' &&
// 		(data->map[data->y_player][data->x_player - 1] == '0'))
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[data->y_player][--data->x_player] = 'E';
// 	}
// 	else if (data->player == 'W' &&
// 		(data->map[data->y_player][data->x_player + 1] == '0'))
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[data->y_player][++data->x_player] = 'W';
// 	}
// 	data->backward = 0;
// }

// void	ft_move_l(t_data *data)
// {
// 	if (data->player == 'N' &&
// 		data->map[data->y_player][data->x_player - 1] == '0')
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[data->y_player][--data->x_player] = 'N';
// 	}
// 	else if (data->player == 'S' &&
// 		data->map[data->y_player][data->x_player + 1] == '0')
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[data->y_player][++data->x_player] = 'S';
// 	}
// 	else if (data->player == 'E' &&
// 		data->map[data->y_player - 1][data->x_player] == '0')
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[--data->y_player][data->x_player] = 'E';
// 	}
// 	else if (data->player == 'W' &&
// 		data->map[data->y_player + 1][data->x_player] == '0')
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[++data->y_player][data->x_player] = 'W';
// 	}
// 	data->left = 0;
// }

// void	ft_move_r(t_data *data)
// {
// 	if (data->player == 'N' &&
// 		data->map[data->y_player][data->x_player + 1] == '0')
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[data->y_player][++data->x_player] = 'N';
// 	}
// 	else if (data->player == 'S' &&
// 		data->map[data->y_player][data->x_player - 1] == '0')
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[data->y_player][--data->x_player] = 'S';
// 	}
// 	else if (data->player == 'E' &&
// 		data->map[data->y_player + 1][data->x_player] == '0')
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[++data->y_player][data->x_player] = 'E';
// 	}
// 	else if (data->player == 'W' &&
// 		data->map[data->y_player - 1][data->x_player] == '0')
// 	{
// 		data->map[data->y_player][data->x_player] = '0';
// 		data->map[--data->y_player][data->x_player] = 'W';
// 	}
// 	data->right = 0;
// }
