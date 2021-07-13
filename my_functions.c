#include "minishell.h"

int	my_echo(char **command)
{
	int	i;
	int	count;
	int	len;

	len = 0;
	count = 0;
	while (command[len])
		len++;
	i = 0;
	if (len > 1)
	{
		while (command[++i] && ft_strncmp(command[i], "-n", 2) == 0)
			count = 1;
		while (command[i])
		{
			ft_putstr(command[i]);
			if (command[i + 1] && command[i][0] != '\0')
				ft_putstr(" ");
			i++;
		}
	}
	if (count == 0)
		write(1, "\n", 1);
	return (1);
}

int	my_cd(char **command)
{
	char	*path;

	if (!command[1])
	{
		ft_putstr("Provide a directory\n");
		return (1);
	}
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

int	my_pwd (void)
{
	char	dir_name[4096];

	getcwd (dir_name, 4096);
	ft_putstr(dir_name);
	ft_putchar('\n');
	return (1);
}

char	**my_export (char **command, char **env, int *result)
{
	char	*key;
	char	*value;
	int		end_name;
	int		i;

	i = 0;
	*result = 1;
	if (command[0] && !command[1])
		print_sorted_env(env);
	else
	{
		while (command[++i])
		{
			end_name = find_end_name(command[i]);
			value = NULL;
			key = ft_substr(command[i], 0, end_name);
			if (command[i][end_name] == '=')
				value = ft_substr(command[i], end_name + 1, \
					ft_strlen(command[i]));
			env = export_name_val(key, value, env);
		}
	}
	return (env);
}

int	print_sorted_env(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*temp;
	char	**env_copy;

	env_copy = copy_env(env);
	len = env_len(env_copy);
	i = -1;
	while (++i < len + 1)
	{
		j = i;
		while (++j < len + 1)
		{
			if (strcmp(env_copy[i], env_copy[j]) > 0)
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
		}
	}
	print_str(env_copy);
	freedom_2d(env_copy);
	return (1);
}
