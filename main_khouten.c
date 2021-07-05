#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *s;
	char ***all;
	int ***fd;

	while (get_next_line(0, &s))
	{
		all = super_split(s, env, &fd);
		free(s);
//		if (all)
//		{
//			freedom_4d(all);
//			freedom_4d_int(fd);
//		}
	}


}

