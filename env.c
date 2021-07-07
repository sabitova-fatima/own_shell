#include "minishell.h"

int   env_len(char **env)
{
	int len;
    
	len = 0;
	while (env[len])
		len++;
	return (len - 1);
}

int		print_sorted_env(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*temp;
	char	**env_copy;

	env_copy = copy_env(env);
	temp = (char*)malloc(1000);
	len = env_len(env_copy);
	i = 0;
	while (i < len)
	{
	j = i + 1;

		while (j < len)
		{
			if (strcmp(env_copy[i], env_copy[j]) > 0)
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env_copy[i])
	printf("%s\n", env_copy[i++]);
	return (1);
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
		// free(env_copy[i]);
	}
	// free(env_copy);
	return (new_env);
}

int   find_end_name(char *name)
{
	int i;

	i = 0;
	while(name[i])
	{
		if(name[i] == '=')
			return(i);
		i++;
	}
	return(i);
}

int	ft_strncmp(char *s1, char *s2, int size)
{
	unsigned int i;

	if (size == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s2[i] != '\0' && i < size - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	if (i != size)
		return (s1[i] - s2[i]);
	return (0);
}

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

char **my_unset(char **env, char **command)
{
	int i ;
	int i_key;

	i = 1;
	if (!command[1])
		printf("Too few arguments");
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
	return (env);
}

char **unset_env(int i_key, char **env)
{
	int i;
	int count;

	// free(env[i_key]);
	env[i_key] = NULL;
	i = i_key;
	count = i_key + 1;

	while (env[i + 1])
	{
		env[i] = ft_strdup(env[i + 1], ft_strlen(env[i + 1]));
		// free(env[i + 1]);
		i++;
		count++;
	}
	env = realloc_env(count - 1, env);
	return (env);
}