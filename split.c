#include "minishell.h"

int into_command_split(char *s, int *i, int w_count, char *c)
{
	if (s[*i] != c[0] && s[*i] != c[1] && s[*i] != '"' && s[*i] != '\'' &&
		(s[(*i) + 1] == c[0] || s[(*i) + 1] == c[1] || !s[(*i) + 1]))
		w_count++;
	else if (s[*i] == '\\' && s[(*i) + 1])
	{
		if (!s[(*i) + 2] || s[(*i) + 2] == c[0] || s[(*i) + 2] == c[1])
			w_count++;
		(*i)++;
	}
	else if (s[*i] == '"' || s[*i] == '\'')
	{
		*i = into_quotes(s, *i);
		if (s[(*i) + 1] == c[0] || s[(*i) + 1] == c[1] || !s[(*i) + 1])
			w_count++;
	}
	return (w_count);
}

int into_command_split2(char *s, int letter, char *c)
{
	char q;

	if (s[letter] != '"' && s[letter] != '\'')
	{
		while (s[letter] != c[0] && s[letter] != c[1] && s[letter] &&
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

void	freedom(char **arr, int w_count)
{
	int	i;

	i = 0;
	while (i < w_count)
		free(arr[i++]);
	free(arr);
}

char	**ft_split2(char *s, int w_count, char *c, char **arr)
{
	int		i;
	int		j;
	int		letter;

	i = -1;
	while (++i < w_count)
	{
		letter = 0;
		j = 0;
		skip_spaces(s, &letter);
		while (s[letter] && s[letter] != c[0] && s[letter] != c[1])
			letter = into_command_split2(s, letter, c);
		arr[i] = (char *)malloc(sizeof(char) * (letter + 1));
		if (!arr[i])
		{
			freedom(arr, i);
			return (NULL);
		}
		while (j < letter)
			arr[i][j++] = *s++;
		arr[i][j] = '\0';
//		printf("word |%s|\n", arr[i]);
	}
	arr[i] = NULL;
	return (arr);
}

char		**ft_split(char *s, char *c, int *help2)
{
	char	**arr;
	int		w_count;
	int		i;

	i = -1;
	w_count = 0;
	if (!s)
		return (NULL);
	while (s[++i])
		w_count = into_command_split(s, &i, w_count, c);
//	printf("words in command: %d\n", w_count);
	*help2 = w_count;
	arr = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (!arr)
		return (NULL);
	arr = ft_split2(s, w_count, c, arr);
	return (arr);
}


