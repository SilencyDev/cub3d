/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:39:39 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/01 14:56:38 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_charset(char c, char *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (c);
	return (0);
}

void	ft_print_tab(t_data *data)
{
	int	y;
	int x;

	x = 0;
	y = 0;
	while (data->map[y][x])
	{
		while (data->map[y][x])
			printf("%c", data->map[y][x++]);
		printf("\n");
		x = 0;
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_init(t_data *data)
{
	data->left = 0;
	data->rleft = 0;
	data->right = 0;
	data->rright = 0;
	data->forward = 0;
	data->backward = 0;
	data->x_player = 0;
	data->x_pplayer = 0;
	data->y_player = 0;
	data->y_pplayer = 0;
	init_max_map(data);
}

void	ft_init_player(t_data *data)
{
	data->x_pplayer = data->x_player * SIZE + SIZE / 2;
	data->y_pplayer = data->y_player * SIZE + SIZE / 2;
	if (data->player == 'N')
		data->pa = N;
	if (data->player == 'W')
		data->pa = W;
	if (data->player == 'S')
		data->pa = S;
	if (data->player == 'E')
		data->pa = E;
}

void	ft_init_hv(t_data *data)
{
	data->hx = 0;
	data->hy = 0;
	data->vx = 0;
	data->vy = 0;
}

void		init_max_map(t_data *data)
{
	int	i;
	int	j;
	int	j_max;

	i = j = j_max = 0;
	while (data->map[i][j])
	{
		while (data->map[i][j])
		{
			j++;
		}
		j_max = j_max < j ? j : j_max;
		j = 0;
		i++;
	}
	data->mxmap = j_max - 1;
	data->mymap = i - 1;
}