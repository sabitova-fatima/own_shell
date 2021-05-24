#include "minishell.h"

char	*cleaner_semicolon_pipe_space(char *s)
{
	char	*new;
	int		j;

	new = (char *)malloc(1);
	new[0] = '\0';
	j = 0;
	skip_spaces(s, &j);
	while (s[j])
	{
		new = join_char(new, s[j]);
		if (!new)
			return (NULL);
		j++;
	}
	j = 0;
	while (new[j])
		j++;
	if (j >= 2 && (new[j - 1] == ';' || new[j - 1] == '|') && \
		new[j - 2] != '\\')
		new[j - 1] = '\0';
	if (j < 2 && (new[j - 1] == ';' || new[j - 1] == '|'))
		new[j - 1] = 6;
	free(s);
	return (new);
}

int	into_quotes_cleaner(char *s, int *j, char **new, char **env)
{
	char	q;

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
		if (s[*j] == '\\' && q == '"' && \
			(s[(*j) + 1] == '\\' || s[(*j) + 1] == '"'))
			(*j)++;
		if (s[*j] == q && s[(*j) - 1] != '\\')
			break ;
		*new = join_char(*new, s[(*j)++]);
	}
	return (++(*j));
}

int	cleaner_other(char *s, int j, char **new, char **env)
{
	while (s[j] != '"' && s[j] != '\'' && s[j])
	{
		if (s[j] == '\\' && s[j + 1])
			j++;
		j = into_dollar(s, new, &j, env);
		if (!s[j])
			break ;
		if (s[j] == '\\' && s[j + 1])
			j++;
		if ((s[j] == '"' || s[j] == '\'') && s[j - 1] != '\\')
			break ;
		if (s[j] == '>' || s[j] == '<')
			break ;
		*new = join_char(*new, s[j++]);
	}
	if (s[j] == '"' || s[j] == '\'')
		j = into_quotes_cleaner(s, &j, new, env);
	return (j);
}

int	main_cleaning(char *s, char **new, char **env, int *help_var)
{
	int	j;

	j = 0;
	while (s[j] && s[j] != '>' && s[j] != '<')
		j = cleaner_other(s, j, new, env);
	if (((s[j] == '>' || s[j] == '<') && s[j + 1] && s[j + 1] != '>')
		|| (s[j] == '>' && s[j + 1] == '>' && s[j + 2]))
		j = current_redirect(s, j + 1, env, help_var);
	return (j);
}

void	cleaner(char **s, int *w_h, char **env, int *****fd)
{
	int		i;
	int		j;
	char	*new;
	int		help_var[4];

	i = -1;
	set_helpvar(help_var, fd, i, w_h);
	while (s[++i])
	{
		new = (char *)malloc(1);
		new[0] = '\0';
//		printf("[%s]", s[i]);
		s[i] = cleaner_semicolon_pipe_space(s[i]);
//		printf(" --- [%s]", s[i]);
		j = main_cleaning(s[i], &new, env, help_var);
		clean_filename(i, help_var, &new);
		if ((s[i][j] == '>' || s[i][j] == '<') && !s[i][j + 1])
			next_redirect(s[i + 1], env, help_var, s[i][j]);
		if (s[i][j] == '>' && s[i][j + 1] == '>' && !s[i][j + 2])
			next_redirect(s[i + 1], env, help_var, 5);
		free(s[i]);
		s[i] = new;
//		printf(" >>> [%s]\n", s[i]);
	}
	set_helpvar(help_var, fd, i, w_h);
}
