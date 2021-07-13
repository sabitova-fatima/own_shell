#include "minishell.h"

char	***split_3d(char **new, int ****fd_three)
{
	char	***all;
	int		i;

	i = 0;
	while (new[i])
		i++;
	*fd_three = (int ***)malloc(sizeof(int **) * (i + 1));
	all = split_spaces(new, *fd_three);
	return (all);
}

void	cleaning_3d(char ***all, char **env, int ***fd)
{
	int	i;

	i = -1;
	while (all[++i])
	{
		g_global.i = i;
		cleaner(all[i], env, fd);
	}
}

char	***super_split(char *s, char **env, int ****fd)
{
	char	**new;
	char	***all;

	if (pre_parser(s))
	{
		g_global.error_status = 258;
		return (NULL);
	}
	new = split_pipes(s);
	if (!new)
		return (NULL);
	all = split_3d(new, fd);
	freedom_2d(new);
	cleaning_3d(all, env, *fd);
	if (g_global.read_trouble == 1)
	{
		g_global.error_status = 1;
		g_global.read_trouble = 0;
	}
	return (all);
}
