/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khouten <khouten@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:19:45 by khouten           #+#    #+#             */
/*   Updated: 2020/12/03 16:19:47 by khouten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# define BUFFER_SIZE 10

typedef struct	s_list
{
	int				fd;
	char			*ostatok;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(int content);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s, int len);
char			*ft_strjoin(char *s1, char *s2);
int				clear(t_list **list, int fd, char *buf, int code);
int				get_next_line(int fd, char **line);
char			**ft_split(char	const *s, char c);

#endif
