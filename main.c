#include "minishell.h"

int main (int argc, char **argv, char **env)
{
	char    ***new;
    int     ***fd;
    char    *input;
    char    **env_copy;
    int     i;
    t_help  help;

    env_copy = copy_env(env);
	// help.error = 0;

	while (1)
	{
        put_dirname();
        signal(SIGINT, ctrl_c);
        signal(SIGQUIT, ctrl_slash);
//         printf(" \033[0m\033[33me-bash>\033[0m$ ");
        input = readline("");
        if (input == NULL)
			exit(0);
        new = super_split(input, env_copy, &fd, &help);
		if (!new)
		{
			// help.error = 1;
			error_status = 1;
			continue ;
		}
		if (new[0][0])
		{
			error_status = 0;
			env_copy = parse_pipes(new, env_copy, fd, input);
			// help.error = 0;
		}
		// help.error = error_status;
		// printf("%d\n", help.error);
	}
}
