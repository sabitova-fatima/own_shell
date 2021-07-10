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
	char	*tmp2;
	char	*path;
	int 	fd;

	j = -1;
	while (tmp[++j])
	{
		tmp2 = ft_strjoin(tmp[j], "/");
		path = ft_strjoin(tmp2, command);
		fd = open(path, O_RDONLY);
		close(fd);
		free(tmp2);
		if (fd != -1)
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
	int 	i;
	int 	fd;

	if (!command || command[0] == '\0')
		return (NULL);
	i = -1;
	while(command[++i])
	{
		if (command[i] == '/')
		{
			fd = open(command, O_RDONLY);
			close(fd);
			if (fd != -1)
				return (ft_strdup2(command));
			return (NULL);
		}
	}
	return (check_path(command, env));
}

void simple_init(char **argv, t_pipe *new_pipe, int **fd)
{
	int i;
	int j;
	int len;

	i = -1;
	len = 0;
	while(argv[++i])
	{
		if (argv[i][0] != 'Q')
			len++;
	}
	new_pipe->fd_read = fd[i - 1][0];
	new_pipe->fd_write = fd[i - 1][1];
	new_pipe->command = (char **)malloc(sizeof(char *) * len + 1);
	i = -1;
	j = -1;
	while (argv[++i])
	{
		if (argv[i][0] != 'Q' && ++j < len)
		{
			new_pipe->command[j] = ft_strdup2(argv[i]);
//			printf("%d [%s]\n", j, new_pipe->command[j]);
		}
	}
	new_pipe->command[++j] = NULL;
}


void parse_argv(char **argv, t_pipe *new_pipe, char **env, int **fd)
{
	simple_init(argv, new_pipe, fd);
	new_pipe->path = absolut_path(env, new_pipe->command[0]);
	if (!new_pipe->path && new_pipe->command[0] &&
	ft_strcmp ("exit", new_pipe->command[0])
	&& ft_strcmp("unset", new_pipe->command[0])
	&& ft_strcmp("export", new_pipe->command[0]))
	{
		printf("e-bash: %s: command not found\n", new_pipe->command[0]);
		global.error_status = 127;
	}
	new_pipe->prev = NULL;
	new_pipe->next = NULL;
}

char **own_function(t_pipe *tmp, char **env)
{
	int result;

	result = 0;
	if (!ft_strcmp("echo", tmp->command[0]))
		result = my_echo(tmp->command);
	if (!ft_strcmp("pwd", tmp->command[0]))
		result = my_pwd();
	if (!ft_strcmp("env", tmp->command[0]))
		result = my_env(tmp->command, env);
	if (!ft_strcmp("cd", tmp->command[0]))
		result = my_cd(tmp->command);
	if (!ft_strcmp("exit", tmp->command[0]))
		result = my_exit(tmp->command);
	if (!ft_strcmp("export", tmp->command[0]))
		env = my_export(tmp->command, env, &result);
	if (!ft_strcmp("unset", tmp->command[0]))
		env = my_unset(env, tmp->command, &result);
	if (result == 0)
		return (NULL);
	return (env);
}

void	exec_child(t_pipe *pipes, char **env)
{
	signal(SIGINT, ctrl_c_kid);
	// signal(SIGQUIT, ctrl_slash);

	if (pipes->fd_read == 0 && pipes->fd_write == 1)
	{
		if (!pipes->prev)
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
	}
	else if (pipes->fd_read > 0)
	{
		if (!pipes->prev)
			dup2(pipes->fd[1], 1);
	}
	if (own_function(pipes, env))
		exit(1);
	execve(pipes->path, pipes->command, env);
	exit(1);
}

char **samopal(t_pipe *tmp, char **env)
{
	char **env2;

	if (tmp->fd_read == 0 && tmp->fd_write == 1)
	{
		if (pipe(tmp->fd) == -1)
			printf("wrong pipe\n");
		if (tmp->next)
			dup2(tmp->fd[1], 1);
	}
	env2 = own_function(tmp, env);
	if (tmp->fd[1] != 0)
		close(tmp->fd[1]);
	return (env2);
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
		if (tmp->prev && tmp->prev->fd[0] != 0)
			close(tmp->prev->fd[0]);
		if (!tmp->next)
			close(tmp->fd[0]);
	}
}

void	 manage_fd(t_pipe *tmp, int *old_fd, int a)
{
	if (a == 0)
	{
		old_fd[1] = dup(1);
		old_fd[0] = dup(0);
		if (tmp->fd_write > 1)
			dup2(tmp->fd_write, 1);
		if (tmp->fd_read > 0)
			dup2(tmp->fd_read, 0);
	}
	else
	{
		dup2(old_fd[1], 1);
		dup2(old_fd[0], 0);
		if (tmp->fd_write > 1)
			close(tmp->fd_write);
		if (tmp->fd_read > 0)
			close(tmp->fd_read);
	}
}

void exec_cmds(t_pipe *pipes, char **env)
{
	t_pipe	*tmp;
	int		status;
	int old_fd[2];

	tmp = pipes;
	while (tmp)
	{
		manage_fd(tmp, old_fd, 0);
		launch_process(tmp, env);
		manage_fd(tmp, old_fd, 1);
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

int is_one_command(t_pipe *pipes)
{
	int i;
	t_pipe *tmp;

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

char  **exec_one_command(t_pipe *tmp, char **env)
{
	pid_t pid;
	int status;
	char **env_new;
	int old_fd[2];

	signal(SIGINT, ctrl_c_kid);
	signal(SIGQUIT, ctrl_slash);
	manage_fd(tmp, old_fd, 0);
	env_new = own_function(tmp, env);
	if (!env_new)
	{
		pid = fork();
		if (pid == 0)
			execve(tmp->path, tmp->command, env);
		else if (pid > 0)
			waitpid(pid, &status, 0);
	}
	manage_fd(tmp, old_fd, 1);
	if (env_new)
		return (env_new);
	return (env);

}

char **parse_pipes(char ***new, char **env, int ***fd, char *input)
{
	t_pipe *pipes;
	t_pipe *new_pipe;
	int i;

	pipes = NULL;
	i = -1;
	while(new[++i])
	{
		new_pipe = (t_pipe *)malloc(sizeof(t_pipe));
		parse_argv(new[i], new_pipe, env, fd[i]);
		if (!new_pipe->command[0])
			new_pipe = NULL;
		ft_lstadd_back(&pipes, new_pipe);
	}
	if (!pipes)
		return (env);
	if (is_one_command(pipes))
		env = exec_one_command(pipes, env);
	else
		exec_cmds(pipes, env);
	free_pipes(pipes);
	if (!(input == NULL))
            add_history(input);
	return (env);
}
