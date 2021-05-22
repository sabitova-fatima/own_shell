#include "minishell.h"

int into_check_empty_redirect(char *s, int j)
{
	if (s[j] == '\\' && s[j+1])
		j++;
	if (s[j] == '>' || s[j] == '<')
	{
		j++;
		if (s[j] == '>')
			j++;
		skip_spaces(s, &j);
		if (!s[j] || (s[j] == '\\' && !s[j+1]) ||
			s[j] == '>' || s[j] == '<')
		{
			printf("syntax error near > or <\n");
			return (-1);
		}
	}
	return (j);
}

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
			if (arr[i][j] != '"' && arr[i][j] != '\'')
			{
				j = into_check_empty_redirect(arr[i], j);
				if (j == -1)
					return (1);
			}
			if (arr[i][j] == '"' || arr[i][j] == '\'')
				j = into_quotes(arr[i], j);
			if (!arr[i][j])
				break;
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
	int *help2;
	int help3;

	i = -1;
	new = split_spaces(array, &help3, &help2);
	if (!new)
		return (1);
	while (new[++i])
	{
		if (pre_cleaner(new[i]))
		{
			printf("not closed quotes\n");
			return (1);
		}
	}
//	freedom_3d(new);
	return (0);
}

int pre_parser(char **arr)
{
	char ***new;
	int i;

	new = split_pipes(arr);
	if (!new)
		return (1);
	i = -1;
	while(new[++i])
	{
		check_empty_redirect(new[i]);
		check_empty_commands(new[i]);
//		if (check_empty_redirect(new[i]) || check_empty_commands(new[i])
//		|| check_opened_quotes(new[i]))
//			return (1);
	}
	freedom_3d(new);
	return (0);
}
