#include "minishell.h"

int check_empty_redirect(char **arr)
{
	int i;
	int j;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while(arr[i][++j])
		{
			while (arr[i][j] != '"' && arr[i][j] != '\'' && arr[i][j])
			{
				j = into_check_empty_redirect(arr, i, j);
				if (j == -1)
					return(1);
			}
			if (arr[i][j] == '"' || arr[i][j] == '\'')
				j = into_quotes(arr[i], j) + 1;
		}
	}

	return (0);
}

int check_empty_commands(char **arr)
{
	int i;
	int j;

	i = -1;
	while(arr[++i])
	{
		j = 0;
		skip_spaces(arr[i], &j);
		if (arr[i][j] == ';' || arr[i][j] == '|' || !arr[i][j])
		{
			printf("syntax error near ; or |\n");
			return (1);
		}
	}

	return (0);
}

int check_opened_quotes(char **array)
{
	char ***new;
	int i;

	i = -1;
	new = split_spaces_pre(array);
	while (new[++i])
	{
		if (pre_cleaner(new[i]))
		{
			printf("not closed quotes\n");
			return (1);
		}
	}

	return (0);
}

int pre_cleaner(char **s)
{
	int i;
	int j;
	char *new;
	int quotes;

	i = -1;
	while(s[++i])
	{
		new = "";
		quotes = 0;
		s[i] = cleaner_semicolon_pipe(s[i]);
		j = 0;
		skip_spaces(s[i], &j);
		while(s[i][j])
			j = into_pre_cleaner(s[i], j, &new, &quotes) + 1;
		if (quotes)
			return (1);
		free(s[i]);
		s[i] = new;
	}
	return (0);
}

int pre_parser(char **arr)
{
	char ***new;
	int i;

	new = split_pipes(arr);
	i = -1;
	while(new[++i])
	{

		if (check_empty_redirect(new[i]) || check_empty_commands(new[i])
		|| check_opened_quotes(new[i]))
			return (1);
	}

	return (0);
}

