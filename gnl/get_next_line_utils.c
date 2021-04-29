/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:23:24 by hdamion           #+#    #+#             */
/*   Updated: 2021/01/04 10:22:35 by hdamion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, int length)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	if (src < dest)
		while (length > 0)
		{
			length--;
			d[length] = s[length];
		}
	else
		while (length > 0)
		{
			length--;
			*d++ = *s++;
		}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		l2;
	int		l1;

	if (!s1 && !s2)
		return (0);
	l2 = ft_strlen(s1);
	l1 = ft_strlen(s2);
	if (!(result = malloc(l2 + l1 + 1)))
		return (0);
	ft_memmove(result, s1, l2);
	ft_memmove((result + l2), s2, l1);
	result[l2 + l1] = '\0';
	free((char*)s1);
	return (result);
}

size_t	ft_strlen(const char *s)
{
	int		res;

	res = 0;
	if (!s)
		return (0);
	while (s[res] != '\0')
		res++;
	return (res);
}

int		is_end(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '\n')
			return (0);
		str++;
	}
	return (1);
}
