#include "minishell.h"

int into_check_empty_redirect(char **arr, int i, int j)
{
	if (arr[i][j] == '\\' && arr[i][j+1])
		j++;
	if (arr[i][j] == '>' || arr[i][j] == '<')
	{
		j++;
		if (arr[i][j] == '>')
			j++;
		skip_spaces(arr[i], &j);
		if (!arr[i][j] || (arr[i][j] == '\\' && !arr[i][j+1]) ||
			arr[i][j] == '>' || arr[i][j] == '<')
		{
			printf("syntax error near > or <\n");
			return (-1);
		}
	}
	if (arr[i][j] != '"' && arr[i][j] != '\'')
		j++;
	return (j);
}

int into_pre_cleaner(char *s, int j, char **new, int *quotes)
{
	char q;

	while (s[j] != '"' && s[j] != '\'' && s[j])
	{
		if (s[j] == '\\' && s[j + 1])
			j++;
		*new = join_char(*new, s[j++]);
	}
	if (s[j] == '"' || s[j] == '\'')
	{
		(*quotes)++;
		q = s[j++];
		while (s[j] != q && s[j])
		{
			if (s[j] == '\\' && q == '"' &&
				(s[j+1] == '\\' || s[j+1] == '"'))
				j++;
			*new = join_char(*new, s[j++]);
		}
		if ((s[j] == '"' && q == '"') ||
			(s[j] == '\'' && q =='\''))
			(*quotes)--;
	}
	return (j);
}

char	**ft_split_pre(char *s, char *c)
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
	arr = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (!arr)
		return (NULL);
	arr = ft_split2(s, w_count, c, arr);
	return (arr);
}

int **create_two(int help)
{
	int **fd_dva_new;
	int i;

	fd_dva_new = (int **)malloc(sizeof(int *) * (help + 1));
	i = -1;
	while(++i < help)
	{
		fd_dva_new[i] = (int *) malloc(sizeof(int) * 2);
		fd_dva_new[i][0] = 0;
		fd_dva_new[i][1] = 1;
	}
	fd_dva_new[i] = NULL;
	return (fd_dva_new);
}

int ***create_three(int help3, int *help2)
{
	int ***fd_three_new;
	int i;

	fd_three_new = (int ***)malloc(sizeof(int **) * (help3 + 1));
	i = -1;
	while(++i < help3)
		fd_three_new[i] = create_two(help2[i]);
	fd_three_new[i] = NULL;
	i = 0;
	while(fd_three_new[i])
		i++;
	return (fd_three_new);
}

