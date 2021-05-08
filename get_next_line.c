/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khouten <khouten@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:19:40 by khouten           #+#    #+#             */
/*   Updated: 2020/12/03 16:19:41 by khouten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list		*find_ptr(t_list **all_data, int fd)
{
	t_list *tmp;

	if (!(*all_data))
		return (*all_data = ft_lstnew(fd));
	tmp = *all_data;
	while ((tmp->fd != fd && tmp->next != 0))
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	else
	{
		tmp->next = ft_lstnew(fd);
		return (tmp->next);
	}
}

static char	*do_ostatok(t_list *fd_data, char **line)
{
	char *empty;
	char *next_line;

	if (fd_data->ostatok == NULL)
	{
		if (!(empty = (char *)malloc(sizeof(char))))
			return (NULL);
		empty[0] = '\0';
		return (empty);
	}
	if ((next_line = ft_strchr(fd_data->ostatok, '\n')))
	{
		*next_line++ = '\0';
		if (!((*line) = ft_strdup(fd_data->ostatok, -1)))
			return (NULL);
		next_line = ft_strdup(next_line, -1);
		free(fd_data->ostatok);
		fd_data->ostatok = next_line;
		return (*line);
	}
	*line = fd_data->ostatok;
	fd_data->ostatok = NULL;
	return (*line);
}

static int	boss_reader(char *buf, t_list *fd_data, char **line)
{
	char *this_line;
	char *tmp;

	if ((this_line = ft_strchr(buf, '\n')))
	{
		*this_line++ = '\0';
		if (!(fd_data->ostatok = ft_strdup(this_line, -1)))
			return (0);
	}
	tmp = *line;
	if (!(*line = ft_strjoin(*line, buf)))
		return (0);
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	read_buf(t_list **all_data, char **line, int fd, t_list *fd_data)
{
	const long long buff_size = BUFFER_SIZE;
	char			*buf;
	long long		bytes;

	bytes = 0;
	if (!(buf = (char *)malloc(sizeof(char) * buff_size + 1)))
		return (clear(all_data, fd, buf, -1));
	while ((fd_data->ostatok == NULL) && (bytes = read(fd, buf, BUFFER_SIZE)))
	{
		if (bytes < 0)
			return (clear(all_data, fd, buf, -1));
		buf[bytes] = '\0';
		if (!boss_reader(buf, fd_data, line))
			return (clear(all_data, fd, buf, -1));
	}
	if (bytes < buff_size && (fd_data->ostatok) == NULL)
		return (clear(all_data, fd, buf, 0));
	free(buf);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*all_data;
	t_list			*fd_data;
	const long long buff_size = BUFFER_SIZE;
	char			test[1];

	if (fd < 0 || buff_size <= 0 || !line || read(fd, test, 0) < 0 ||
		!(fd_data = find_ptr(&all_data, fd)))
		return (-1);
	if (!(*line = do_ostatok(fd_data, line)))
		return (clear(&(all_data), fd, NULL, -1));
	return (read_buf(&(all_data), line, fd, fd_data));
}


