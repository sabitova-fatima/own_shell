#include "minishell.h"

void	parse_argv(char **argv, t_pipe *new_pipe, char **env, int **fd)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (fd[i][0] == -1)
			new_pipe->command = NULL;
		if (fd[i][0] == -1)
			return ;
	}
	simple_init(argv, new_pipe, fd, env);
	if (!new_pipe->path && new_pipe->command[0] && \
		!is_in_list(new_pipe->command[0]))
	{
		printf("e-bash: %s: command not found\n", new_pipe->command[0]);
		g_global.bad_command = 1;
	}
	else
	{
		g_global.bad_command = 0;
		g_global.error_status = 0;
	}
	new_pipe->prev = NULL;
	new_pipe->next = NULL;
}

void	simple_init(char **argv, t_pipe *new_pipe, int **fd, char **env)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = 0;
	while (argv[++i])
	{
		if (argv[i][0] != 5)
			len++;
	}
	new_pipe->fd_read = fd[i - 1][0];
	new_pipe->fd_write = fd[i - 1][1];
	new_pipe->command = (char **)malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = -1;
	while (argv[++i])
	{
		if (argv[i][0] != 5 && ++j < len)
			new_pipe->command[j] = ft_strdup2(argv[i]);
	}
	new_pipe->command[++j] = NULL;
	new_pipe->path = absolut_path(env, new_pipe->command[0]);
}

char	*absolut_path(char **env, char *command)
{
	int		i;
	int		fd;

	if (!command || command[0] == '\0')
		return (NULL);
	if ((command[0] == '.' && !command[1]) || (command[0] == '.' && \
		command[1] =='.' && !command[2]))
		return (NULL);
	i = -1;
	while (command[++i])
	{
		if (command[i] == '/')
		{
			fd = open(command, O_RDONLY);
			if (fd != -1)
			{
				close(fd);
				return (ft_strdup2(command));
			}
			return (NULL);
		}
	}
	return (check_path(command, env));
}

char	*check_path(char *command, char **env)
{
	char	**path_arr;
	char	*path;
	int		i;
	char	**tmp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp2(env[i], "PATH", 4))
		{
			path_arr = ft_split3(env[i], '=');
			tmp = ft_split3(path_arr[1], ':');
			path = check_path2(tmp, command);
			free_tmp(path_arr);
			free_tmp(tmp);
			if (path)
				return (path);
		}
	}
	return (NULL);
}

char	*check_path2(char **tmp, char *command)
{
	int		j;
	char	*tmp2;
	char	*path;
	int		fd;

	j = -1;
	while (tmp[++j])
	{
		tmp2 = ft_strjoin(tmp[j], "/");
		path = ft_strjoin(tmp2, command);
		fd = open(path, O_RDONLY);
		free(tmp2);
		if (fd != -1)
		{
			close(fd);
			return (path);
		}
		free(path);
	}
	return (NULL);
}
