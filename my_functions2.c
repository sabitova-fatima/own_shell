#include "minishell.h"

int with_value(char *env)
{
	int i;
	i = 0;

	while (env[i])
	{
		if(env[i] == '=')
			return(42);
		i++;
	}
	return(0);
}

int	my_env(char **command, char **env)
{
	int	i;

	if (command[0] && !command[1])
	{
		i = 0;
		while (i < env_len(env))
		{
			if (with_value(env[i]) == 42)
				ft_putstr(env[i]);
			ft_putchar('\n');
			i++;
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
