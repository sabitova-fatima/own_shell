#include "minishell.h"

char	***split_3d(char **new, int ****fd_three)
{
	char	***all;
	int		i;

	i = 0;
	while (new[i])
		i++;
	*fd_three = (int ***)malloc(sizeof(int **) * i + 1);
	all = split_spaces(new, fd_three);
	return (all);
}

void	cleaning_3d(char ****all, char **env, int ****fd)
{
	int	i;
	int	j;
	int	help;

	i = -1;
	while ((*all)[++i])
	{
		j = -1;
		while ((*all)[i][++j])
		{
			printf("%i:d j:%d before clear [%s]\n", i,j,(*all)[i][j]);
		}
	}

	i = -1;
	while ((*all)[++i])
	{
		help = i;
		cleaner((*all)[i], help, env, fd);
	}
	i = -1;
	while ((*all)[++i])
	{
		j = -1;
		while ((*all)[i][++j])
		{
			printf("BSPLIT read:%d write:%d\n", (*fd)[i][j][0], (*fd)[i][j][1]);
			printf("%i:d j:%d after clear [%s]\n", i,j,(*all)[i][j]);
		}
	}
}

char	***super_split(char *s, char **env, int ****fd)
{
	char	**new;
	char	***all;

	if (pre_parser(s))
		return (NULL);
	new = split_pipes(s);
	if (!new)
		return (NULL);
	all = split_3d(new, fd);
	freedom_2d(new);
	cleaning_3d(&all, env, fd);
	return (all);
}
