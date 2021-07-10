#include "minishell.h"

int main (int argc, char **argv, char **env)
{
	char    ***new;
    int     ***fd;
    char    *input;
    char    **env_copy;
    t_help  help;

    env_copy = copy_env(env);
    global.error_status = 0;
	while (1)
	{
        signal(SIGINT, ctrl_c);
        signal(SIGQUIT, ctrl_slash);
		input = readline("e-bash> ");
		if (input == NULL)
			exit(0);
        new = super_split(input, env_copy, &fd, &help);
		if (!new)
			continue ;
		if (new[0][0])
			env_copy = parse_pipes(new, env_copy, fd, input);
		free(input);
	}
	free(env_copy);
}
