#include "minishell.h"

int into_quotes(char *s, int i)
{
	char q;

	q = s[i++];
	while (s[i] && s[i] != q)
	{
		if (s[i] == '\\' && q == '"' &&
			(s[i+1] == '"' || s[i+1] == '\\'))
			i++;
		i++;
	}
	return (i);
}

int into_command_semicolon(char *s, int i)
{
	while (s[++i] && s[i] != ';')
	{
		if (s[i] == '\\' && s[i + 1])
			i++;
		else if (s[i] == '\'' || s[i] == '"')
			i = into_quotes(s, i);
	}
	if (s[i] == ';')
		i++;
	return (i);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
}

char *join_char(char *s, char c)
{
	char *tmp;
	char *new;

	tmp = s;
	new = ft_strjoin_char(s, c);
	if (ft_strlen(tmp))
		free(tmp);
	return (new);

}

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}