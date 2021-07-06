#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *s;
	char ***all;
	int ***fd;
	t_help *help;

	help = (t_help *)malloc(sizeof(t_help));
	help->error = 0;
	while (get_next_line(0, &s))
	{
		all = super_split(s, env, &fd, help);
		free(s);
//		if (all)
//		{
//			freedom_4d(all);
//			freedom_4d_int(fd);
//		}
	}
	free(help);

}

