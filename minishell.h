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

#ifndef MINISHELL_H
# define MINISHELL_H
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
char			*ft_strdup(char *s, int len);
char			*ft_strjoin(char *s1, char *s2);
int				clear(t_list **list, int fd, char *buf, int code);
int				get_next_line(int fd, char **line);
char			**ft_split(char	 *s, char c);
int             ft_strlen(char const *s);
char			*ft_strdup_new(char *s, int len);
void			skip_spaces(char *line, int *i);
char			*ft_strjoin_char(char *s1, char c);
int 			into_quotes(char *s, int i);
int 			into_command_split(char *s, int *i, int w_count, char c);
int 			into_command_split2(char *s, int letter, char c);
char 			*join_char(char *s, char c);
char 			***super_split(char *s);

// libft
void			ft_bzero(void *s, int n);
char			*ft_strnew(int size);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
static int		int_len(const char *str, char c);
static int		ft_ln(const char *str, char c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strdup1(const char *s1);
int				ft_strcmp(char *s1, char *s2);
char			*ft_substr(char const *s, unsigned int start, int len);

int my_echo (char **command, char *line);
int my_cd(char **command);
int my_pwd (char **command);
int my_unset (char **command);
int my_export (char **command);
int my_env (char **command, char **env);
int my_exit (char **command);








#endif
