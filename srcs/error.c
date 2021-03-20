/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:32:37 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 16:27:10 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *s, t_data *data)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
	ft_exit(data, 1);
}

int		is_save(char *s, t_data *data)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i == 6 && s[i - 1] == 'e' && s[i - 2] == 'v'
		&& s[i - 3] == 'a' && s[i - 4] == 's'
		&& s[i - 5] == '-' && s[i - 6] == '-')
		return (1);
	ft_error("The 2nd argument isn't --save", data);
	return (0);
}

int		is_numspace(char *str)
{
	while (*str)
	{
		if (!((*str >= '0' && *str <= '9') || *str == ' '))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit2(t_data *data, int i)
{
	int	y;

	y = 0;
	if (data->map)
	{
		while (y < data->mymap)
		{
			free(data->map[y]);
			data->map[y++] = NULL;
		}
		free(data->map);
		data->map = NULL;
		y = 0;
	}
	if (data->sprite)
		free(data->sprite);
	y = data->width;
	if (data->d)
		free(data->d);
	exit(i);
}

int		ft_exit(t_data *data, int i)
{
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	if (data->parsing)
	{
		if ((data->b_path > 1 || data->b_path == 0) && data->texture[0].img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->texture[0].img_ptr);
		if ((data->b_path > 2 || data->b_path == 0) && data->texture[1].img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->texture[1].img_ptr);
		if ((data->b_path > 3 || data->b_path == 0) && data->texture[2].img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->texture[2].img_ptr);
		if ((data->b_path > 4 || data->b_path == 0) && data->texture[3].img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->texture[3].img_ptr);
		if ((data->b_path > 5 || data->b_path == 0) && data->texture[4].img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->texture[4].img_ptr);
	}
	if (data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	if (data->mlx_ptr)
	{
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	ft_exit2(data, i);
	exit(i);
}
