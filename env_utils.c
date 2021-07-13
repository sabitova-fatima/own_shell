#include "minishell.h"

int	where_to_put_env(char *name, char **env_copy)
{
	int		i;
	int		end_name;

	i = -1;
	while (env_copy[++i])
	{
		end_name = find_end_name(name);
		if (ft_strncmp(name, env_copy[i], end_name) == 0)
			return (i);
	}
	return (i);
}

void	help_export(char *key)
{
	printf("export: not an identifier: %s\n", key);
	g_global.error_status = 1;
}

char	**export_name_val(char *key, char *value, char **env_copy)
{
	int		n_var;
	char	*right_side;

	if ((key[0] >= 'A' && key[0] <= 'Z') || (key[0] >= 'a' && key[0] <= 'z'))
	{
		n_var = where_to_put_env(key, env_copy);
		if (env_copy[n_var])
			free(env_copy[n_var]);
		else
			env_copy = realloc_env(n_var + 1, env_copy);
		if (value)
		{	
			right_side = ft_strjoin("=", value);
			env_copy[n_var] = ft_strjoin(key, right_side);
			free(right_side);
		}
		else
			env_copy[n_var] = key;
	}
	else
		help_export(key);
	// free(key);
	if (value)
		free(value);
	return (env_copy);
}

char	**my_unset(char **env, char **command, int *result)
{
	int		i;
	int		i_key;

	if (!command[1])
	{
		printf("Too few arguments\n");
		return (env);
	}
	i = 0;
	while (command[++i])
	{
		i_key = where_to_put_env(command[i], env);
		if (env[i_key])
			env = unset_env(i_key, env);
	}
	*result = 1;
	return (env);
}

char	**unset_env(int i_key, char **env)
{
	int		i;

	i = i_key;
	while (env[i + 1])
	{
		free(env[i]);
		env[i] = ft_strdup(env[i + 1], ft_strlen(env[i + 1]));
		i++;
	}
	free(env[i]);
	env = realloc_env(i, env);
	return (env);
}
