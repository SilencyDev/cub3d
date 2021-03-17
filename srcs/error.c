/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:32:37 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/17 13:03:51 by kmacquet         ###   ########.fr       */
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

int		is_save(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i == 6 && s[i - 1] == 'e' && s[i - 2] == 'v'
		&& s[i - 3] == 'a' && s[i - 4] == 's'
		&& s[i - 5] == '-' && s[i - 6] == '-')
		return (1);
	ft_error("The 2nd argument isn't --save");
	return (0);
}
