#include "minishell.h"

int main (int argc, char **argv, char **env)
{
	char    ***new;
    int     ***fd;
    char    *input;
    char    **env_copy;
    t_help  help;
    char *line;

//    env_copy = copy_env(env);
    global.error_status = 0;
	while (get_next_line(0, &line))
	{
//        signal(SIGINT, ctrl_c);
//        signal(SIGQUIT, ctrl_slash);
//		input = readline("e-bash> ");
//		if (input == NULL)
//			exit(0);
        new = super_split(line, env, &fd, &help);
		if (!new)
		{
			free(line);
			continue ;
		}
		if (new[0][0])
			env_copy = parse_pipes(new, env, fd, line);
//		free(input);
		free(line);
		freedom_3d(new);
		freedom_3d_int(fd);
	}
	// free(env_copy);
}
