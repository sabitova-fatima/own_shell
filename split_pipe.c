#include "minishell.h"

int into_command_split_pipe(char *s, int *i, int p_count, char c)
{
	if (s[*i] == '|')
		p_count++;
	else if (s[*i] == '\\' && s[(*i) + 1])
		(*i)++;
	else if (s[*i] == '"' || s[*i] == '\'')
		*i = into_quotes(s, *i);
	return (p_count);
}

int into_command_split2_pipe(char *s, int letter, char c)
{
	char q;

	if (s[letter] != '"' && s[letter] != '\'')
	{
		while (s[letter] != c && s[letter] &&
			   s[letter] != '"' && s[letter] != '\'')
		{
			if (s[letter] == '\\' && s[letter + 1])
				letter++;
			letter++;
		}
	}
	if (s[letter] == '"' || s[letter] == '\'')
	{
		q = s[letter];
		letter = into_quotes(s, letter);
		if (s[letter] == q)
			letter++;
	}
	return (letter);
}

char	**ft_split2_pipe(char *s, int p_count, char c, char **arr)
{
	int i;
	int j;
	int letter;

	i = -1;
	while (++i < p_count)
	{
		letter = 0;
		j = 0;
		skip_spaces(s, &letter);
		while (s[letter] && s[letter] != c)
			letter = into_command_split2_pipe(s, letter, c);
		arr[i] = (char *)malloc(sizeof(char) * (letter + 1));
		if (!arr[i])
		{
			freedom(arr, i);
			return (NULL);
		}
		while (j < letter)
			arr[i][j++] = *s++;
		if (*s == '|')
			arr[i][j++] = *s++;
		arr[i][j] = '\0';
//		printf("word <%s>\n", arr[i]);
	}
	arr[i] = NULL;
	return (arr);
}

char		**ft_split_pipe(char *s, char c)
{
	char	**arr;
	int		p_count;
	int		i;

	i = -1;
	p_count = 0;
	if (!s)
		return (NULL);
	while (s[++i])
		p_count = into_command_split_pipe(s, &i, p_count, c);
//	printf("pipes in command: %d\n", p_count);
	arr = (char **)malloc(sizeof(char *) * (p_count + 1 + 1));
	if (!arr)
		return (NULL);
	arr = ft_split2_pipe(s, p_count + 1, '|', arr);
	return (arr);
}