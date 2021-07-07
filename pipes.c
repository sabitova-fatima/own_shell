#include "minishell.h"

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	i = 0;
	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	while ((one[i] || two[i]) && i < n)
	{
		if (one[i] != two[i])
			return (one[i] - two[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup2(char *s)
{
	int		i;
	char	*b;

	i = 0;
	b = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!b)
		return (NULL);
	while (s[i])
	{
		b[i] = s[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}

void	free_tmp(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static void	*freedom(char **johny, int w_count)
{
	int	i;

	i = 0;
	while (i < w_count)
		free(johny[i++]);
	free(johny);
	return (NULL);
}

static char	**iphone_pro(char const *s, int w_count, char c, char **johny)
{
	int		i;
	int		j;
	int		chari;

	i = -1;
	while (++i < w_count)
	{
		chari = 0;
		j = 0;
		while (*s == c)
			s++;
		while (s[chari] != c && s[chari] != '\0')
			chari++;
		johny[i] = (char *)malloc(sizeof(char) * (chari + 1));
		if (!johny[i])
			freedom(johny, i);
		while (j < chari)
			johny[i][j++] = *s++;
		johny[i][j] = '\0';
	}
	johny[i] = NULL;
	return (johny);
}

char	**ft_split3(char	const *s, char c)
{
	char	**johny;
	int		w_count;
	int		i;

	i = 0;
	w_count = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			w_count++;
		i++;
	}
	johny = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (!johny)
		return (NULL);
	johny = iphone_pro(s, w_count, c, johny);
	return (johny);
}

void	ft_lstadd_back(t_pipe **pipes, t_pipe *new_pipe)
{
	t_pipe	*temp;

	if (!(*pipes))
		*pipes = new_pipe;
	else
	{
		temp = *pipes;
		while (temp->next)
			temp = temp->next;
		temp->next = new_pipe;
		new_pipe->prev = temp;
	}
}

char	*check_path2(char **tmp, char *command)
{
	int		j;
	int		acc;
	char	*tmp2;
	char	*path;

	j = -1;
	while (tmp[++j])
	{
		tmp2 = ft_strjoin(tmp[j], "/");
		path = ft_strjoin(tmp2, command);
		acc = access(path, F_OK);
		free(tmp2);
		if (!acc)
			return (path);
		free(path);
	}
	return (NULL);
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

char	*absolut_path(char **env, char *command)
{
	char	*new_path;

	if (command[0] == '/')
	{
		if (!access(command, F_OK))
		{
			new_path = ft_strdup2(command);
			return (new_path);
		}
		else
			return (NULL);
	}
	return (check_path(command, env));
}

void parse_argv(char **argv, t_pipe *new_pipe, char **env)
{
	int i;
	int j;
	int len;

	i = -1;
	while(argv[++i])
	{
		if (argv[i][0] != 'E')
			len++;
	}
	new_pipe->command = (char **)malloc(sizeof(char *) * len + 1);
	j = -1;
	while (++j < len)
	{
		if (argv[j][0] != 'E')
			new_pipe->command[j] = ft_strdup2(argv[j]);
	}
	new_pipe->command[j] = NULL;
	new_pipe->path = absolut_path(env, new_pipe->command[0]);
	if (!new_pipe->path)
		printf("command not found\n");
	new_pipe->prev = NULL;
	new_pipe->next = NULL;
}

void	exec_child(t_pipe *pipes, char **env)
{
	if (!pipes->prev && !pipes->next)
		execve(pipes->path, pipes->command, env);
	else if (!pipes->prev)
		dup2(pipes->fd[1], 1);
	else if (!pipes->next)
		dup2(pipes->prev->fd[0], 0);
	else
	{
		dup2(pipes->prev->fd[0], 0);
		dup2(pipes->fd[1], 1);
		close(pipes->prev->fd[1]);
		close(pipes->fd[0]);
	}
	execve(pipes->path, pipes->command, env);
	exit(1);
}

void	launch_process(t_pipe *tmp, char **env)
{
	pid_t	pid;

	if (pipe(tmp->fd) == -1)
		printf("wrong pipe\n");
	pid = fork();
	tmp->pid = pid;
	if (pid == -1)
		printf("pid error\n");
	else if (pid == 0)
		exec_child(tmp, env);
	else
	{
		close(tmp->fd[1]);
		if (tmp->prev)
			close(tmp->prev->fd[0]);
		if (!tmp->next)
			close(tmp->fd[0]);
	}
}
void	exec_cmds(t_pipe *pipes, char **env)
{
	t_pipe	*tmp;
	int		status;

	tmp = pipes;
	while (tmp)
	{
//		printf("%s\n", pipes->path);
		launch_process(tmp, env);
		tmp = tmp->next;
	}
	tmp = pipes;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
}
void	free_pipes(t_pipe *pipes)
{
	int		i;
	t_pipe	*tmp;

	while (pipes)
	{
		tmp = pipes->next;
		i = -1;
		while (pipes->command[++i])
			free(pipes->command[i]);
		free(pipes->command);
		free(pipes->path);
		free(pipes);
		pipes = tmp;
	}
}
void parse_pipes(char ***new, char **env)
{
	t_pipe *pipes;
	t_pipe *new_pipe;
	int i;

	pipes = NULL;
	i = -1;
	while(new[++i])
	{
		new_pipe = (t_pipe *)malloc(sizeof(t_pipe));
		parse_argv(new[i], new_pipe, env);
		ft_lstadd_back(&pipes, new_pipe);
	}
	if (pipes)
		exec_cmds(pipes, env);
	free_pipes(pipes);

}
