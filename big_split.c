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

void	cleaning_3d(char ****all, char **env, int ****fd, t_help *help)
{
	int	i;
	int	j;

	// i = -1;
	// while ((*all)[++i])
	// {
	// 	j = -1;
	// 	while ((*all)[i][++j])
	// 	{
	// 		printf("%i:d j:%d before clear [%s]\n", i,j,(*all)[i][j]);
	// 	}
	// }
	i = -1;
	while ((*all)[++i])
	{
		help->help = i;
		cleaner((*all)[i], help, env, fd);
	}
	 i = -1;
	 while ((*all)[++i])
	 {
	 	j = -1;
	 	while ((*all)[i][++j])
	 	{
	 		// printf("%i:d j:%d after clear [%s] read:%d write:%d\n", i,j,
					// (*all)[i][j], (*fd)[i][j][0], (*fd)[i][j][1]);
	 	}
	 }
}

char	***super_split(char *s, char **env, int ****fd, t_help *help)
{
	char	**new;
	char	***all;

	if (pre_parser(s, help))
		return (NULL);
	new = split_pipes(s);
	if (!new)
		return (NULL);
	all = split_3d(new, fd);
	freedom_2d(new);
	cleaning_3d(&all, env, fd, help);
	return (all);
}
