#include "minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**env_copy;
	int		len;
	int		total_len;

	len = 0;
	i = 0;
	total_len = 0;
	while (env[len])
	{
		i = 0;
		while (env[len][i])
		{
			i++;
			total_len++;
		}
		len++;
	}
	env_copy = (char **)malloc(sizeof(char *) * (total_len + 1));
	i = -1;
	while (env[++i])
		env_copy[i] = ft_strdup(env[i], ft_strlen(env[i]));
	return (env_copy);
}

int	env_len(char **env)
{
	int		len;

	len = 0;
	while (env[len])
		len++;
	return (len - 1);
}

void	print_str(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
		printf("%s %s\n", "declare -x", env_copy[i++]);
}

char	**realloc_env(int added, char **env_copy)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * (added + 100));
	i = -1;
	while (env_copy[++i] && i < added)
	{
		new_env[i] = ft_strdup(env_copy[i], ft_strlen(env_copy[i]));
		free(env_copy[i]);
	}
	new_env[i] = NULL;
	free(env_copy);
	return (new_env);
}

int	find_end_name(char *name)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
			return (i);
		i++;
	}
	return (i);
}
