#include "minishell.h"

int	my_env(char **command, char **env)
{
	int	i;

	if (command[0] && !command[1])
	{
		i = -1;
		while (env[++i])
		{
			ft_putstr(env[i]);
			ft_putchar('\n');
		}
	}
	else if (command[1])
		ft_putstr("No arguments, please!\n");
	return (1);
}

int	my_exit (void)
{
	exit(0);
}

void	write_error(t_data *data, char *filename)
{
	if (data->fd_read == -1)
	{
		write(2, "e-bash: ", ft_strlen("e-bash: "));
		write(2, filename, ft_strlen(filename));
		write(2, ": ", 2);
		perror("");
		g_global.read_trouble = 1;
	}
}

char	*ft_empty(void)
{
	char	*empty;

	empty = (char *)malloc(sizeof(char));
	if (!empty)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}

void	total_free(char *input, char ***new, int ***fd)
{
	free(input);
	freedom_3d(new);
	freedom_3d_int(fd);
}
