#include "minishell.h"

int	into_check_empty_redirect(char *s, int j)
{
	char	q;

	if (s[j] == '>' || s[j] == '<')
	{
		q = s[j++];
		if (s[j] == q)
			j++;
		skip_spaces(s, &j);
		if (!s[j] || s[j] == '>' || s[j] == '<')
		{
			printf("syntax error near > or <\n");
			return (-1);
		}
	}
	return (j);
}

int	check_empty_redirect(char **arr)
{
	int	i;
	int	j;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] != '"' && arr[i][j] != '\'')
			{
				j = into_check_empty_redirect(arr[i], j);
				if (j == -1)
					return (1);
			}
			if (arr[i][j] == '"' || arr[i][j] == '\'')
				j = into_quotes(arr[i], j);
			if (!arr[i][j])
				break ;
		}
	}
	return (0);
}

int	check_empty_commands(char **arr)
{
	int	i;
	int	j;

	i = -1;
	while (arr[++i])
	{
		j = 0;
		skip_spaces(arr[i], &j);
		if (arr[i][j] == '|' || (!arr[i][j] && i > 0))
		{
			printf("syntax error near |\n");
			return (1);
		}
	}
	return (0);
}

int	check_opened_quotes(char **array)
{
	char	***new;
	int		i;
	int		***fd;

	i = 0;
	while (array[i])
		i++;
	fd = (int ***)malloc(sizeof(int **) * (i + 1));
	new = split_spaces(array, fd);
	if (!new)
		return (1);
	i = -1;
	while (new[++i])
	{
		if (pre_cleaner(new[i]))
		{
			printf("not closed quotes\n");
			freedom_3d(new);
			freedom_3d_int(fd);
			return (1);
		}
	}
	freedom_3d(new);
	freedom_3d_int(fd);
	return (0);
}

int	pre_parser(char *s)
{
	char	**new;

	new = split_pipes(s);
	if (!new)
		return (1);
	if (check_opened_quotes(new) || check_empty_commands(new) || \
		check_empty_redirect(new))
	{
		freedom_2d(new);
		return (1);
	}
	freedom_2d(new);
	return (0);
}
