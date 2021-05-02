# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>

# include "minishell.h"
 
// экзаменационный гнл, хаха

int        get_next_line(char **line)
{
    char    c;
    char    *buf;
    int        rv;
    int        i = 0;

    if (!(buf = (char*)malloc(10000)))
        return (-1);
    *line = buf;
    while ((rv = read(0, &c, 1)) > 0 && c != '\n' && c != '\0')
    {
        buf[i] = c;
        i++;
    }
    buf[i] = '\0';
    if (rv == -1)
        return (-1);
    return (rv ? 1 : 0);
}

// порезать бы функцию на два ..
int my_echo (char **command, char *line)
{
    char *trimmed_line;
    int start;
    int i = 0;
    int flag;
    int len;
    // flag is 0 when there is -n
    len = ft_strlen(line);

    flag = ft_strcmp(command[1], "-n");
    while (line[i])
    {
        if (flag != 0 && line[i] == 'o')
        {
            i = i + 1;
            while (line[i] == ' ')
                i++;
            start = i;
            break;
        }
        if (flag == 0 && line[i] == '-' && line[i + 1] == 'n')
        {
            i = i + 2;
            while (line[i] == ' ')
                i++;
            start = i;
        }
        i++;
    }
    trimmed_line = ft_substr(line, start, len);

    if (flag == 0)
    {
        ft_putstr(trimmed_line);
        return (1);
    }
    else
    {
        ft_putstr(trimmed_line);
        ft_putchar('\n');
        return (1);
    }
    return (1);
}

// умеет переходить и без начальной /
// умышленно не умеет работать без аргументов, потому что сабж этого не требует
// может и научится, когда сделаю env глобальной переменной

int my_cd(char **command)
{
    char *path;

    if (!command[1])
        ft_putstr("Provide a directory\n");
    if (command[1][0] != '/')
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
}

// да, максимально бестолковые функции, ай ноу
// char* find_home(char **env)
// {
//     int i;

//     i = 0;

//     while (env[i])
//     {
//         if (env[i][0] == 'H' && env[i][1] == 'O' 
//         && env[i][2] == 'M' && env[i][3] == 'E')
//         return(env[i]);
//         i++;   
//     }
// }

int main (int argc, char **argv, char **env)
{
    char    dir_name[4096];
	char	*line;
    char    **command;
	char	*command_dir;
    char    *dir;
    char    **dirs;
	pid_t	pid;
    int     fd;
    int     is_own;
    int     i;
    
    // ооо да, я знаю, что переменных больше 5, извиняйте

    i = 0;

    is_own = 0;
    dir = find_path(env);
    dirs = ft_strsplit(dir, ':');

    while (1)
	{
        getcwd(dir_name, 4096);
        ft_putstr(dir_name);
        ft_putstr(" \033[0m\033[33msh>\033[0m$ ");
    
        get_next_line(&line);
        command = ft_strsplit(line, ' ');

        // передаю в функцию все, что может пригодиться :)
        is_own = start_own_function(command, env, line);
        if (is_own == 0)
        {
            while (dirs[i])
            {
                command_dir = ft_strjoin(ft_strjoin(dirs[i], "/"), command[0]);
                fd = open(command_dir, O_RDONLY);
                i++;
                if (fd >= 0)
                {
                    // close(fd); - почему ломается, если раскомментить?
                    break ;
                }
            }
        }
        i = 0;
        pid = fork();
        if (pid == 0)
            execve(command_dir, command, env);
        wait(&pid);
        if (fd < 0)
            ft_putstr("program not fround :(\n");
	}
}