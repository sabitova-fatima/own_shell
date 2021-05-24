#include "minishell.h"

int	into_quotes(char *s, int i)
{
	char	q;

	q = s[i++];
	while (s[i] && s[i] != q)
	{
		if (s[i] == '\\' && q == '"' && (s[i + 1] == '"' || s[i + 1] == '\\'))
			i++;
		i++;
	}
	return (i);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	count_spaces_help(char *s, int i, int *w_count, char *c)
{
	if (s[i] != c[0] && s[i] != c[1] && s[i] != '"' && s[i] != '\'' && \
		(s[i + 1] == c[0] || s[i + 1] == c[1] || !s[i + 1]))
		(*w_count)++;
	else if (s[i] == '\\' && s[i + 1])
	{
		if (!s[i + 2] || s[i + 2] == c[0] || s[i + 2] == c[1])
			(*w_count)++;
		i++;
	}
	else if (s[i] == '"' || s[i] == '\'')
	{
		i = into_quotes(s, i);
		if ((s[i] && (s[i + 1] == c[0] || s[i + 1] == c[1] || !s[i + 1]))
			|| !s[i])
			(*w_count)++;
	}
	return (i);
}
