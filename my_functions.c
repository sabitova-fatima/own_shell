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

int my_export_output (char **command, char **env)
{
    printf("here will be my export\n");
    return (1);
}

// если без аргументов - выводит в алфавитном порядке все переменные, 
// сначала с большой буквы, а потом маленькой 
// если один аргумент, создает переменную со значением ''
// если два аргумента - создает переменную и присваивает ей значение

// функция ниже ничего из этого не делает
int my_export (char **command, char **env)
{
    if (command[0] && !command[1])
		my_export_output(command, env);

    else if (command[1] && !command[2])
    {
        ft_putstr("Too little arguments! Provide it like NAME VALUE\n");
        return (1);
    }
    else if (command[1] && command[2]&& command[3])
    {
        ft_putstr("Too many arguments! Provide it like NAME VALUE\n");
        return (1);
    }
    else if (command[1] && command[2])
    {
        printf("допустим, присвоение произошло\n");
        return (1);
    }
    return (1);
}

int my_unset (char **command)
{
    printf("Here will be my own unset\n");
    return (1);
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
    if (!command[1])
		my_env_output(command, env);
    else if (command[1])
        ft_putstr("No arguments, please!\n");
    return (1);
}

int my_exit (char **command)
{
    // add free?
    exit(0);
}
