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

#include "minishell.h"

char	*ft_empty(void)
{
	char	*empty;

	empty = (char *)malloc(sizeof(char));
	if (!empty)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}

t_list	*find_ptr(t_list **all_data, int fd)
{
	t_list	*tmp;

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
	char	*next_line;

	if (fd_data->ostatok == NULL)
		return (ft_empty());
	next_line = ft_strchr(fd_data->ostatok, '\n');
	if (next_line)
	{
		*next_line++ = '\0';
		*line = ft_strdup(fd_data->ostatok, -1);
		if (!(*line))
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
	char	*this_line;
	char	*tmp;

	this_line = ft_strchr(buf, '\n');
	if (this_line)
	{
		*this_line++ = '\0';
		fd_data->ostatok = ft_strdup(this_line, -1);
//		if (!fd_data->ostatok)
//			return (0);
	}
	tmp = *line;
	*line = ft_strjoin(*line, buf);
	if (!(*line))
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
	buf = (char *)malloc(sizeof(char) * buff_size + 1);
	if (!buf)
		return (clear(all_data, fd, buf, -1));
	while (fd_data->ostatok == NULL)
	{
		bytes = read(fd, buf, 10);
		if (!bytes)
			break ;
		if (bytes < 0)
			return (clear(all_data, fd, buf, -1));
		buf[bytes] = '\0';
		if (!boss_reader(buf, fd_data, line))
			return (clear(all_data, fd, buf, -1));
	}
	if (bytes < buff_size && !(fd_data->ostatok))
		return (clear(all_data, fd, buf, 0));
	free(buf);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static t_list	*all_data;
	t_list			*fd_data;
	const long long buff_size = BUFFER_SIZE;
	char			test[1];
	int a;

	if (fd < 0 || buff_size <= 0 || !line || read(fd, test, 0) < 0
		|| !(fd_data = find_ptr(&all_data, fd)))
		return (-1);
	*line = do_ostatok(fd_data, line);
	if (!(*line))
		return (clear(&(all_data), fd, NULL, -1));
	a = read_buf(&(all_data), line, fd, fd_data);
//	free(fd_data->ostatok);
	return(a);
}


