#include "minishell.h"

int	count_pipe(char *s)
{
	int	i;
	int	p_count;

	i = -1;
	p_count = 1;
	while (s[++i])
	{
		if (s[i] == '|')
			p_count++;
		else if (s[i] == '"' || s[i] == '\'')
			i = into_quotes(s, i);
		if (!s[i])
			break ;
	}
	return (p_count);
}

int	count_letters_pipe(char *s)
{
	char	q;
	int		letter;

	letter = 0;
	skip_spaces(s, &letter);
	while (s[letter] && s[letter] != '|')
	{
		while (s[letter] != '"' && s[letter] != '\'' && s[letter] != '|' \
		       && s[letter])
			letter++;
		if (s[letter] == '"' || s[letter] == '\'')
		{
			q = s[letter];
			letter = into_quotes(s, letter);
			if (s[letter] == q)
				letter++;
		}
	}
	if (s[letter] == '|')
		letter++;
	return (letter);
}

char	**ft_split_pipe(char *s, int p_count, char **arr)
{
	int	i;
	int	j;
	int	letter;

	i = -1;
	while (++i < p_count)
	{
		letter = count_letters_pipe(s);
		arr[i] = (char *)malloc(sizeof(char) * (letter + 1));
		if (!arr[i])
		{
			freedom_2d(arr);
			return (NULL);
		}
		j = 0;
		while (j < letter)
			arr[i][j++] = *s++;
		arr[i][j] = '\0';
	}
	arr[i] = NULL;
	return (arr);
}

char	**split_pipes(char *s)
{
	char	**new;
	int		p_count;

	p_count = count_pipe(s);
	new = (char **)malloc(sizeof(char *) * (p_count + 1));
	if (!new)
		return (NULL);
	new = ft_split_pipe(s, p_count, new);
	return (new);
}
