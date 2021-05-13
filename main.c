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
# include "get_next_line.h"

int w_count(char *s)
{
	int i;
	int count;
	char q;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ';')
			count++;
		else if (s[i] && s[i+1] == '\0')
			count++;
		else if (s[i] == '\\' && (s[i + 1] == ';' || s[i + 1] == '\'' ||
								  s[i + 1] == '"' || s[i + 1] == '\\'))
		{
			if (!s[i+2])
				count++;
			i++;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
			{
				if (s[i] == '\\' && q == '"' &&
					(s[i+1] == '"' || s[i+1] == '\\'))
					i++;
				i++;
			}
			if (!s[i+1])
				count++;
		}
		i++;
	}
	return (count);
}

char **split_semicolon(char *s, int count)
{
	char **arr;
	int i;
	int j;
	char q;


	arr = (char**)malloc(sizeof(char *) * count + 10);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		j = 0;
		while (s[j] && s[j] != ';')
		{
			if (s[j] == '\\' && (s[j + 1] == ';' || s[j + 1] == '\'' ||
								 s[j + 1] == '"' || s[j + 1] == '\\'))
				j++;
			else if (s[j] == '\'' || s[j] == '"')
			{
				q = s[j];
				j++;
				while (s[j] && s[j] != q)
				{
					if (s[j] == '\\' && q == '"' &&
						(s[j+1] == '"' || s[j+1] == '\\'))
						j++;
					j++;
				}
			}
			j++;
		}
		arr[i] = ft_strdup(s, j);
		s += j+1;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char ***split_spaces(char **arr, int count)
{
	char ***new;
	int i;

	new = (char ***)malloc(sizeof(char **) * count +10);
	i = 0;
	while (i < count)
	{
		new[i] = ft_split(arr[i], ' ');
		i++;
	}
	new[i] = NULL;
	return (new);
}

char ***super_split(char *s)
{
	int count;
	char **array;
	char ***new;

	count = w_count(s);
//	printf("%d\n", count);
	array = split_semicolon(s, count);
	if (!array)
		return (NULL);
	new = split_spaces(array, count);
	if (!new)
		return (NULL);
	return (new);
}

// int main(int argc, char **argv, char **env)
// {
// 	int i;
// 	int j;
// 	char *s;
// 	char ***new;

// 	while (get_next_line(0, &s))
// 	{
// 		new = super_split(s);
// 		if (!new)
// 			printf("error\n");

// 		i = 0;
// 		while (new[i])
// 		{
// 			j = 0;
// 			while (new[i][j])
// 			{
// 				write(1, "a\n", 2);
// 				printf("%s\n", new[i][j]);
// 				write(1, "X\n", 2);
// 				j++;
// 			}
// 			i++;
// 		}
// 	}
// }


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
    char *dir_name;
    dir_name = malloc(4096);
    getcwd(dir_name, 4096);
    ft_putstr(dir_name);
    ft_putstr(" \033[0m\033[33msh>\033[0m$ ");
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

void	ctrl_c(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		put_prompt();
		signal(SIGINT, ctrl_c);
	}
}

int main (int argc, char **argv, char **env)
{
    char    *dir_name;
	char	*line;
    char    **command;
	char	*command_dir;
    char    *dir;
    char    **dirs;
    int     fd;
    int     is_own;
    int     i;
	char    ***new;
	pid_t	pid;
    int     m;
    
    dir_name = malloc(4096);
    getcwd(dir_name, 4096);

    i = 0;

    is_own = 0;
    dir = find_path(env); // переменная path
    dirs = ft_strsplit(dir, ':'); // переменная path разделенная 

    while (1)
	{
        put_prompt();
        signal(SIGINT, ctrl_c); // для crtl c
        get_next_line(0, &line);
        new = super_split(line);
        
        i = 0;
        while (new[i])
        {
            command = new[i];

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
	}
    free (dir_name);
}