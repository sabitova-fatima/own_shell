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
    char dir[4096];

	int		r;
	char	*line;

    getcwd(dir, 4096);

    ft_putstr(dir);
    ft_putstr(" \033[0m\033[33msh>\033[0m$ ");

    
	line = NULL;
	r = get_next_line(&line);
    printf("%s\n", line);
    free(line);
    line = NULL;
}