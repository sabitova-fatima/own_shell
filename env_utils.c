#include "minishell.h"

int	where_to_put_env(char *name, char **env_copy)
{
	int		i;
	int 	end_name;

	i = -1;
	while (env_copy[++i])
	{
		end_name = find_end_name(name);
		if (ft_strncmp(name, env_copy[i], end_name) == 0)
			return (i);
	}
	return (i);
}

char	*key_value(char *value)
{
	char	*right_side;
	char	*right_side2;
	char	*temp;

	right_side2 = (char *)malloc(1);
	if (value)
	{
		right_side = ft_strjoin("=\"", value);
		temp = right_side2;
		right_side2 = ft_strjoin(right_side, "\"");
		free(temp);
		if (right_side)
			free(right_side);
	}
	return (right_side2);
}

char	**export_name_val(char *key, char *value, char **env_copy)
{
	int		n_var;
	char	*right_side;

	if ((key[0] >= 'A' && key[0] <= 'Z') || (key[0] >= 'a' && key[0] <= 'z'))
	{
		right_side = key_value(value);
		n_var = where_to_put_env(key, env_copy);
		if (env_copy[n_var])
			free(env_copy[n_var]);
		else
			env_copy = realloc_env(n_var + 1, env_copy);
		env_copy[n_var] = ft_strjoin(key, right_side);
		if (right_side)
			free(right_side);
	}
	else
	{
		printf("export: not an identifier: %s\n", key);
		g_global.error_status = 1;
	}
	free(key);
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
