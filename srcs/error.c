/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:32:37 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/09 17:26:17 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *s)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
	exit(1);
}

// int		is_save(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	if (i != 7)
// 		return (0)
	
// }
