/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:30:14 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/17 13:54:27 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	data->player = 0;
	data->mymap = 0;
	data->mxmap = 0;
	data->hx = 0;
	data->hy = 0;
	data->vx = 0;
	data->vy = 0;
	data->one = 0;
	data->nb_player = 0;
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

void	ft_init_texture(t_data *data)
{
	int		n;

	n = 0;
	while (n < 5)
	{
		data->texture[n].img_height = 64;
		data->texture[n].img_width = 64;
		if (!(data->texture[n].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			data->texture[n].path, &data->texture[n].img_width,
			&data->texture[n].img_height)))
			ft_error("Texture's path incorrect");
		data->texture[n].addr_ptr = mlx_get_data_addr(data->texture[n].img_ptr,
		&data->texture[n].bits_per_pixel_t, &data->texture[n].line_length_t,
		&data->texture[n].endian_t);
		n++;
	}
}
