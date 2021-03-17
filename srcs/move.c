/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:44:38 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/17 15:13:02 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_move(t_data *data)
{
	double	pdx;
	double	pdy;

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

void		ft_move_f(t_data *data, double pdx, double pdy)
{
	if (data->mxmap > (int)floor((data->x_pplayer + pdx) / SIZE)
		&& (int)floor((data->x_pplayer + pdx) / SIZE) > 0
		&& data->mymap > (int)floor((data->y_pplayer - pdy) / SIZE)
		&& (int)floor((data->y_pplayer - pdy) / SIZE) > 0)
	{
		if (data->mymap > (int)floor((data->y_pplayer - pdy) / SIZE)
			&& data->map[(int)floor((data->y_pplayer - pdy) / SIZE)]
			[(int)floor((data->x_pplayer + pdx) / SIZE)]
			&& data->map[(int)floor((data->y_pplayer - pdy) / SIZE)]
			[(int)floor((data->x_pplayer + pdx) / SIZE)] != '1')
		{
			data->x_pplayer += pdx;
			data->y_pplayer -= pdy;
		}
	}
	data->forward = 0;
}

void		ft_move_b(t_data *data, double pdx, double pdy)
{
	if (data->mxmap > (int)floor((data->x_pplayer - pdx) / SIZE)
		&& (int)floor((data->x_pplayer - pdx) / SIZE) > 0
		&& data->mymap > (int)floor((data->y_pplayer + pdy) / SIZE)
		&& (int)floor((data->y_pplayer + pdy) / SIZE) > 0)
	{
		if (data->mymap > (int)floor((data->y_pplayer + pdy) / SIZE) &&
			data->map[(int)floor((data->y_pplayer + pdy) / SIZE)]
			[(int)floor((data->x_pplayer - pdx) / SIZE)] &&
			data->map[(int)floor((data->y_pplayer + pdy) / SIZE)]
			[(int)floor((data->x_pplayer - pdx) / SIZE)] != '1')
		{
			data->x_pplayer -= pdx;
			data->y_pplayer += pdy;
		}
	}
	data->backward = 0;
}

void		ft_move_l(t_data *data, double pdx, double pdy)
{
	if (data->mxmap > (int)floor((data->x_pplayer + pdy) / SIZE)
		&& (int)floor((data->x_pplayer + pdy) / SIZE) > 0
		&& data->mymap > (int)floor((data->y_pplayer + pdx) / SIZE)
		&& (int)floor((data->y_pplayer + pdx) / SIZE) > 0)
	{
		if (data->mymap > (int)floor((data->y_pplayer + pdx) / SIZE) &&
			data->map[(int)floor((data->y_pplayer + pdx) / SIZE)]
			[(int)floor((data->x_pplayer + pdy) / SIZE)] &&
			data->map[(int)floor((data->y_pplayer + pdx) / SIZE)]
			[(int)floor((data->x_pplayer + pdy) / SIZE)] != '1')
		{
			data->x_pplayer += pdy;
			data->y_pplayer += pdx;
		}
	}
	data->left = 0;
}

void		ft_move_r(t_data *data, double pdx, double pdy)
{
	if (data->mxmap > (int)floor((data->x_pplayer - pdy) / SIZE)
		&& (int)floor((data->x_pplayer - pdy) / SIZE) > 0
		&& data->mymap > (int)floor((data->y_pplayer - pdx) / SIZE)
		&& (int)floor((data->y_pplayer - pdx) / SIZE) > 0)
	{
		if (data->mymap > (int)floor((data->y_pplayer - pdx) / SIZE)
			&& data->map[(int)floor((data->y_pplayer - pdx) / SIZE)]
			[(int)floor((data->x_pplayer - pdy) / SIZE)]
			&& data->map[(int)floor((data->y_pplayer - pdx) / SIZE)]
			[(int)floor((data->x_pplayer - pdy) / SIZE)] != '1')
		{
			data->x_pplayer -= pdy;
			data->y_pplayer -= pdx;
		}
	}
	data->right = 0;
}
