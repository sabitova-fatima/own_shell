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
		new[j - 1] = 'E';
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
	int j;

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
		*new = join_char(*new, 'Q');
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
void	to_low(char *s)
{
	int i;

	if (!s)
		return ;
	i = -1;
	while(s[++i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
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
	while(s[++i] && data->fd_read != -1)
	{
		new = (char *)malloc(1);
		new[0] = '\0';
		s[i] = cleaner_semicolon_pipe_space(s[i]);
		j = main_cleaning(s[i], &new, env, data);
		clean_filename(i, data, &new);
		if ((s[i][j] == '>' || s[i][j] == '<') && !s[i][j + 1])
			next_redirect(s[i + 1], env, data, s[i][j]);
		else if ((s[i][j] == '>' || s[i][j] == '<') && (s[i][j + 1] == '>' \
			|| s[i][j + 1] == '<') && !s[i][j + 2])
			next_redirect(s[i + 1], env, data, s[i][j + 1] + 1);
		if (new[0] == '\0' && data->type > 0 && data->fd_read != -1)
			new = join_char(new, 'R');
		free(s[i]);
		s[i] = new;
	}
	if (data->fd_read == -1 && !ft_strcmp(s[i-1], ""))
		s[i - 1] = data->filename;
	else if (data->fd_read == -1 && !s[i+1])
		s[i] = cleaner_semicolon_pipe_space(s[i]);
	else if (data->fd_read == -1 && i == 1)
	{
		s[0] = ft_strjoin(s[0], "0");
		s[0] = ft_strjoin(s[0], data->filename);
	}
	set_data(data, fd, i, help);
	free(data);
}
