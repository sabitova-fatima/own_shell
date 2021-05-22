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
//		printf("2D:arr[%d]\n", i);
		freedom_2d(arr[i]);
	}
	free(arr);
}

void freedom_4d(char ****arr)
{
	int i;

	i = -1;
	while(arr[++i])
	{
//		printf("3D:arr[%d]\n", i);
		freedom_3d(arr[i]);
	}
	free(arr);
}

void	freedom_2d_int(int **arr)
{
	int	i;

	i = -1;
	while(arr[++i])
	{
//		printf("1D INT [%d]\n", i);
		free(arr[i]);
	}
	free(arr);
}

void freedom_3d_int(int ***arr)
{
	int i;

	i = -1;
	while(arr[++i])
	{
//		printf("2D INT:arr[%d]\n", i);
		freedom_2d_int(arr[i]);
	}
	free(arr);
}

void freedom_4d_int(int ****arr)
{
	int i;

	i = -1;
	while(arr[++i])
	{
//		printf("3D INT:arr[%d]\n", i);
		freedom_3d_int(arr[i]);
	}
	free(arr);
}