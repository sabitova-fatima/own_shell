#include "minishell.h"

int start_own_function (char **command, char **env, char *line)
{
    if (ft_strcmp("echo", command[0]) == 0)
        return(my_echo(command, line));
    if (ft_strcmp("cd", command[0]) == 0)
        return(my_cd(command));
    if (ft_strcmp("pwd", command[0]) == 0)
        return(my_pwd(command));
    if (ft_strcmp("export", command[0]) == 0)
        return(my_export(command));
    if (ft_strcmp("unset", command[0]) == 0)
        return(my_unset(command));
    if (ft_strcmp("env", command[0]) == 0)
        return(my_env(command, env));
    if (ft_strcmp("exit", command[0]) == 0)
        return(my_exit(command));
    return (0);
}

char* find_path(char **env)
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

void put_prompt(void)
{
    char dir_name[4096 + 1];
    getcwd(dir_name, 4096);
    ft_putstr(dir_name);
    ft_putstr(" \033[0m\033[33me-bash>\033[0m$ ");
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

// void	ctrl_c(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		ft_putstr("\n");
// 		put_prompt();
// 		signal(SIGINT, ctrl_c);
// 	}
// }

// void	ctrl_slash(int signo)
// {
// 	if (signo == SIGQUIT)
// 	{
// 		exit(0);
// 	}
// }

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

int main (int argc, char **argv, char **env)
{
	pid_t	pid;
    char    *dir_name;
	char	*line;
    char    **command;
	char	*command_dir;
    char    *dir;
    char    **dirs;
    int     is_own;
	char    ****new;
    int     m;
    int     ****fd;

    int     i;
    int     j;


    // dir_name = malloc(4096);
    // getcwd(dir_name, 4096);

    is_own = 0;
    dir = find_path(env); // переменная path
    dirs = ft_strsplit(dir, ':'); // переменная path разделенная 

    while (1)
	{
        put_prompt();
        // signal(SIGINT, ctrl_c); // для crtl c
        // signal(SIGQUIT, ctrl_slash); // для crtl /
        get_next_line(0, &line);
        // new = super_split(line);
        new = super_split(line, env, &fd);

        
        i = 0;
        j = 0;
        while (new[j])
        {
            i = 0;
            while (new[j][i])
            {
                command = cut_command(new[j][i]);

                is_own = start_own_function(command, env, line);
                if (is_own == 0)
                {
                    command_dir = find_dir_path(command, dirs);
                    pid = fork();
                    if (pid == 0 && command_dir)
                        execve(command_dir, command, env);
                    wait(&pid);
                }
                i++;
            }
            j++;
        }
	}
    // free (dir_name);
}



// int main(int argc, char **argv, char **env)
// {
// 	int i;
// 	int j;
// 	char *s;
// 	char ****all;
// 	int ****fd;

// 	while (get_next_line(0, &s))
// 	{
// 		all = super_split(s, env, &fd);
// 		free(s);
// 	}
// }