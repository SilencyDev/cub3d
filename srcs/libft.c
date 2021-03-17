/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:42:03 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/17 13:20:14 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_countword(char *str, char *charset)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (is_charset(*str, charset) && *str)
			str++;
		if (!is_charset(*str, charset) && *str)
		{
			while (!is_charset(*str, charset) && *str)
				str++;
			i++;
		}
	}
	return (i);
}

void		ft_strcpy(char *start, char *str, char *dest)
{
	int	j;

	j = 0;
	while (start < str)
		dest[j++] = *start++;
	dest[j] = '\0';
}

char		**ft_split_str(char *s, char *charset)
{
	char	**dest;
	char	*start;
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (!s)
		return (NULL);
	if (!(dest = malloc(sizeof(char *) * (ft_countword(str, charset) + 1))))
		return (NULL);
	while (*str)
		if (!is_charset(*str, charset))
		{
			start = str;
			while (*str && !is_charset(*str, charset))
				str++;
			dest[i] = malloc(str - start + 1);
			ft_strcpy(start, str, dest[i]);
			i++;
		}
		else
			str++;
	dest[i] = NULL;
	return (dest);
}

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putstr_fd(char *s, int fd)
{
	while (s && *s)
		ft_putchar_fd(*s++, fd);
}
