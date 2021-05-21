#include "minishell.h"

//архивный файл (может понадобиться, если будут траблы с unused help2, help3)



char	**ft_split_pre(char *s, char *c, int *help2)
{
	char	**arr;
	int		w_count;

	w_count = count_spaces(s, c);
	*help2 = w_count;
	printf("words in command: %d\n", w_count);
	arr = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (!arr)
		return (NULL);
	arr = ft_split2(s, w_count, c, arr);
	return (arr);
}

char ***split_spaces_pre(char **arr, int *help3, int **help2)
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
	*help3 = i;
	*help2 = (int *)malloc(sizeof(int) * i);
	i = -1;
	while (arr[++i])
	{
		printf("before split <%s>\n", arr[i]);
		new[i] = ft_split_pre(arr[i], c, &(*help2)[i]);
		if (!new[i])
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}
