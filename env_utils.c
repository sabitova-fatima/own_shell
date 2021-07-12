#include "minishell.h"

int	where_to_put_env(char *name, char **env_copy)
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
	int		n_var;
	char	*right_side;
	char	*right_side2;
	char *fuck;

	right_side2 = (char *)malloc(1);
	if (key[0] >= 'A' && key[0] <= 'Z' | key[0] >= 'a' && key[0] <= 'z')
	{
//		right_side = "";
		if (value[0])
		{
			printf("HERE\n");
			right_side = ft_strjoin("=\"", value);
			fuck = right_side2;
			right_side2 = ft_strjoin(right_side, "\"");
			free(fuck);
			if (right_side)
				free(right_side);
		}
		n_var = where_to_put_env(key, env_copy);
		if (env_copy[n_var]) /* если переменная уже есть */
			free(env_copy[n_var]);
		else /* если переменной еще нет */
			env_copy = realloc_env(n_var + 1, env_copy);
		env_copy[n_var] = ft_strjoin(key, right_side2);
		printf("and?\n");
		if (right_side2)
		{
			printf("OIOIOIOIOI\n");
			free(right_side2);
		}
	}
	else
	{
		printf("export: not an identifier: %s\n", key);
		g_global.error_status = 1;
	}
	free(key);
	free(value);
	return (env_copy);
}

// int key_checker(char **key)
// {
// 	if (key[0] >= 'A' && key[0] <= 'Z' | key[0] >= 'a' && key[0] <= 'z')
// }

char	**my_unset(char **env, char **command, int *result)
{
	int		i;
	int		i_key;
	char **env_new;
	i = 0;
	if (!command[1])
		printf("Too few arguments\n");
	else
	{
		while (command[++i])
		{
			i_key = where_to_put_env(command[i], env);
//			printf("%d\n", i_key);
//			printf("%s\n", env[i_key]);
			if (env[i_key])
				env_new = unset_env(i_key, env);
		}
	}
	*result = 1;
	return (env_new);
}

char	**unset_env(int i_key, char **env)
{
	int		i;
	int		count;

	i = i_key;
	count = i_key + 1;
	printf("count %d\n", count);
	while (env[i + 1])
	{
		free(env[i]);
		env[i] = ft_strdup(env[i + 1], ft_strlen(env[i + 1]));
		i++;
		count++;
	}
	free(env[i]);
	printf("count after %d\n", count);
//	env = realloc_env(count - 1, env);
	return (env);
}

void free_env(char **env_copy)
{
	int		i;

	i = 0;
	while (i < env_len(env_copy))
		free(env_copy[i]);
	free(env_copy);
}
