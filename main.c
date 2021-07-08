#include "minishell.h"

int error_status = 0;

int main (int argc, char **argv, char **env)
{
	char    ***new;
    int     ***fd;
    char    *input;
    char    **env_copy;
    int     i;
    t_help  help;

	help.error = 0;
    env_copy = copy_env(env);

	while (1)
	{
        put_dirname();
        signal(SIGINT, ctrl_c);
        signal(SIGQUIT, ctrl_slash);
        input = readline(" \033[0m\033[33me-bash>\033[0m$ ");
        if (input == NULL)
			exit(0);
        new = super_split(input, env_copy, &fd, &help);
        if (new[0][0])
			env_copy = parse_pipes(new, env_copy, fd, input);
	}
}
