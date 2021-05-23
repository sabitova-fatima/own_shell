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

void into_redirect(char *s, int i, int j, int w, int h, int *****fd, char **env)
{
	int fd_new;
	char *new;

	while(s[j])
	{
		new = (char *)malloc(1);
		new[0] = '\0';
		j = cleaner_other(s, j, &new, env);
		printf("redir [%s]\n", new);
		fd_new = open(new, O_RDWR | O_CREAT | O_TRUNC, 0666);
		free(new);
		printf("%d\n", fd_new);
		if (!s[j++])
			break;
	}
	(*fd)[w][h][i][1] = fd_new;
	printf("final fd %d\n", (*fd)[w][h][i][1] );

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
		if (s[j] == '>' || s[j] == '<')
			break;
		*new = join_char(*new, s[j++]);
	}
	if (s[j] == '"' || s[j] == '\'')
		j = into_quotes_cleaner(s, &j, new, env);
	return (j);
}

int cleaner(char **s, int w, int h, char **env, int *****fd)
{
	int i;
	int j;
	char *new;

	i = -1;
	while(s[++i])
	{
		new = (char *)malloc(1);
		new[0] = '\0';
		printf("[%s]", s[i]);
		j = 0;
		skip_spaces(s[i], &j);
		s[i] = cleaner_semicolon_pipe_space(s[i], j);
		printf(" --- [%s]", s[i]);
		j = 0;
		while(s[i][j] && s[i][j] != '>' && s[i][j] != '<')
			j = cleaner_other(s[i], j, &new, env);
		if (s[i][j] == '>')
			into_redirect(s[i], i, j+1, w, h, fd, env);
		printf(" >>> [%s]\n", new);
		free(s[i]);
		s[i] = new;
	}
	return (0);
}

