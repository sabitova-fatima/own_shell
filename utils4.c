#include "minishell.h"

char ***split_spaces_pre(char **arr)
{
	char ***new;
	int i;
	char c[2];

	i = 0;
	while (arr[i])
		i++;
	c[0] = ' ';
	c[1] = '	';
	new = (char ***)malloc(sizeof(char **) * (i + 1));
	i = -1;
	while (arr[++i])
	{
//		printf("before split <%s>\n", arr[i]);
		new[i] = ft_split_pre(arr[i], c);
		if (!new[i])
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}

int w_count(char *s)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == ';')
			count++;
		else if (s[i] && !s[i+1])
			count++;
		else if (s[i] == '\\' && s[i + 1])
		{
			if (!s[i + 2])
				count++;
			i++;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			i = into_quotes(s, i);
			if (!s[i+1])
				count++;
		}
	}
	return (count);
}
