#include "minishell.h"


void	freedom_2d(char **arr)
{
	int	i;

	i = -1;
	while(arr[++i])
	{
//		printf("arr[%d] [%s]\n", i, arr[i]);
		free(arr[i]);
	}
		free(arr);
}

void freedom_3d(char ***arr)
{
	int i;

	i = -1;
	while(arr[++i])
	{
//		printf("3D:arr[%d]\n", i);
		freedom_2d(arr[i]);
	}
	free(arr);
}
