#include "minishell.h"

int my_echo (char **command, char *line)
{
    char *trimmed_line;
    int start;
    int i = 0;
    // int flag;
    int len;
    // flag is 0 when there is -n
    len = ft_strlen(line);

    // flag = ft_strcmp(command[1], "-n");
    while (line[i])
    {
        // if (flag != 0 && line[i] == 'o')
        // {
            i = i + 1;
            while (line[i] == ' ')
                i++;
            start = i;
            break;
        // }
        // if (flag == 0 && line[i] == '-' && line[i + 1] == 'n')
        // {
        //     i = i + 2;
        //     while (line[i] == ' ')
        //         i++;
        //     start = i;
        // }
        i++;
    }
    trimmed_line = ft_substr(line, start, len);

    // if (flag == 0)
    // {
    //     ft_putstr(trimmed_line);
    //     return (1);
    // }
    // else
    // {
        ft_putstr(trimmed_line);
        ft_putchar('\n');
        return (1);
    // }
    return (1);
}

int my_cd(char **command)
{
    char *path;

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
}

int my_pwd (char **command)
{
    char    dir_name[4096];
    getcwd(dir_name, 4096);

    ft_putstr(dir_name);
    ft_putchar('\n');
    return (1);
}

int my_export (char **command)
{
    printf("Here will be my own export\n");
    return (1);
}

int my_unset (char **command)
{
    printf("Here will be my own unset\n");
    return (1);
}

int my_env (char **command, char **env)
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

int my_exit (char **command)
{
    // add free?
    exit(0);
}
