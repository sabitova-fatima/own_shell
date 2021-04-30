# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>

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

int main (int argc, char **argv, char **env)
{
    char    dir[4096];
	char	*line;
    char    **command;
	char	*command_dir;
    char    *path;
	pid_t	pid;

    // получаем директорию в виде строки
    getcwd(dir, 4096);

    while (1)
	{
        ft_putstr(dir);
        ft_putstr(" \033[0m\033[33msh>\033[0m$ ");
        get_next_line(&line);
        command = ft_strsplit(line, ' ');

        // надо найти и считать с path
        path = "/bin";

        command_dir = ft_strjoin(ft_strjoin(path, "/"), command[0]);

        pid = fork();
        if (pid == 0)
        execve(path, command, env);
        wait(&pid);

        free(line);
        line = NULL;
	}
}