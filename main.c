#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>

int start_own_function (char **command, char **env, char *line)
{
    if (ft_strcmp("echo", command[0]) == 0)
        return(my_echo(command, line));
    if (ft_strcmp("cd", command[0]) == 0)
        return(my_cd(command));
    if (ft_strcmp("pwd", command[0]) == 0)
        return(my_pwd(command));
    if (ft_strcmp("export", command[0]) == 0)
        return(my_export(command, env));
    if (ft_strcmp("unset", command[0]) == 0)
        return(my_unset(command));
    if (ft_strcmp("env", command[0]) == 0)
        return(my_env(command, env));
    if (ft_strcmp("exit", command[0]) == 0)
        return(my_exit(command));
    return (0);
}

char    *find_path(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (env[i][0] == 'P' && env[i][1] == 'A' 
        && env[i][2] == 'T' && env[i][3] == 'H')
        return(env[i]);
        i++;   
    }
    return (NULL);
}

void put_dirname(void)
{
    char dir_name[4096 + 1];
    getcwd(dir_name, 4096);
    ft_putstr(dir_name);
}

char *find_dir_path(char **command, char **dirs)
{
    int fd;
    int m = 0;
    char *command_dir;
    while (dirs[m])
    {
        command_dir = ft_strjoin(ft_strjoin(dirs[m], "/"), command[0]);
        fd = open(command_dir, O_RDONLY);
        m++;
        if (fd >= 0)
            break ;
    }
    if (fd < 0)
    {
        ft_putstr("program not found :(\n");
        return (NULL);
    }
    return (command_dir);
}

void	ctrl_c(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		put_dirname();
        ft_putstr(" \033[0m\033[33me-bash>\033[0m$ ");
		// signal(SIGINT, ctrl_c);
	}
}

void	ctrl_c_kid(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, ctrl_c_kid);
	}
}

void	ctrl_slash(int signo)
{
	if (signo == SIGQUIT)
	{
		exit(0);
	}   
}

char **cut_command(char ** command)
{
    int i;
    int j;

    i = 0;
    int len = 0;

    char ** res;
    while (command[i] || command[i + 1])
    {
        i++;
        len++;
    }
    res = malloc (sizeof(char *) * (len + 1));
    i = 0;
    j = 0;

    while (i < len)
    {
        if (command[i])
        {
            res[j] = command[i];
            i++;
            j++;
        }
        i++;
    }
    res[j] = NULL;
    return (res);
}

int start_builtin(char **command, char **dirs, char **env)
{
    char *command_dir;
	pid_t	pid;

    command_dir = find_dir_path(command, dirs);
    signal(SIGINT, ctrl_c_kid);
    if (command_dir != NULL)
        pid = fork();
    if (pid == 0 && command_dir != NULL)
        execve(command_dir, command, env);
    wait(&pid);
    signal(SIGQUIT, ctrl_slash);
    return (1);
}

int main (int argc, char **argv, char **env)
{
	char    ****new;
    int     ****fd;
    char    **command;
    char    *input;
    int     i;
    int     j;

    while (1)
	{
        put_dirname();
        signal(SIGINT, ctrl_c);
        input = readline(" \033[0m\033[33me-bash>\033[0m$ ");

        // фиксит сегу от ctrl d
        if (input == NULL)
            exit(0);
        new = super_split(input, env, &fd);
        i = 0;
        j = 0;
        while (new[j])
        {
            i = 0;
            while (new[j][i])
            {
                command = new[j][i];
                if (!start_own_function(command, env, input))
                    start_builtin(command, ft_strsplit(find_path(env), ':'), env);
                i++;
            }
            j++;
        }
        if (!(input == NULL))
            add_history(input);
	}
}
