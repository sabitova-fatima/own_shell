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

char* find_path(char **env)
{
    int i;

    i = 0;

    while (env[i])
    {
        // printf("%s\n\n\n", env[i]);
        if (env[i][0] == 'P' && env[i][1] == 'A' 
        && env[i][2] == 'T' && env[i][3] == 'H')
        return(env[i]);
        i++;   
    }
}

int main (int argc, char **argv, char **env)
{
    char    dir[4096];
	char	*line;
    char    **command;
    // char    **stroka;
	char	*command_dir;
	// char	*tmp;
    char    *path;
    char    **paths;
	pid_t	pid;

    int i = 0;

    // получаем директорию в виде строки
    getcwd(dir, 4096);

    path = find_path(env);
    // printf("PATH IS: %s\n", path);

    paths = ft_strsplit(path, ':');
    // while (paths[i])
    // {
    //     printf("paths %d %s\n\n", i, paths[i]);
    //     i++;
    // }
int fd;
    while (1)
	{
        ft_putstr(dir);
        ft_putstr(" \033[0m\033[33msh>\033[0m$ ");
        get_next_line(&line);
        
        // stroka = ft_strsplit(line, ';');
        command = ft_strsplit(line, ' ');
        // printf("%s\n", command);

        // надо найти и считать с path
        // while (paths[i])
        // {
        //     command_dir = ft_strjoin(ft_strjoin(paths[i], "/"), command[0]);
        //     // printf("%s\n", tmp);
        //     i++;
        //     fd = open(command_dir, O_RDONLY);
        //     if (fd > 0)
        //     break ;
        //     // printf("fd: %d", fd);
        // }
        command_dir = ft_strjoin(ft_strjoin("/usr/bin", "/"), command[0]);

        // printf("tmp: %s\n", command_dir);
        // command_dir = ft_strjoin(ft_strjoin(path, "/"), command[0]);
        // printf("%s\n", command_dir);
        
        pid = fork();
        if (pid == 0)
            execve(command_dir, command, env);
        wait(&pid);

        // free(line);
        // line = NULL;
	}
}