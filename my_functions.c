#include "minishell.h"

int my_echo (char **command, char *line)
{
    printf("hi\n");
    return(1);
}

int my_cd(char **command)
{
    char *path;
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        if (!command[1])
        {
            ft_putstr("Provide a directory\n");
            return (1);
        }
        else if (command[1][0] != '/')
            path = ft_strjoin("/", command[1]);
        else
            path = command[1];
        if (chdir(path) == 0)
            return (1);
        else
        {
            ft_putstr("Directory not found\n");
            return (-1);
        }
        exit(0);
    }
    wait(&pid);
    return (1);
}

int my_pwd (char **command)
{
    pid_t pid;
    pid = fork();

    char    dir_name[4096];
    if (pid == 0)
    {
        getcwd (dir_name, 4096);
        ft_putstr(dir_name);
        ft_putchar('\n');
        exit(0);
    }
    wait(&pid);
    return (1);
}

char **my_export (char **command, char **env)
{
    char    *key;
    char    *value;
    int     end_name;
    int     i = 1;

    if (command[0] && !command[1])
		print_sorted_env(env);
    else
        while (command[i])
        {
            end_name = find_end_name(command[i]);
            if (end_name != -1)
            {
                key = ft_substr(command[i], 0, end_name);
                value = ft_substr(command[i], end_name+1, ft_strlen(command[i]));
            }
            env = export_name_val(key, value, env);
            i++;
        }
    return (env);
}

int my_env_output (char **command, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_putstr(env[i]);
        ft_putchar('\n');
        i++;
    }
    return (1);
}

int my_env(char **command, char **env)
{
    if (command[0] && !command[1])
		my_env_output(command, env);
    else if (command[1])
        ft_putstr("No arguments, please!\n");
    return (1);
}

int my_exit (char **command)
{
    exit(0);
}
