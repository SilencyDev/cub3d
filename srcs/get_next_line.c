/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:33:06 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/20 10:16:35 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char				*ft_memalloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (!(ptr = malloc(size)))
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}

void				*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = c;
	return (s);
}

int					ft_memdel(void **ptr)
{
	if (*ptr)
	{
		ft_memset(*ptr, 0, ft_strlen(*ptr));
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

int					get_next_line(int fd, char **line)
{
	ssize_t		r;
	char		bf[BUFFER_SIZE + (r = 1)];
	static char	*p_l = NULL;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	p_l == NULL ? p_l = ft_memalloc(1) : NULL;
	while (!ft_strchr(p_l, '\n') && (r = read(fd, bf, BUFFER_SIZE)) > 0)
	{
		bf[r] = '\0';
		tmp = ft_strjoin(p_l, bf);
		ft_memdel((void **)&p_l);
		p_l = tmp;
	}
	if (r == 0)
		*line = ft_strdup(p_l);
	else if (r > 0)
		*line = ft_substr(p_l, 0, (ft_strchr(p_l, '\n') - p_l));
	else
		return (-1);
	tmp = ft_strdup(p_l + (ft_strlen(*line) + (r > 0 ? +1 : +0)));
	ft_memdel((void **)&p_l);
	p_l = tmp;
	return (r == 0 ? 0 * ft_memdel((void **)&p_l) : 1);
}
