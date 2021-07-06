#include "minishell.h"

int	ft_strncmp_env(char *s1, char *s2, int *j)
{
	int	i;
	int	len;

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

char	*search_env(char *dollar, char **env)
{
	int		i;
	int		j;
	char	*env_print;

	env_print = "";
	i = -1;
	while (env[++i])
	{
		j = 0;
		if (!ft_strncmp_env(env[i], dollar, &j))
			env_print = env[i] + j + 1;
	}
	return (env_print);
}

int	into_dollar2(char *s, int j, char **new, char **env)
{
	char	*dollar;

	if (s[j] == '$' && s[j + 1] && s[j + 1] != '$')
	{
		j++;
		dollar = (char *)malloc(1);
		dollar[0] = '\0';
		while (s[j] != '$' && s[j] && s[j] != '"' && s[j] != '\'')
			dollar = join_char(dollar, s[j++]);
		*new = ft_strjoin(*new, search_env(dollar, env));
		free(dollar);
	}
	return (j);
}

void	ft_putnbr(int n, char **new)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10, new);
		ft_putnbr(n % 10, new);
	}
	else
		*new = join_char(*new, '0' + n);
}

int	into_dollar(char *s, char **new, t_data *data, char **env)
{
	int j;

	j = data->j;
	while (s[j] == '$')
	{
		if (!s[j + 1])
			*new = join_char(*new, s[j++]);
		if (s[j] == '$' && s[j + 1] == '?')
			ft_putnbr(data->error, new);
		if (s[j] == '$' && s[j + 1] == '$')
			*new = join_char(*new, s[j++]);
		j = into_dollar2(s, j, new, env);
	}
	return (j);
}
