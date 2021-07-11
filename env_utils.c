#include "minishell.h"

int		where_to_put_env(char *name, char **env_copy)
{
	int		i;
	int		end_name;

	i = -1;
	while (env_copy[++i])
	{
		end_name = find_end_name(env_copy[i]);
		if (ft_strncmp(name, env_copy[i], end_name) == 0)
			return (i);
	}
	return (i);
}

char	**export_name_val(char *key, char *value, char **env_copy)
{
	int   	n_var;
	char	*right_side;

	if (value[0])
		right_side = ft_strjoin("=", value);
	else
		right_side = "=\"\"";
	n_var = where_to_put_env(key, env_copy);
	if (env_copy[n_var]) /* если переменная уже есть */
		free(env_copy[n_var]);
	else  /* если переменной еще нет */
		env_copy = realloc_env(n_var + 1, env_copy);
	env_copy[n_var] = ft_strjoin(key, right_side);
	return (env_copy);
}

char **my_unset(char **env, char **command, int *result)
{
	int i ;
	int i_key;

	i = 1;
	if (!command[1])
		printf("Too few arguments\n");
	else
	{
		while(command[i])
		{
			i_key = where_to_put_env(command[i], env);

			if (env[i_key])
				env = unset_env(i_key, env);
			i++;
		}
	}
	*result = 1;
	return (env);
}

char **unset_env(int i_key, char **env)
{
	int i;
	int count;
	env[i_key] = NULL;
	i = i_key;
	count = i_key + 1;

	while (env[i + 1])
	{
		env[i] = ft_strdup(env[i + 1], ft_strlen(env[i + 1]));
		i++;
		count++;
	}
	env = realloc_env(count - 1, env);
	return (env);
}

void free_env(char **env_copy)
{
	int i;
	i = 0;
	while (i < env_len(env_copy))
		free(env_copy[i]);
	free(env_copy);
}