#include "minishell.h"

int **create_two(int help)
{
	int **fd_dva_new;
	int i;

	fd_dva_new = (int **)malloc(sizeof(int *) * (help + 1));
	i = -1;
	while(++i < help)
	{
		fd_dva_new[i] = (int *) malloc(sizeof(int) * 2);
		fd_dva_new[i][0] = 0;
		fd_dva_new[i][1] = 1;
	}
	fd_dva_new[i] = NULL;
	return (fd_dva_new);
}

int ***create_three(int help3, int *help2)
{
	int ***fd_three_new;
	int i;

	fd_three_new = (int ***)malloc(sizeof(int **) * (help3 + 1));
	i = -1;
	while(++i < help3)
		fd_three_new[i] = create_two(help2[i]);
	fd_three_new[i] = NULL;
	i = 0;
	while(fd_three_new[i])
		i++;
	return (fd_three_new);
}

