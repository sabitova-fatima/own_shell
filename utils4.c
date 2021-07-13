#include "minishell.h"

void	to_up(char *s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
	}
}

void	heredoc(char *limiter)
{
	int		fd;
	char	*line;

	to_up(limiter);
	fd = open(".temp.txt", O_TRUNC | O_CREAT | O_RDWR, 0666);
	while (get_next_line(0, &line))
	{
		if (strcmp(line, limiter))
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		else
		{
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
}

char	*cleaner_help(char *new, t_data *data, char *s)
{
	if (new[0] == '\0' && data->type > 0 && data->fd_read != -1)
		new = join_char(new, 5);
	free(s);
	s = new;
	return (s);
}

char	*init_empty(void)
{
	char	*new;

	new = (char *)malloc(1);
	new[0] = '\0';
	return (new);
}

char	*ft_itoa(int n)
{
	char	a[11];
	char	*itog;
	int		i;
	int		j;

	i = 0;
	if (n == 0)
		a[i++] = '0';
	j = (n < 0);
	while (n != 0)
	{
		a[i++] = '0' + (char)(ft_znak(n % 10));
		n /= 10;
	}
	itog = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!itog)
		return (NULL);
	if (j == 1)
		itog[0] = '-';
	while (i > 0)
		itog[j++] = a[--i];
	itog[j] = '\0';
	return (itog);
}
