#include "minishell.h"

char	**exec_one_command(t_pipe *tmp, char **env)
{
	pid_t	pid;
	int		status;
	char	**env_new;
	int		old_fd[2];

	signal(SIGINT, ctrl_c_kid);
	signal(SIGQUIT, ctrl_slash);
	manage_fd(tmp, old_fd, 0);
	env_new = own_function(tmp, env);
	if (!env_new && tmp->path)
	{
		pid = fork();
		if (pid == 0)
		{
			if (!g_global.was_command)
				execve(tmp->path, tmp->command, env);
			exit(1);
		}
		else if (pid > 0)
			waitpid(pid, &status, 0);
	}
	manage_fd(tmp, old_fd, 1);
	if (env_new)
		return (env_new);
	return (env);
}

void	exec_cmds(t_pipe *pipes, char **env)
{
	t_pipe	*tmp;
	int		status;
	int		old_fd[2];

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

void	manage_fd(t_pipe *tmp, int *old_fd, int a)
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
