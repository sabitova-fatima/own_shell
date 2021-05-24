#include "minishell.h"

int	count_spaces(char *s, char *c)
{
	int	i;
	int	w_count;

	i = -1;
	w_count = 0;
	while (s[++i])
	{
		i = count_spaces_help(s, i, &w_count, c);
		if (!s[i])
			break ;
	}
	return (w_count);
}

int	count_letters(char *s, char *c)
{
	char	q;
	int		letter;

	letter = 0;
	skip_spaces(s, &letter);
	while (s[letter] && s[letter] != c[0] && s[letter] != c[1])
	{
		while (s[letter] != '"' && s[letter] != '\'' && s[letter] != c[0] \
		&& s[letter] != c[1] && s[letter])
		{
			if (s[letter] == '\\' && s[letter + 1])
				letter++;
			letter++;
		}
		if (s[letter] == '"' || s[letter] == '\'')
		{
			q = s[letter];
			letter = into_quotes(s, letter);
			if (s[letter] == q)
				letter++;
		}
	}
	return (letter);
}

char	**ft_split2(char *s, int w_count, char *c, char **arr)
{
	int		i;
	int		j;
	int		letter;

	i = -1;
	while (++i < w_count)
	{
		letter = count_letters(s, c);
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
//		printf("word [%s]\n", arr[i]);
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char *s, int *help2)
{
	char	**arr;
	int		w_count;
	char	c[2];

	c[0] = ' ';
	c[1] = '	';
	w_count = count_spaces(s, c);
//	printf("words in command: %d\n", w_count);
	*help2 = w_count;
	arr = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (!arr)
		return (NULL);
	arr = ft_split2(s, w_count, c, arr);
	return (arr);
}

char	***split_spaces(char **arr, int *help3, int **help2)
{
	char	***new;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new = (char ***)malloc(sizeof(char **) * (i + 1));
	if (!new)
		return (NULL);
	*help3 = i;
	*help2 = (int *)malloc(sizeof(int) * i);
	i = -1;
	while (arr[++i])
	{
//		printf("before split spaces [%s]\n", arr[i]);
		new[i] = ft_split(arr[i], &(*help2)[i]);
		if (!new[i])
		{
			freedom_3d(new);
			return (NULL);
		}
	}
	new[i] = NULL;
	return (new);
}
