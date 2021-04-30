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


char	*get_env_var(char *var, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(env[i], tmp))
		{
			free(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

int main (int argc, char **argv, char **env)
{
    char dir[4096];

	int		r;
	char	*line;
    char    **command;
	char	*bin_path;


    int i = 0;

    getcwd(dir, 4096);

    ft_putstr(dir);
    ft_putstr(" \033[0m\033[33msh>\033[0m$ ");

    
	line = NULL;
	r = get_next_line(&line);
   	command = ft_strsplit(line, ' ');

    // printf("%s\n", line);
    // printf("%s\n", commands[0]);

    char    **path;
	path = ft_strsplit(get_env_var("PATH", env), ':');

    
    while (path && path[i])
	{
		if (ft_strstartswith(command[0], path[i]))
			bin_path = ft_strdup(command[0]);
		else
			bin_path = ft_pathjoin(path[i], command[0]);
        i++;
    }
    printf("%s\n", bin_path);

    // run_cmd(ft_strdup(command[0]), command);

    free(line);
    line = NULL;
}