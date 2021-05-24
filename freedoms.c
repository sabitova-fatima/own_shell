#include "minishell.h"

void	freedom_2d(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	freedom_3d(char ***arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		freedom_2d(arr[i]);
	free(arr);
}

void	freedom_4d(char ****arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		freedom_3d(arr[i]);
	free(arr);
}

void	freedom_2d_int(int **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	freedom_3d_int(int ***arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		freedom_2d_int(arr[i]);
	free(arr);
}
