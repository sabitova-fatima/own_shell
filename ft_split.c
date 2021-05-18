
// #include "minishell.h"

// static void	freedom(char **arr, int w_count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < w_count)
// 		free(arr[i++]);
// 	free(arr);
// }

// static char	**ft_split2(char *s, int w_count, char c, char **arr)
// {
// 	int		i;
// 	int		j;
// 	int		letter;

// 	i = -1;
// 	while (++i < w_count)
// 	{
// 		letter = 0;
// 		j = 0;
// 		skip_spaces(s, &letter);
// 		while (s[letter] && s[letter] != c)
// 			letter = into_command_split2(s, letter, c);
// 		arr[i] = (char *)malloc(sizeof(char) * (letter + 1));
// 		if (!arr[i])
// 		{
// 			freedom(arr, i);
// 			return (NULL);
// 		}
// 		while (j < letter)
// 			arr[i][j++] = *s++;
// 		arr[i][j] = '\0';
// //		printf("word |%s|\n", arr[i]);
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }

// char		**ft_split(char *s, char c)
// {
// 	char	**arr;
// 	int		w_count;
// 	int		i;

// 	i = -1;
// 	w_count = 0;
// 	if (!s)
// 		return (NULL);
// 	while (s[++i])
// 		w_count = into_command_split(s, &i, w_count, c);
// //	printf("words in command: %d\n", w_count);
// 	arr = (char **)malloc(sizeof(char *) * (w_count + 1));
// 	if (!arr)
// 		return (NULL);
// 	arr = ft_split2(s, w_count, ' ', arr);
// 	return (arr);
// }
