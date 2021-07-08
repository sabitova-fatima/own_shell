#include "minishell.h"

int start_own_function (char **command, char **env, char *line)
{
    if (command[0])
    {
//        if (ft_strcmp("cd", command[0]) == 0)
//            return(my_cd(command));
//        if (ft_strcmp("pwd", command[0]) == 0)
//            return(my_pwd(command));
        if (ft_strcmp("exit", command[0]) == 0)
            return(my_exit(command));
        if (ft_strcmp("env", command[0]) == 0)
            return(my_env(command, env));
    }
    return (0);
}

char **start_env_funcs(char **command, char **env, char *line)
{
    if (command[0])
    {
        if (ft_strcmp("export", command[0]) == 0)
            env = my_export(command, env);
        if (ft_strcmp("unset", command[0]) == 0)
            env = my_unset(env, command);
    }
    return (env);
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
        if (command[0])
            command_dir = ft_strjoin(ft_strjoin(dirs[m], "/"), command[0]);
        fd = open(command_dir, O_RDONLY);
        m++;
        if (fd >= 0)
            break ;
    }
    if (fd < 0 && command[0])
    {
        ft_putstr("program not found :(\n");
        return (NULL);
    }
    return (command_dir);
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
    char    *command_dir;
	pid_t	pid;

    signal(SIGQUIT, ctrl_slash_kid);
    command_dir = find_dir_path(command, dirs);
    if (command_dir == NULL)
        return (0);
    signal(SIGINT, ctrl_c_kid);
    if (command_dir != NULL)
        pid = fork();
    if (pid == 0 && command_dir != NULL)
        execve(command_dir, command, env);
    wait(&pid);
    return (1);
}