/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:44:38 by kmacquet          #+#    #+#             */
/*   Updated: 2024/06/15 10:17:46 by kmacquet         ###   ########.fr       */
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
	if (data->backward)
		ft_move_b(data, pdx, pdy);
	if (data->left)
		ft_move_l(data, pdy, pdx);
	if (data->right)
		ft_move_r(data, pdy, pdx);
	if (data->rright)
		ft_rotate_r(data);
	if (data->rleft)
		ft_rotate_l(data);
}

int		isInBound(double maxX, int newX, double maxY, int newY) {
	return maxX > newX
		&& newX > 0
		&& maxY > newY
		&& newY > 0;
}

int		isTravelable(t_data *data, int newX,int newY) {
	return data->map[newY]
			[newX] != '1'
			&& data->map[newY]
			[newX] != '2';
}

void adaptXY(t_data *data, int isXPositive, int isYPositive, double pdx, double pdy) {
	int nextX = 0;
	if (isXPositive > 0)
		nextX = (int)floor((data->x_pplayer + pdx) / SIZE);
	else
		nextX = (int)floor((data->x_pplayer - pdx) / SIZE);

	int nextY = 0;
	if (isYPositive > 0)
		nextY = (int)floor((data->y_pplayer + pdy) / SIZE);
	else
		nextY = (int)floor((data->y_pplayer - pdy) / SIZE);
		
	if (isInBound(data->mxmap, nextX, data->mymap, nextY) && isTravelable(data, nextX, nextY))
	{
		if (isXPositive > 0)
			data->x_pplayer += pdx;
		else
			data->x_pplayer -= pdx;
		
		if (isYPositive > 0)
			data->y_pplayer += pdy;
		else
			data->y_pplayer -= pdy;
	}
}

void		ft_move_f(t_data *data, double pdx, double pdy)
{
	adaptXY(data, 1, -1, pdx, pdy);
}

void		ft_move_b(t_data *data, double pdx, double pdy)
{
	adaptXY(data, -1, 1, pdx, pdy);
}

void		ft_move_r(t_data *data, double pdx, double pdy)
{
	adaptXY(data, 1, 1, pdx, pdy);
}

void		ft_move_l(t_data *data, double pdx, double pdy)
{
	adaptXY(data, -1, -1, pdx, pdy);
}
