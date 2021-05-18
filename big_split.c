#include "minishell.h"

char **split_semicolon(char *s, int count)
{
	char **arr;
	int i;
	int j;

	arr = (char**)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		j = into_command_semicolon(s, -1);
		arr[i] = ft_strdup(s, j);
		if (!arr[i])
		{
			freedom(arr, i);
			return (NULL);
		}
		s += j;
	}
	arr[i] = NULL;
	return (arr);
}

char ***split_spaces(char **arr, int *help3, int **help2)
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
//		printf("before split <%s>\n", arr[i]);
		new[i] = ft_split(arr[i], c, &(*help2)[i]);
		if (!new[i])
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}

char ***split_pipes(char **arr)
{
	char ***new;
	int i;

	i = 0;
	while(arr[i])
		i++;

	new = (char ***)malloc(sizeof(char **) * i + 1);
	i = -1;
	while (arr[++i])
	{
//		printf("before split <%s>\n", arr[i]);
		new[i] = ft_split_pipe(arr[i], '|');
		if (!new[i])
			return (NULL);
	}

	new[i] = NULL;
	return (new);
}

char ****split_4d(char ***new, int *****fd_four)
{
	char ****all;
	int i;
	int ****fd_four_new;
	int help3;
	int *help2;

	i = 0;
	while (new[i])
		i++;
	fd_four_new = (int ****)malloc(sizeof(int ***)*(i+1));
	all = (char ****)malloc(sizeof(char ***) * i + 1);

	i = -1;
	while(new[++i])
	{
		all[i] = split_spaces(new[i], &help3, &help2);

//		printf("help3 %d help2 %d \n", help3, help2[i]);
		fd_four_new[i] = create_three(help3, help2);
	}

	fd_four_new[i] = NULL;
	i = 0;
	while(fd_four_new[i])
		i++;
//	printf("iii %d\n", i);
	all[i] = NULL;
	*fd_four = fd_four_new;
	return(all);
}

char ****super_split(char *s, char **env, int *****fd)
{
	int semi_count;
	char **array;
	char ***new;
	char ****all;
	int i;
	int j;
	int k;

	int ****fd_four;

	semi_count = w_count(s);
//	printf("\n\n\ncommands_count = %d\n", count);
	array = split_semicolon(s, semi_count);

	if (!array)
		return (NULL);
	if (pre_parser(array))
		return (NULL);


	new = split_pipes(array);
	all = split_4d(new, &fd_four);
//	int tri = 0;
//	int dva = 0;
//	int odin = 0;
//	while (fd_four[tri])
//	{
//		dva= 0;
//		while (fd_four[tri][dva])
//		{
//			odin = 0;
//			while(fd_four[tri][dva][odin])
//				odin++;
//			printf("1mernikov: %d\n", odin);
//			dva++;
//		}
//		printf("2mernikov: %d\n", dva);
//		tri++;
//		printf("3mernikov: %d\n", tri);
//	}

	i = -1;
	while(all[++i])
	{
		j = -1;
		while (all[i][++j])
		{
			k = -1;
			while(all[i][j][++k])
			{
				// printf("%i:d j:%d k:%d before clear [%s]\n", i,j,k,
				// all[i][j][k]);
			}
		}
	}
	i = -1;
	while (all[++i])
	{
		j = -1;
		while(all[i][++j])
		{
			if (cleaner(all[i][j], env))
				return (NULL);
		}
	}
	i = -1;
	while(all[++i])
	{
		j = -1;
		while (all[i][++j])
		{
			k = -1;
			while(all[i][j][++k])
			{
				// printf("%i:d j:%d k:%d after clear [%s]\n", i,j,k,
					//    all[i][j][k]);
			}
		}
	}
	return (all);
}
