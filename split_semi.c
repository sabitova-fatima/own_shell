#include "minishell.h"

int w_count(char *s)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == ';' || (s[i] && !s[i+1]))
			count++;
		else if (s[i] == '\\' && s[i++ + 1])
		{
			if (!s[i + 1])
				count++;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			i = into_quotes(s, i);
			if (s[i] && !s[i + 1] || !s[i])
				count++;
		}
		if (!s[i])
			break;
	}
	return (count);
}

int into_semicolon(char *s, int i)
{
	while (s[++i] && s[i] != ';')
	{
		if (s[i] == '\\' && s[i + 1])
			i++;
		else if (s[i] == '\'' || s[i] == '"')
			i = into_quotes(s, i);
		if (!s[i])
			break;
	}
	if (s[i] == ';')
		i++;
	return (i);
}

char **split_semicolon(char *s)
{
	int count;
	char **arr;
	int i;
	int j;

	count = w_count(s);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		j = into_semicolon(s, -1);
		arr[i] = ft_strdup(s, j);
		if (!arr[i])
		{
			freedom_2d(arr);
			return (NULL);
		}
		s += j;
	}
	arr[i] = NULL;
	return (arr);
}