#include "minishell.h"

char *cleaner_semicolon_pipe(char *s)
{
	int i;
	char *new;

	new = "";
	i = -1;
	while(s[++i])
	{
		new = join_char(new, s[i]);
		if (!new)
			return (NULL);
	}
	i = 0;
	while(new[i])
		i++;
	if ((new[i-1] == ';' || new[i-1] == '|') && new[i-2] != '\\')
		new[i-1] = '\0';
	free(s);
	return (new);

}

int into_quotes_cleaner(char *s, int *j, char **new, char **env)
{
	char q;

	q = s[(*j)++];
	while (s[*j] != q && s[*j])
	{
		if (q == '"')
			*j = into_dollar(s, new, j, env);
		if (s[*j] == '\\' && q == '"' &&
			(s[(*j)+1] == '\\' || s[(*j)+1] == '"'))
			(*j)++;
		if (s[*j] == q && s[(*j) - 1] != '\\')
			break;
		*new = join_char(*new, s[(*j)++]);
	}
	return (*j);
}

int into_redirect(char **s, int i, int j, char **new)
{
	int fd;

	fd = open(s[i+1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (!fd)
		return (-1);
//	j++;

	return (j);
}

int into_cleaner(char **s, int i, int j, char **new, char **env)
{
	while (s[i][j] != '"' && s[i][j] != '\'' && s[i][j])
	{
		if (s[i][j] == '\\' && s[i][j + 1])
			j++;
		j = into_dollar(s[i], new, &j, env);
		if (s[i][j] == '\\' && s[i][j+1])
			j++;
		if ((s[i][j] == '"' || s[i][j] == '\'') && s[i][j-1]!='\\')
			break;
		if (s[i][j] == '>' || s[i][j] == '<')
			j = into_redirect(s, i, j, new);
		*new = join_char(*new, s[i][j++]);
	}
	if (s[i][j] == '"' || s[i][j] == '\'')
		j = into_quotes_cleaner(s[i], &j, new, env);
	return (j);
}

int cleaner(char **s, char **env)
{
	int i;
	int j;
	char *new;

	i = -1;
	while(s[++i])
	{
		new = "";
		s[i] = cleaner_semicolon_pipe(s[i]);
		j = 0;
		skip_spaces(s[i], &j);
		while(s[i][j])
			j = into_cleaner(s, i, j, &new, env);
		free(s[i]);
		s[i] = new;
	}
	return (0);
}

