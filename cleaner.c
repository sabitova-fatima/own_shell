#include "minishell.h"

char *cleaner_semicolon_pipe_space(char *s, int j)
{
	char *new;

	new = (char *)malloc(1);
	new[0] = '\0';
	while(s[j])
	{
		new = join_char(new, s[j]);
		if (!new)
			return (NULL);
		j++;
	}
	j = 0;
	while(new[j])
		j++;
	if (j >= 2 && (new[j-1] == ';' || new[j-1] == '|') && new[j-2] != '\\')
		new[j-1] = '\0';
	if (j < 2 && (new[j-1] == ';' || new[j-1] == '|'))
		new[j-1] = 6;
	free(s);
	return (new);

}

int into_quotes_cleaner(char *s, int *j, char **new, char **env)
{
	char q;

	q = s[(*j)++];
	if (s[*j] == q)
	{
		*new = join_char(*new, '\0');
		return (++(*j));
	}
	while (s[*j] != q && s[*j])
	{
		if (q == '"')
			*j = into_dollar(s, new, j, env);
		if (s[*j] == '\\' && q == '"' &&
			(s[(*j) + 1] == '\\' || s[(*j) + 1] == '"'))
			(*j)++;
		if (s[*j] == q && s[(*j) - 1] != '\\')
			break;
		*new = join_char(*new, s[(*j)++]);
	}
	return (++(*j));
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

int cleaner_other(char *s, int j, char **new, char **env)
{
	while (s[j] != '"' && s[j] != '\'' && s[j])
	{
		if (s[j] == '\\' && s[j + 1])
			j++;
		j = into_dollar(s, new, &j, env);
		if (!s[j])
			break;
		if (s[j] == '\\' && s[j+1])
			j++;
		if ((s[j] == '"' || s[j] == '\'') && s[j-1] != '\\')
			break;
//		if (s[j] == '>' || s[j] == '<')
//			j = into_redirect(s, i, j, new);
		*new = join_char(*new, s[j++]);
	}
	if (s[j] == '"' || s[j] == '\'')
		j = into_quotes_cleaner(s, &j, new, env);
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
//		new = "";
		new = (char *)malloc(1);
		new[0] = '\0';
		printf("[%s]", s[i]);
		j = 0;
		skip_spaces(s[i], &j);
		s[i] = cleaner_semicolon_pipe_space(s[i], j);
		printf(" --- [%s]", s[i]);
		j = 0;
		while(s[i][j])
			j = cleaner_other(s[i], j, &new, env);
		printf(" >>> [%s]\n", new);
		free(s[i]);
		s[i] = new;
	}
	return (0);
}

