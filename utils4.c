#include "minishell.h"


void	freedom_2d(char **arr)
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
		free(arr[i]);
	free(arr);
}

void freedom_3d(char ***arr)
{
	int i;

	i = 0;
//	while (arr[i] || arr[i + 1])
//	{
//		if (arr[i])
//			freedom_2d(arr[i]);
//		else if (arr[i + 1])
//			freedom_2d(arr[i + 1]);
//		i++;
//	}
	i = -1;
	while(arr[++i])
		freedom_2d(arr[i]);
	free(arr);
}
