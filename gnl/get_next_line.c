/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:23:08 by hdamion           #+#    #+#             */
/*   Updated: 2021/01/04 10:40:52 by hdamion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*saved_line(char *saved)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!saved)
		return (0);
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (0);
	}
	if (!(result = malloc((ft_strlen(saved) - i) + 1)))
		return (0);
	i++;
	while (saved[i])
		result[j++] = saved[i++];
	result[j] = '\0';
	free(saved);
	return (result);
}

char	*get_line(char *str)
{
	int		i;
	char	*result;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(result = malloc(i + 1)))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int		get_next_line(int fd, char **line)
{
	char			*buf;
	static char		*saved;
	int				ret;

	ret = 1;
	if (!line || 1 <= 0 || fd < 0 || !(buf = malloc(1 + 1)))
		return (-1);
	while (ret != 0 && is_end(saved))
	{
		ret = read(fd, buf, 1);
		if (ret == -1)
		{
			free(buf);
			return (-1);
		}
		buf[ret] = '\0';
		saved = ft_strjoin(saved, buf);
	}
	free(buf);
	*line = get_line(saved);
	saved = saved_line(saved);
	if (ret == 0)
		return (0);
	return (1);
}
