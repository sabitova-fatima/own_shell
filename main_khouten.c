#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	int i;
	int j;
	char *s;
	char ****all;
	int ****fd;


	while (get_next_line(0, &s))
	{
		all = super_split(s, env, &fd);
		free(s);
	}

}

