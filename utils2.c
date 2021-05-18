#include "minishell.h"

char	*ft_strjoin_char(char *s1, char c)
{
	char	*new;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	if (!(new = (char*)malloc((i + 1) + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	return (new);
}

int	ft_strncmp_env(char *s1, char *s2, int n, int *j)
{
	int			i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
		(*j)++;
	}
	if (s1[i] != '=')
		return (1);
	return (0);
}

char *search_env(char *dollar, char **env)
{
	int i;
	int len;
	int j;
	char *env_print;

	i = -1;
	env_print = "";
	len = ft_strlen(dollar);
	while (env[++i])
	{
		j = 0;
		if (!ft_strncmp_env(env[i], dollar, len, &j))
			env_print = env[i] + j + 1;
	}
	return (env_print);
}

int into_dollar2(char *s, int *j, char **new, char **env)
{
	char *dollar;
	char *tmp;

	while (s[*j] == '$' && s[(*j)+1] != '\\' && s[(*j) + 1] &&
		   s[(*j) + 1] != '$')
	{
		if (s[*j] == '$' && s[(*j) + 1] == '?')
		{
			*new = join_char(*new, s[(*j)++]);
			return (*j);
		}
		(*j)++;
		dollar = "";
		while (s[*j] != '$' && s[*j] != '\\' && s[*j] && s[*j] != '"'
			   && s[*j] != '\'')
			dollar = join_char(dollar, s[(*j)++]);
		tmp = *new;
		*new = ft_strjoin(*new, search_env(dollar, env));
		if (ft_strlen(tmp))
			free(tmp);
	}
	return (*j);
}

int into_dollar(char *s, char **new, int *j, char **env)
{
	while (s[*j] == '$')
	{
		if (!s[(*j) + 1] || s[(*j) + 1] == '"')
		{
			*new = join_char(*new, s[*j]);
			return ((*j) + 1);
		}
		if (s[*j] == '$' && s[(*j) + 1] == '?')
			*new = join_char(*new, s[(*j)++]);
		if (s[*j] == '$' && s[(*j)+1] == '$')
			(*j) += 2;
		*j = into_dollar2(s, j, new, env);
		if (s[*j] == '$' && s[(*j)+1] == '$')
			(*j) += 2;
		if (s[*j] == '$' && s[(*j)+1] == '\\')
			*new = join_char(*new, s[(*j)++]);
	}
	return (*j);
}

