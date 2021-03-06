#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

int	my_exit (void)
{
	exit(0);
}

int	is_in_list(char *command)
{
	if (!ft_strcmp ("echo", command) || !ft_strcmp("pwd", command) || \
	!ft_strcmp("env", command) || !ft_strcmp("cd", command) || \
	!ft_strcmp("exit", command) || !ft_strcmp("export", command) || \
	!ft_strcmp("unset", command))
		return (1);
	return (0);
}

int	find_end_name(char *name)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
			return (i);
		i++;
	}
	return (i);
}
