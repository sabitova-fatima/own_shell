/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:23:36 by hdamion           #+#    #+#             */
/*   Updated: 2021/01/04 10:18:40 by hdamion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

void	*ft_memmove(void *dest, const void *src, int length);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
int		is_end(char *str);
char	*get_save(char *save);
char	*get_line(char *str);
int		get_next_line(int fd, char **line);

#endif
