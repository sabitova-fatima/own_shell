#include "minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**env_copy;
	int		len;

	len = 0;
	while (env[len])
		len++;
	env_copy = (char **)malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (env[++i])
		env_copy[i] = ft_strdup(env[i], ft_strlen(env[i]));
	env_copy[i] = NULL;
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
	int	j;
	int	end_name;

	i = 0;
	j = 0;
	while (env_copy[i])
	{
		end_name = find_end_name(env_copy[i]);
		j = 0;
		printf("declare -x ");
		while (j <= end_name)
			printf("%c", env_copy[i][j++]);
		if (with_value(env_copy[i]) == 42)
		{
			printf("\"");
			while (env_copy[i][j])
				printf("%c", env_copy[i][j++]);
			printf("\"");
		}
		printf("\n");
		i++;
	}
}

int	count_total_len(char **env)
{
	int	total_len;
	int	len;
	int	i;

	len = 0;
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
	return (total_len);
}

char	**realloc_env(int added, char **env_copy)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * \
		(count_total_len(env_copy) + 10000));
	i = 0;
	while (env_copy[i] && i < added)
	{
		new_env[i] = ft_strdup(env_copy[i], ft_strlen(env_copy[i]));
		free(env_copy[i]);
		i++;
	}
	new_env[i] = NULL;
	free(env_copy);
	return (new_env);
}
