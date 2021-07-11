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
	char 	*old_new;

	old_new = *new;
	if (s[j] == '$' && s[j + 1] && s[j + 1] != '$')
	{
		j++;
		dollar = (char *)malloc(1);
		dollar[0] = '\0';
		while (s[j] != '$' && s[j] && s[j] != '"' && s[j] != '\'')
			dollar = join_char(dollar, s[j++]);
		*new = ft_strjoin(*new, search_env(dollar, env));
		free(old_new);
		free(dollar);
	}
	return (j);
}

int	ft_znak(int r)
{
	if (r < 0)
		return (-r);
	return(r);
}

char		*ft_itoa(int n)
{
	char	a[11];
	char	*itog;
	int		i;
	int		j;

	i = 0;
	if (n == 0)
		a[i++] = '0';
	j = (n < 0);
	while (n != 0)
	{
		a[i++] = '0' + (char)(ft_znak(n % 10));
		n /= 10;
	}
	itog = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!itog)
		return (NULL);
	if (j == 1)
		itog[0] = '-';
	while (i > 0)
		itog[j++] = a[--i];
	itog[j] = '\0';
	return (itog);
}


int	into_dollar(char *s, char **new, t_data *data, char **env)
{
	int	j;

	j = data->j;
	while (s[j] == '$')
	{
		if (!s[j + 1])
			*new = join_char(*new, s[j++]);
		if (s[j] == '$' && s[j + 1] == '?')
		{
			free(*new);
			*new = ft_itoa(global.error_status);
			global.error_status = 0;
		}
		if (s[j] == '$' && s[j + 1] == '$')
			*new = join_char(*new, s[j++]);
		j = into_dollar2(s, j, new, env);
	}
	return (j);
}
