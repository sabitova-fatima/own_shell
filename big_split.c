#include "minishell.h"

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
		fd_four_new[i] = create_three(help3, help2);
	}

	fd_four_new[i] = NULL;
	i = 0;
	while(fd_four_new[i])
		i++;
	all[i] = NULL;
	*fd_four = fd_four_new;
	return(all);
}
void	freedom_2dd(char **arr)
{
	int	i;

//	i = 0;
//	while (arr[i] || arr[i + 1])
//	{
//		if (arr[i])
//			free(arr[i]);
//		else if (arr[i + 1])
//			free(arr[i + 1]);
//		i++;
//	}
	i = -1;
	while(arr[++i])
	{
//		printf("arr[%d] [%s]\n", i, arr[i]);
		free(arr[i]);
	}
	free(arr);
}
char ****super_split(char *s, char **env, int *****fd)
{
	char **array;
	char ***new;
	char ****all;
//	int i;
//	int j;
//	int k;
//	int ****fd_four;

	array = split_semicolon(s);
	if (!array)
		return (NULL);
	if (pre_parser(array))
		return (NULL);

//	new = split_pipes(array);
	freedom_2dd(array);
//	all = split_4d(new, &fd_four);
//	*fd = fd_four;
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

//	i = -1;
//	while(all[++i])
//	{
//		j = -1;
//		while (all[i][++j])
//		{
//			k = -1;
//			while(all[i][j][++k])
//			{
//				// printf("%i:d j:%d k:%d before clear [%s]\n", i,j,k,
//				// all[i][j][k]);
//			}
//		}
//	}
//	i = -1;
//	while (all[++i])
//	{
//		j = -1;
//		while(all[i][++j])
//		{
//			if (cleaner(all[i][j], env))
//				return (NULL);
//		}
//	}
//	i = -1;
//	while(all[++i])
//	{
//		j = -1;
//		while (all[i][++j])
//		{
//			k = -1;
//			while(all[i][j][++k])
//			{
//				// printf("%i:d j:%d k:%d after clear [%s]\n", i,j,k,
//					//    all[i][j][k]);
//			}
//		}
//	}
	return (all);
}
