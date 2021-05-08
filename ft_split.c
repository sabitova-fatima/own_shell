
#include "get_next_line.h"

static void	*freedom(char **arr, int w_count)
{
	int	i;

	i = 0;
	while (i < w_count)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static char	**ft_split2(char const *s, int w_count, char c, char **arr)
{
	int		i;
	int		j;
	int		letter;

	i = -1;
	while (++i < w_count)
	{
		letter = 0;
		j = 0;
		while (*s == c)
			s++;
		while (s[letter] != c && s[letter])
			letter++;
		arr[i] = (char *)malloc(sizeof(char) * (letter + 10));
		if (!arr[i])
			freedom(arr, i);
		while (j < letter)
			arr[i][j++] = *s++;
		arr[i][j] = '\0';
	}
	arr[i] = NULL;
	return (arr);
}

char		**ft_split(char	const *s, char c)
{
	char	**arr;
	int		w_count;
	int		i;

	i = 0;
	w_count = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			w_count++;
		i++;
	}
	arr = (char **)malloc(sizeof(char *) * (w_count + 10));
	if (!arr)
		return (NULL);
	arr = ft_split2(s, w_count, c, arr);
	return (arr);
}
