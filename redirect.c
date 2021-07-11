#include "minishell.h"

void	next_redirect(char *s, char **env, t_data *data, char sign)
{
	int		j;
	char	*filename;

	if (data->fd_read != -1)
	{
		data->type = sign;
		j = 0;
		skip_spaces(s, &j);
		filename = (char *) malloc(1);
		filename[0] = '\0';
		while (s[j] && s[j] != '>' && s[j] != '<')
		{
			data->j = j;
			j = cleaner_other(s, data, &filename, env);
		}
		open_close(data, filename);
		if (data->fd_read == -1)
		{
			write(2, "e-bash: ", ft_strlen("e-bash: "));
			write(2, filename, ft_strlen(filename));
			write(2, ": ", 2);
			perror("");
			global.read_trouble = 1;
		}
		free(filename);
		data->was_redirect = 1;
	}
}

int	current_redirect(char *s, int j, char **env, t_data *data)
{
	char	*filename;

	while (s[j] && data->fd_read != -1)
	{
		if ((s[j - 1] == '>' || s[j - 1] == '<') && s[j] != '>' && s[j] != '<')
			data->type = (int)s[j - 1];
		if (s[j - 1] == '>' && s[j] == '>')
			data->type = (int)(s[j++] + 1);
		if (s[j - 1] == '<' && s[j] == '<')
			data->type = (int)(s[j++] + 1);
		if (!s[j])
			break ;
		filename = (char *)malloc(1);
		filename[0] = '\0';
		while (s[j] && s[j] != '>' && s[j] != '<')
		{
			data->j = j;
			j = cleaner_other(s, data, &filename, env);
		}
		open_close(data, filename);
		if (data->fd_read == -1)
		{
			write(2, "e-bash: ", ft_strlen("e-bash: "));
			write(2, filename, ft_strlen(filename));
			write(2, ": ", 2);
			perror("");
			global.read_trouble = 1;
		}
		free(filename);
		if (!s[j++])
			break ;
	}
	return (j - 1);
}

void	clean_filename(int i, t_data *data, char **new)
{
	if (i == 0)
		return ;
	if (!data->was_redirect)
		return ;
	free(*new);
	*new = (char *)malloc(1);
	*new[0] = '\0';
	data->was_redirect = 0;
}

void	set_data(t_data *data, int ****fd, int i, t_help *help)
{
	if (i == -1)
	{
		data->fd_read = -5;
		data->fd_write = -5;
		data->was_redirect = 0;
		data->type = 0;
		data->error = help->error;
	}
	else
	{
		if (data->fd_read != -5)
			(*fd)[help->help][i - 1][0] = data->fd_read;
		if (data->fd_write != -5)
			(*fd)[help->help][i - 1][1] = data->fd_write;
		help->error = data->error;
	}
}

void	open_close(t_data *data, char *filename)
{
	if (data->type == (int)('>'))
	{
		if (data->fd_write != -5)
			close(data->fd_write);
		data->fd_write = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	if (data->type == (int)('<'))
	{
		if (data->fd_read != -5)
			close(data->fd_read);
		data->fd_read = open(filename, O_RDONLY, 0666);
	}
	if (data->type == (int)('>' + 1)) // >>
	{
		if (data->fd_write != -5)
			close(data->fd_write);
		data->fd_write = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	if (data->type == (int)('<' + 1)) // <<
	{
		heredoc(filename);
		if (data->fd_read != -5)
			close(data->fd_read);
		data->fd_read = open(".temp.txt", O_RDONLY, 0666);
	}
}
