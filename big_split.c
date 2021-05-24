#include "minishell.h"

char	****split_4d(char ***new, int *****fd_four)
{
	char	****all;
	int		i;
	int		help3;
	int		*help2;

	i = 0;
	while (new[i])
		i++;
	*fd_four = (int ****)malloc(sizeof(int ***) * (i + 1));
	all = (char ****)malloc(sizeof(char ***) * (i + 1));
	i = -1;
	while (new[++i])
	{
		all[i] = split_spaces(new[i], &help3, &help2);
		(*fd_four)[i] = create_3d(help3, help2);
		free(help2);
	}
	all[i] = NULL;
	(*fd_four)[i] = NULL;
	return (all);
}

void	cleaning_4d(char *****all, char **env, int *****fd)
{
	int	i;
	int	j;
	int	k;
	int	help[2];

//	i = -1;
//	while (all[++i])
//	{
//		j = -1;
//		while (all[i][++j])
//		{
//			k = -1;
//			while (all[i][j][++k])
//			{
//				 printf("%i:d j:%d k:%d before clear [%s]\n", i,j,k,
//				 all[i][j][k]);
//			}
//		}
//	}
	i = -1;
	while ((*all)[++i])
	{
		j = -1;
		while ((*all)[i][++j])
		{
			help[0] = i;
			help[1] = j;
			cleaner((*all)[i][j], help, env, fd);
		}
	}
//	i = -1;
//	while (all[++i])
//	{
//		j = -1;
//		while (all[i][++j])
//		{
//			k = -1;
//			while (all[i][j][++k])
//			{
//				printf("BSPLIT read:%d write:%d\n", (*fd)[i][j][k][0], (*fd)
//				[i][j][k][1]);
//				 printf("%i:d j:%d k:%d after clear [%s]\n", i,j,k,
//					    all[i][j][k]);
//			}
//		}
//	}
}

char	****super_split(char *s, char **env, int *****fd)
{
	char	**array;
	char	***new;
	char	****all;

	array = split_semicolon(s);
	if (!array)
		return (NULL);
	if (pre_parser(array))
		return (NULL);
	new = split_pipes(array);
	freedom_2d(array);
	all = split_4d(new, fd);
	freedom_3d(new);
	cleaning_4d(&all, env, fd);
	return (all);
}
