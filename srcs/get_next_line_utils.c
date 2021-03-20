/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:06:07 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 13:03:08 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_strlen(char *s)
{
	int		n;

	n = 0;
	if (!s)
		return (0);
	while (s[n])
		n++;
	return (n);
}

char		*ft_strdup(char *str)
{
	char	*new;
	ssize_t	i;

	if (!(new = ft_memalloc(ft_strlen(str) + 1)))
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	return (new);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		len;
	char	*dest_init;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(dest = malloc(sizeof(char *) * len + 1)))
		return (NULL);
	dest_init = dest;
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
	return (dest_init);
}

char		*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = NULL;
	if (!s || !(dest = ((int)start >= ft_strlen(s)) ? malloc(1)
		: malloc(len + 1)))
		return (NULL);
	if ((int)start < ft_strlen(s))
		while (s[start] && len--)
			dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

char		*ft_strchr(char *s, int c)
{
	char	*str;

	str = s;
	while (*str != c)
		if (!*str++)
			return (NULL);
	return (str);
}
