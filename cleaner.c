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
	if (j >= 2 && new[j - 1] == '|' && new[j - 2] != '\\')
		new[j - 1] = '\0';
	if (j < 2 && new[j - 1] == '|')
		new[j - 1] = 5;
	free(s);
	return (new);
}

int	into_quotes_cleaner(char *s, int j, char **new)
{
	char	q;

	q = s[j++];
	if (s[j] == q)
	{
		*new = join_char(*new, '\0');
		return (++j);
	}
	while (s[j] != q && s[j])
	{
		if (s[j] == '\\' && q == '"' && (s[j + 1] == '\\' || \
			s[j + 1] == '"'))
			j++;
		if (s[j] == q && s[j - 1] != '\\')
			break ;
		*new = join_char(*new, s[j++]);
	}
	return (++j);
}

int	cleaner_other(char *s, t_data *data, char **new, char **env)
{
	int	j;

	j = data->j;
	while (s[j] != '"' && s[j] != '\'' && s[j])
	{
		data->j = j;
		j = into_dollar(s, new, data, env);
		if (!s[j] || s[j] == '"' || s[j] == '\'')
			break ;
		if (s[j] == '<' || s[j] == '>')
			break ;
		*new = join_char(*new, s[j++]);
	}
	if (s[j] == '"' || s[j] == '\'')
		j = into_quotes_cleaner(s, j, new);
	return (j);
}

int	main_cleaning(char *s, char **new, char **env, t_data *data)
{
	int	j;

	j = 0;
	skip_spaces(s, &j);
	if (((s[j] == '<' || s[j] == '>') && !s[j + 1]) || \
		((s[j] == '<' || s[j] == '>') && (s[j + 1] == '<' || \
		s[j + 1] == '>') && !s[j + 2]))
		*new = join_char(*new, 5);
	while (s[j] && s[j] != '>' && s[j] != '<')
	{
		data->j = j;
		j = cleaner_other(s, data, new, env);
	}
	if (((s[j] == '>' || s[j] == '<') && s[j + 1] && s[j + 1] != '>' && \
		s[j + 1] != '<') || (s[j] == '>' && s[j + 1] == '>' && s[j + 2]) || \
		(s[j] == '<' && s[j + 1] == '<' && s[j + 2]))
		j = current_redirect(s, j + 1, env, data);
	return (j);
}

void	cleaner(char **s, t_help *help, char **env, int ****fd)
{
	int		i;
	int		j;
	char	*new;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	i = -1;
	set_data(data, fd, i, help);
	if (s[0] && s[0][0] != '"' && s[0][0] != '\'' && s[0][0] != '$')
		to_low(s[0]);
	while (s[++i] && data->fd_read != -1)
	{
		new = init_empty();
		s[i] = cleaner_semicolon_pipe_space(s[i]);
		j = main_cleaning(s[i], &new, env, data);
		clean_filename(i, data, &new);
		if ((s[i][j] == '>' || s[i][j] == '<') && !s[i][j + 1])
			next_redirect(s[i + 1], env, data, s[i][j]);
		else if ((s[i][j] == '>' || s[i][j] == '<') && (s[i][j + 1] == '>' \
			|| s[i][j + 1] == '<') && !s[i][j + 2])
			next_redirect(s[i + 1], env, data, s[i][j + 1] + 1);
		s[i] = cleaner_help(new, data, s[i]);
	}
	set_data(data, fd, i, help);
	free(data);
}
