#include "minishell.h"

void	free_pipes(t_pipe *pipes)
{
	int		i;
	t_pipe	*tmp;

	while (pipes)
	{
		tmp = pipes->next;
		i = -1;
		if (pipes->command)
		{
			while (pipes->command[++i])
				free(pipes->command[i]);
			free(pipes->command);
		}
		if (pipes->path)
			free(pipes->path);
		free(pipes);
		pipes = tmp;
	}
}

int	is_one_command(t_pipe *pipes)
{
	int		i;
	t_pipe	*tmp;

	if (!pipes)
		return (0);
	tmp = pipes;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (i == 1)
		return (1);
	return (0);
}

int	if_bad_read(char **argv, int **fd)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (fd[i][0] == -1)
		{
			g_global.was_command = 1;
			return (1);
		}
	}
	return (0);
}

char **exec_pipes(t_pipe *pipes, char **env, char *input)
{
	if (!pipes)
		return (env);
	if (is_one_command(pipes))
		env = exec_one_command(pipes, env);
	else
		exec_cmds(pipes, env);
	free_pipes(pipes);
	if (!(input == NULL))
		add_history(input);
	g_global.was_command = 0;
	return(env);
}

char	**parse_pipes(char ***new, char **env, int ***fd, char *input)
{
	t_pipe	*pipes;
	t_pipe	*new_pipe;
	int		i;

	pipes = NULL;
	i = -1;
	while (new[++i])
	{
		new_pipe = (t_pipe *)malloc(sizeof(t_pipe));
		parse_argv(new[i], new_pipe, env, fd[i]);
		if (if_bad_read(new[i], fd[i]) || (new_pipe && !new_pipe->command[0]))
		{
			free(new_pipe->command);
			free(new_pipe);
			new_pipe = NULL;
		}
		ft_lstadd_back(&pipes, new_pipe);
	}
	return (exec_pipes(pipes, env, input));
}
