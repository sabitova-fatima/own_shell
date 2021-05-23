#include "minishell.h"

int	ft_strncmp_env(char *s1, char *s2, int *j)
{
	int			i;
	int 		len;

	len = ft_strlen(s2);
	i = -1;
	while (++i < len && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		(*j)++;
	}
	if (s1[i] != '=')
		return (1);
	return (0);
}

char *search_env(char *dollar, char **env)
{
	int i;
	int j;
	char *env_print;

	i = -1;
	env_print = "";
	while (env[++i])
	{
		j = 0;
		if (!ft_strncmp_env(env[i], dollar, &j))
			env_print = env[i] + j + 1;
	}
	return (env_print);
}

int into_dollar2(char *s, int *j, char **new, char **env)
{
	char *dollar;
	char *tmp;

	if (s[*j] == '$' && s[(*j)+1] != '\\' && s[(*j) + 1] &&
		   s[(*j) + 1] != '$')
	{
		(*j)++;
		dollar = (char *)malloc(1);
		dollar[0] = '\0';
		while (s[*j] != '$' && s[*j] != '\\' && s[*j] && s[*j] != '"'
			   && s[*j] != '\'')
			dollar = join_char(dollar, s[(*j)++]);
		tmp = *new;
		*new = ft_strjoin(*new, search_env(dollar, env));
		free(tmp);
		free(dollar);
	}
	return (*j);
}

int into_dollar(char *s, char **new, int *j, char **env)
{
	if (*j > 0 && s[*j] == '$' && s[(*j) - 1] == '\\')
	{
		*new = join_char(*new, s[(*j)++]);
		return (*j);
	}
	while (s[*j] == '$')
	{
		if (!s[(*j) + 1])
		{
			*new = join_char(*new, s[(*j)++]);
			return (*j);
		}
		if (s[*j] == '$' && s[(*j) + 1] == '?')
			*new = join_char(*new, s[(*j)++]);
		if (s[*j] == '$' && s[(*j)+1] == '$')
			*new = join_char(*new, s[(*j)++]);
		*j = into_dollar2(s, j, new, env);
		if (s[*j] == '$' && s[(*j) + 1] == '\\')
			*new = join_char(*new, s[(*j)++]);
	}
	return (*j);
}

